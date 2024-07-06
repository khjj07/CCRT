#include "CppClassBuilder.h"

#include "AccessSpecifier.h"
#include "CppClassData.h"
#include "DataField.h"
#include "Enum.h"
#include "Method.h"

ccrt::ICppClassData* ccrt::CppClassBuilder::Build()
{
	return new CppClassData(*this);
}

ccrt::CppClassBuilder& ccrt::CppClassBuilder::SetUSR(std::string usr)
{
	this->usr = usr;
	return *this;
}

ccrt::CppClassBuilder& ccrt::CppClassBuilder::SetName(std::string name)
{
	this->name = name;
	return *this;
}

ccrt::CppClassBuilder& ccrt::CppClassBuilder::SetFileName(std::string filename)
{
	this->filename = filename;
	return *this;
}

ccrt::CppClassBuilder& ccrt::CppClassBuilder::SetFilePath(std::string path)
{
	this->filepath = path;
	return *this;
}

ccrt::CppClassBuilder& ccrt::CppClassBuilder::SetDirectoryPath(std::string directorypath)
{
	this->directorypath = directorypath;
	return *this;
}


ccrt::CppClassBuilder& ccrt::CppClassBuilder::AddBaseClass(std::string usr)
{
	baseClasses.push_back(usr);
	return *this;
}

ccrt::CppClassBuilder& ccrt::CppClassBuilder::AddDataField(std::string type, std::string name, std::string usr, std::string defaultValue)
{
	dataFields.push_back(std::make_shared<DataField>(currentAccessSpecifier,type, name, usr, defaultValue));
	return *this;
}

ccrt::CppClassBuilder& ccrt::CppClassBuilder::AddMethods(std::string returnType, std::string name,std::vector<std::string> arguments)
{
	methods.push_back(std::make_shared<Method>(currentAccessSpecifier, returnType, name, arguments));
	return *this;
}

ccrt::CppClassBuilder& ccrt::CppClassBuilder::AddEnum(std::string name,std::string usr)
{
	currentEnumName = name;
	enums.insert(std::make_pair(name,std::make_shared<Enum>(name,usr)));
	return *this;
}

ccrt::CppClassBuilder& ccrt::CppClassBuilder::AddEnumConstant(std::string constantName)
{
	enums[currentEnumName]->AddConstant(constantName);
	return *this;
}

ccrt::CppClassBuilder& ccrt::CppClassBuilder::SetPublic()
{
	currentAccessSpecifier = Public;
	return *this;
}

ccrt::CppClassBuilder& ccrt::CppClassBuilder::SetProtected()
{
	currentAccessSpecifier = Protected;
	return *this;
}

ccrt::CppClassBuilder& ccrt::CppClassBuilder::SetPrivate()
{
	currentAccessSpecifier = Private;
	return *this;
}


ccrt::AccessSpecifier ccrt::CppClassBuilder::GetCurrentAccessSpecifier()
{
	return currentAccessSpecifier;
}
