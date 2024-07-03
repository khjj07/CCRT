#include "Method.h"

#include <cstdarg>

ccrt::Method::Method(std::string accessSpecifier, std::string returnType, std::string name, std::vector<std::string> arguments)
	: accessSpecifier_(accessSpecifier), returnType_(returnType), name_(name), arguments_(arguments)
{

}


std::string ccrt::Method::GetAccessSpecifier()
{
	return accessSpecifier_;
}

std::string ccrt::Method::GetReturnType()
{
	return returnType_;
}

std::string ccrt::Method::GetName()
{
	return name_;
}

std::vector<std::string> ccrt::Method::GetArguments()
{
	return arguments_;
}

void ccrt::Method::Serialize(std::ostringstream& stream)
{
	stream << "[Method]" << returnType_ << " " << name_;
}

void ccrt::Method::Deserialize(std::istringstream& stream)
{
}
