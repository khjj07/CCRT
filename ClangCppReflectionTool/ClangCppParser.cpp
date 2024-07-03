#include "ClangCppParser.h"

#include <filesystem>
#include <iostream>

#include "CppClassBuilder.h"
#include "MacroManager.h"
#include "Util.h"

ccrt::MacroManager ccrt::ClangCppParser::macroManager_;


CXTranslationUnit ccrt::ClangCppParser::Translate(std::string fileName, const char** commandLineArgs,int numCommandLineArgs)
{
	CXIndex index = clang_createIndex(0, 0);
	
	auto unit = clang_parseTranslationUnit(index, fileName.c_str(), commandLineArgs, numCommandLineArgs, nullptr, 0,
		CXTranslationUnit_SkipFunctionBodies |
		CXTranslationUnit_DetailedPreprocessingRecord |
		CXTranslationUnit_IncludeAttributedTypes |
		CXTranslationUnit_VisitImplicitAttributes | CXTranslationUnit_KeepGoing);
	return unit;
}

CXCursor ccrt::ClangCppParser::GetCursor(CXTranslationUnit unit)
{
	return clang_getTranslationUnitCursor(unit);
}

std::vector<ccrt::ICppClassData*> ccrt::ClangCppParser::GenerateCppClassFromFolder(std::string folderPath, const char** commandLineArgs, int numCommandLineArgs)
{
	std::vector<ccrt::ICppClassData*> result;
	std::filesystem::path path(folderPath);
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		if (entry.is_regular_file())
		{
			result.push_back(GenerateCppClassFromFile(entry.path().generic_string(), commandLineArgs, numCommandLineArgs));
		}
		else if (entry.is_directory())
		{
			std::vector<ICppClassData*> tmp = GenerateCppClassFromFolder(entry.path().generic_string(), commandLineArgs, numCommandLineArgs);
			result.insert(result.end(), tmp.begin(), tmp.end());
		}
	}
	return result;
}

std::string ccrt::ClangCppParser::GetFieldDefaultValue(CXCursor cursor)
{
	CXSourceRange  extent = clang_getCursorExtent(cursor);
	std::string initializerStr;
	CXToken* tokens;
	unsigned int numTokens;
	auto unit = clang_Cursor_getTranslationUnit(cursor);
	clang_tokenize(unit, extent, &tokens, &numTokens);
	std::vector<std::string> args;

	for (unsigned int i = 0; i < numTokens; ++i)
	{
		CXString tokenString = clang_getTokenSpelling(unit, tokens[i]);
		initializerStr += std::string(clang_getCString(tokenString));
		clang_disposeString(tokenString);
	}
	size_t equalPosition = initializerStr.find('=');
	if (equalPosition != std::string::npos)
	{
		auto result = std::string(initializerStr.begin() + equalPosition, initializerStr.end());
		return trim(result);
	}
	return "";
}

std::vector<std::string> ccrt::ClangCppParser::GetMethodArguments(CXCursor cursor)
{
	std::vector<std::string> result;
	int numArgs = clang_Cursor_getNumArguments(cursor);
	for (int i = 0; i < numArgs; ++i) {
		CXCursor argCursor = clang_Cursor_getArgument(cursor, i);
		CXType argType = clang_getCursorType(argCursor);
		CXString argTypeName = clang_getTypeSpelling(argType);
		result.push_back(clang_getCString(argTypeName));
		clang_disposeString(argTypeName);
	}
	return result;
}

ccrt::ICppClassData* ccrt::ClangCppParser::GenerateCppClassFromFile(std::string filepath, const char** commandLineArgs, int numCommandLineArgs)
{
	CppClassBuilder builder;
	auto path = std::filesystem::path(filepath);
	builder.SetFileName(path.filename().generic_string());
	builder.SetDirectoryPath(path.parent_path().generic_string());
	builder.SetFilePath(filepath);
	CXCursor cursor = GetCursor(Translate(filepath,commandLineArgs,numCommandLineArgs));
	clang_visitChildren(cursor, FileVisitor, &builder);
	return builder.Build();
}


std::vector<std::string> ccrt::ClangCppParser::ParseMacroExpansion(CXTranslationUnit tu, CXCursor cursor)
{
	std::vector<std::string> result;

	CXSourceRange range = clang_getCursorExtent(cursor);
	CXToken* tokens;
	unsigned int numTokens;
	clang_tokenize(tu, range, &tokens, &numTokens);

	for (unsigned int i = 0; i < numTokens; ++i) {
		CXToken token = tokens[i];
		CXString tokenSpelling = clang_getTokenSpelling(tu, token);
		result.push_back(clang_getCString(tokenSpelling));
		clang_disposeString(tokenSpelling);
	}

	clang_disposeTokens(tu, tokens, numTokens);
	return result;
}

