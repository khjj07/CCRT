#pragma once
#include "CppClassBuilder.h"
#include "ICppClassData.h"

namespace ccrt
{

	class CRRTAPI CppClassData : public ICppClassData
	{
	public:
		CppClassData(const CppClassBuilder& cpp_class_builder);

	public:
		void Serialize(std::ostringstream& stream) override;
		void Deserialize(std::istringstream& stream) override;
		std::string GetName() override;
		std::string GetFileDirectoryPath() override;
		std::string GetFilePath() override;
		std::string GetFileName() override;
		std::string GetUSR() override;
		std::vector<std::shared_ptr<IDataField>> GetDataFields();
		std::vector<std::shared_ptr<IMethod>> GetMethods();

	private:
		std::string usr_;
		std::string name_;
		std::string filepath_;
		std::string directorypath_;
		std::string filename_;
		std::vector<std::string> baseClasses_;
		std::vector<std::shared_ptr<IDataField>> dataFields_;
		std::vector<std::shared_ptr<IMethod>> methods_;
	};

}
