#pragma once
#include <string>
#include <unordered_map>

#include "AccessSpecifier.h"
#include "ICppClassData.h"
#include "IBuilder.h"
#include "IDataField.h"
#include "IEnum.h"
#include "IMethod.h"

namespace ccrt
{
	class CRRTAPI CppClassBuilder : public IBuilder<ICppClassData>
	{
	public:
		friend class CppClassData;
		ICppClassData* Build() override;
	public:
		CppClassBuilder& SetUSR(std::string usr);
		CppClassBuilder& SetName(std::string name);
		CppClassBuilder& SetFileName(std::string path);
		CppClassBuilder& SetFilePath(std::string path);
		CppClassBuilder& SetDirectoryPath(std::string path);
		CppClassBuilder& AddBaseClass(std::string usr);
		CppClassBuilder& AddDataField(std::string type, std::string name, std::string usr, std::string defaultValue);
		CppClassBuilder& AddMethods(std::string returnType, std::string name, std::vector<std::string> arguments);
		CppClassBuilder& AddEnum(std::string name,std::string usr);
		CppClassBuilder& AddEnumConstant(std::string constantName);
		CppClassBuilder& SetPublic();
		CppClassBuilder& SetProtected();
		CppClassBuilder& SetPrivate();

	public:
		AccessSpecifier GetCurrentAccessSpecifier();

	private:
		std::string usr;
		std::string name;
		std::string filepath;
		std::string filename;
		std::string directorypath;
		std::vector<std::string> baseClasses;
		std::vector<std::shared_ptr<IDataField>> dataFields;
		std::vector<std::shared_ptr<IMethod>> methods;
		std::unordered_map<std::string,std::shared_ptr<IEnum>> enums;
		AccessSpecifier currentAccessSpecifier = Public;
		std::string currentEnumName;
	};

}
