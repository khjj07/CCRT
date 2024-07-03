#pragma once
#include "Define.h"
#include "ISerializable.h"

namespace ccrt
{
	class CRRTAPI IMethod : public ISerializable
	{
	public:
		virtual std::string GetAccessSpecifier() = 0;
		virtual std::string GetName() = 0;
		virtual std::string GetReturnType() = 0;
		virtual std::vector<std::string> GetArguments() = 0;
	};
}
