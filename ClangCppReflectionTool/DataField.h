#pragma once
#include <string>

#include "AccessSpecifier.h"
#include "IDataField.h"

namespace ccrt
{
	class DataField : public IDataField
	{
	public:
		DataField(AccessSpecifier accessSpecifier, std::string type, std::string name, std::string usr, std::string defaultValue);
	public:
		std::string GetType() override;
		AccessSpecifier GetAccessSpecifier() override;
		std::string GetName() override;
		std::string GetUSR() override;
		std::string GetDefaultValue() override;
		void Serialize(std::ostringstream& stream) override;
		void Deserialize(std::istringstream& stream) override;

	private:
		AccessSpecifier accessSpecifier_;
		std::string type_;
		std::string usr_;
		std::string name_;
		std::string defaultValue_;


	};
}
