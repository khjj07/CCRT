#pragma once
#include <string>
#include <vector>
#include <clang-c/Index.h>

#include "Define.h"
#include "CppClassData.h"
#include "MacroManager.h"

/// \brief
///	구문분석에 의한 Reflection은 Editor Time 혹은 빌드 이전에 수행되어야함
///

namespace ccrt
{
	class CRRTAPI ClangCppParser
	{
	public:
		ICppClassData* GenerateCppClassFromFile(std::string filepath, const char** commandLineArgs, int numCommandLineArgs);
		std::vector<ccrt::ICppClassData*> GenerateCppClassFromFolder(std::string folderPath, const char** commandLineArgs, int numCommandLineArgs);
		
	private:
		CXTranslationUnit Translate(std::string fileName, const char** commandLineArgs, int numCommandLineArgs);
		CXCursor GetCursor(CXTranslationUnit unit);
		static std::string GetFieldDefaultValue(CXCursor cursor);
		static std::vector<std::string> GetMethodArguments(CXCursor cursor);
		static CXChildVisitResult FileVisitor(CXCursor child, CXCursor parent, CXClientData clientData);
		static std::vector<std::string> ParseMacroExpansion(CXTranslationUnit tu, CXCursor cursor);

	private:
		static MacroManager macroManager_;
	};
}

