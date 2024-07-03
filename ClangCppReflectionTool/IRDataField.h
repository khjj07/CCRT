#pragma once
#include <string>
#include "AccessSpecifier.h"
#include "Define.h"

namespace ccrt
{
	class CRRTAPI IRDataField
	{
	public:
		virtual std::string  GetAccessSpecifier() = 0;
		virtual std::string GetType() = 0;
		virtual std::string GetValue() = 0;
		virtual void SetValue(std::string value) = 0;
	};
}
