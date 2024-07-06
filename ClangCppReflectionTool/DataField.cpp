#include "DataField.h"

ccrt::DataField::DataField(AccessSpecifier accessSpecifier, std::string type, std::string name, std::string usr, std::string defaultValue)
	: accessSpecifier_(accessSpecifier),type_(type), name_(name), usr_(usr), defaultValue_(defaultValue) {}

std::string ccrt::DataField::GetType()
{
	return type_;
}

ccrt::AccessSpecifier ccrt::DataField::GetAccessSpecifier()
{
	return accessSpecifier_;
}

std::string ccrt::DataField::GetName()
{
	return name_;
}

std::string ccrt::DataField::GetUSR()
{
	return usr_;
}

std::string ccrt::DataField::GetDefaultValue()
{
	return defaultValue_;
}

void ccrt::DataField::Serialize(std::ostringstream& stream)
{
	stream << "[DataField] " << accessSpecifier_ << " " << type_ << " " << name_ << " " << defaultValue_;
}

void ccrt::DataField::Deserialize(std::istringstream& stream)
{
}
