#pragma once
#include <string>
#include <vector>

#include "IMethod.h"

namespace ccrt
{
	class Method : public IMethod
	{
	public:
		Method(AccessSpecifier accessSpecifier, std::string returnType, std::string name, std::vector<std::string> arguments);

	public:
		AccessSpecifier GetAccessSpecifier() override;
		std::string GetReturnType() override;
		std::string GetName() override;
		std::vector<std::string> GetArguments() override;
		void Serialize(std::ostringstream& stream) override;
		void Deserialize(std::istringstream& stream) override;
	private:
		AccessSpecifier accessSpecifier_;
		std::string returnType_;
		std::string name_;
		std::vector<std::string> arguments_;
	};
}
