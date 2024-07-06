#pragma once
#include <vector>
#include "Define.h"
#include "ISerializable.h"

namespace ccrt
{
	class IEnum : public ISerializable
	{
	public:
		virtual std::string GetName() = 0;
		virtual std::string GetUSR() = 0;
		virtual std::vector<std::string> GetConstants() = 0;
		virtual void AddConstant(std::string constant) = 0;
	};
}