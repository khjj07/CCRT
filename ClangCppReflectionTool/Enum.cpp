#include "Enum.h"

ccrt::Enum::Enum(std::string name, std::string usr)
	: name_(name), usr_(usr)
{
}

void ccrt::Enum::Serialize(std::ostringstream& stream)
{
	stream << "[Enum] " << name_;
	for (auto constant : constants_)
	{
		stream << std::endl;
		stream << "[EnumConstant] " << constant;
	}
}

void ccrt::Enum::Deserialize(std::istringstream& stream)
{
}

std::string ccrt::Enum::GetName()
{
	return name_;
}

std::string ccrt::Enum::GetUSR()
{
	return usr_;
}

std::vector<std::string> ccrt::Enum::GetConstants()
{
	return constants_;
}

void ccrt::Enum::AddConstant(std::string constant)
{
	constants_.push_back(constant);
}
