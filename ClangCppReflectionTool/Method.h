#pragma once
#include <string>
#include <vector>

#include "IMethod.h"

namespace ccrt
{
	class CRRTAPI Method : public IMethod
	{
	public:
		Method(std::string accessSpecifier, std::string returnType, std::string name, std::vector<std::string> arguments);

	public:
		std::string GetAccessSpecifier() override;
		std::string GetReturnType() override;
		std::string GetName() override;
		std::vector<std::string> GetArguments() override;
		void Serialize(std::ostringstream& stream) override;
		void Deserialize(std::istringstream& stream) override;
	private:
		std::string accessSpecifier_;
		std::string returnType_;
		std::string name_;
		std::vector<std::string> arguments_;
	};
}