CXChildVisitResult ccrt::ClangCppParser::FileVisitor(CXCursor child, CXCursor parent, CXClientData clientData)
{
	auto builder = static_cast<CppClassBuilder*>(clientData);

	CXCursorKind cursorKind = clang_getCursorKind(child);

	CXType cursorType = clang_getCursorType(child);
	CXCursor typeDeclarationCursor = clang_getTypeDeclaration(cursorType);

	std::string cursorString = clang_getCString(clang_getCursorSpelling(child));
	std::string typeString = clang_getCString(clang_getTypeSpelling(cursorType));
	std::string usr = clang_getCString(clang_getCursorUSR(child));
	std::string baseClassUSR = clang_getCString(clang_getCursorUSR(typeDeclarationCursor));


	CXSourceLocation cursorLocation = clang_getCursorLocation(child);

	CXFile file;
	unsigned int line, column;
	clang_getFileLocation(cursorLocation, &file, &line, &column, NULL);

	if (clang_Location_isFromMainFile(cursorLocation))
	{
		auto currentMacro = macroManager_.GetCurrentMacro(line);

		switch (cursorKind)
		{
		case CXCursor_MacroExpansion:
		{
			std::vector<std::string> macroTokens = ParseMacroExpansion(clang_Cursor_getTranslationUnit(child), child);
			macroManager_.AddMacro(std::move(macroTokens), line);
		}
		break;
		case CXCursor_CXXBaseSpecifier:
			builder->AddBaseClass(baseClassUSR);
			break;
		case CXCursor_StructDecl:
			if (clang_isCursorDefinition(clang_getCursorDefinition(child)))
			{
				if (currentMacro == nullptr || currentMacro->GetType() != IMacro::Uclass)
				{
					return CXChildVisit_Break;
				}
				else
				{
					macroManager_.GetCurrentMacro(line)->SetFlag(true);
				}
				builder->SetName(typeString);
				builder->SetUSR(usr);
				builder->SetPublic();
			}
			break;
		case CXCursor_ClassDecl:
			if (clang_isCursorDefinition(clang_getCursorDefinition(child)))
			{
				if (currentMacro == nullptr || currentMacro->GetType() != IMacro::Uclass)
				{
					return CXChildVisit_Break;
				}
				else
				{
					currentMacro->SetFlag(true);
				}
				builder->SetName(typeString);
				builder->SetUSR(usr);
				builder->SetPrivate();
			}
			break;
		case CXCursor_ClassTemplate:
			if (clang_isCursorDefinition(clang_getCursorDefinition(child)))
			{
				if (currentMacro == nullptr || currentMacro->GetType() != IMacro::Uclass)
				{
					return CXChildVisit_Break;
				}
				else
				{
					currentMacro->SetFlag(true);
				}
				builder->SetName(cursorString);
				builder->SetUSR(usr);
				builder->SetPrivate();
			}
			break;
		case CXCursor_CXXAccessSpecifier:
			switch (clang_getCXXAccessSpecifier(child))
			{
			case CX_CXXPublic:
				builder->SetPublic();
				break;
			case CX_CXXProtected:
				builder->SetProtected();
				break;
			case CX_CXXPrivate:
				builder->SetPrivate();
				break;
			}
			break;

		case CXCursor_EnumDecl:
			builder->AddEnum(cursorString, usr);
			break;
		case CXCursor_EnumConstantDecl:
			builder->AddEnumConstant(cursorString);
			break;
		case CXCursor_FieldDecl:
			if (currentMacro == nullptr || currentMacro->GetType() != IMacro::Uproperty)
			{
				return CXChildVisit_Recurse;
			}
			else
			{
				currentMacro->SetFlag(true);
			}
			switch (cursorType.kind)
			{
			case CXType_Elaborated:
			{
				CXType namedType = clang_Type_getNamedType(cursorType);
				std::string typeName = clang_getCString(clang_getTypeSpelling(namedType));
				if (namedType.kind == CXType_Enum)
				{
					builder->AddDataField(typeName, cursorString, baseClassUSR, GetFieldDefaultValue(child));
				}
				else
				{
					builder->AddDataField(typeString, cursorString, usr, GetFieldDefaultValue(child));
				}
			}
			break;
			default:
				builder->AddDataField(typeString, cursorString, usr, GetFieldDefaultValue(child));
				break;
			}
			break;
		case CXCursor_CXXMethod:
			{
			CXType returnType = clang_getCursorResultType(child);
			std::string returnTypeName = clang_getCString(clang_getTypeSpelling(returnType));

			std::vector<std::string> arguments = GetMethodArguments(child);
				
			builder->AddMethods(returnTypeName,cursorString, arguments);
			}
			
			break;
		}
		return CXChildVisit_Recurse;
	}
	else
	{
		return CXChildVisit_Recurse;
	}
}
