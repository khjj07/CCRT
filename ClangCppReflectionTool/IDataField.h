#pragma once
#include "Define.h"
#include "ISerializable.h"

namespace ccrt
{
	class IDataField : public ISerializable
	{

	public:
		virtual std::string GetName() = 0;
		virtual std::string GetType() = 0;
		virtual std::string GetUSR() = 0;
		virtual std::string GetDefaultValue() = 0;
		virtual AccessSpecifier GetAccessSpecifier() = 0;
	};
}
