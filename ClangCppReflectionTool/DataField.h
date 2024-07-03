#pragma once
#include <string>

#include "IDataField.h"

namespace ccrt
{
	class CRRTAPI DataField : public IDataField
	{
	public:
		DataField(std::string accessSpecifier, std::string type, std::string name, std::string usr, std::string defaultValue);
	public:
		std::string GetType() override;
		std::string GetAccessSpecifier() override;
		std::string GetName() override;
		std::string GetUSR() override;
		std::string GetDefaultValue() override;
		void Serialize(std::ostringstream& stream) override;
		void Deserialize(std::istringstream& stream) override;

	private:
		std::string accessSpecifier_;
		std::string type_;
		std::string usr_;
		std::string name_;
		std::string defaultValue_;


	};
}
