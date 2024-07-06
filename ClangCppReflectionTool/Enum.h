#pragma once
#include "IEnum.h"

namespace ccrt
{
	class Enum : public IEnum
	{
	public:
		Enum(std::string name, std::string usr);
		void Serialize(std::ostringstream& stream) override;
		void Deserialize(std::istringstream& stream) override;
		std::string GetName() override;
		std::string GetUSR() override;
		std::vector<std::string> GetConstants() override;
		void AddConstant(std::string constant) override;

	private:
		std::string name_;
		std::string usr_;
		std::vector<std::string> constants_;
	};
}

