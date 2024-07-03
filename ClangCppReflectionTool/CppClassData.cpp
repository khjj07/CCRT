#include "CppClassData.h"

ccrt::CppClassData::CppClassData(const CppClassBuilder& builder)
	: usr_(builder.usr),
	name_(builder.name),
	filepath_(builder.filepath),
	filename_(builder.filename),
	directorypath_(builder.directorypath),
	dataFields_(builder.dataFields),
	methods_(builder.methods)
{

}

void ccrt::CppClassData::Serialize(std::ostringstream& stream)
{
	stream << "[USR] " << usr_ << std::endl;
	stream << "[Name] " << name_ << std::endl;
	stream << "[FileName] " << filename_ << std::endl;
	stream << "[FilePath] " << filepath_ << std::endl;
	stream << "[DirectoryPath] " << directorypath_ << std::endl;
	for (auto baseClass : baseClasses_)
	{
		stream << "[BaseClass] " << baseClass << std::endl;
	}
	for (auto dataField : dataFields_)
	{
		dataField->Serialize(stream);
		stream << std::endl;
	}
	for (auto method : methods_)
	{
		method->Serialize(stream);
		stream << std::endl;
	}
}

void ccrt::CppClassData::Deserialize(std::istringstream& stream)
{

}

std::string ccrt::CppClassData::GetName()
{
	return name_;
}

std::string ccrt::CppClassData::GetFileDirectoryPath()
{
	return directorypath_;
}

std::string ccrt::CppClassData::GetFilePath()
{
	return filepath_;
}

std::string ccrt::CppClassData::GetFileName()
{
	return filename_;
}


std::string ccrt::CppClassData::GetUSR()
{
	return usr_;
}

std::vector<std::shared_ptr<ccrt::IDataField>> ccrt::CppClassData::GetDataFields()
{
	return dataFields_;
}

std::vector<std::shared_ptr<ccrt::IMethod>> ccrt::CppClassData::GetMethods()
{
	return methods_;
}
