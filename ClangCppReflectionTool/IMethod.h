#pragma once
#include "AccessSpecifier.h"
#include "Define.h"
#include "ISerializable.h"

namespace ccrt
{
	class IMethod : public ISerializable
	{
	public:
		virtual AccessSpecifier GetAccessSpecifier() = 0;
		virtual std::string GetName() = 0;
		virtual std::string GetReturnType() = 0;
		virtual std::vector<std::string> GetArguments() = 0;
	};
}
