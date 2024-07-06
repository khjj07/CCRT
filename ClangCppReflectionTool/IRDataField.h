#pragma once
#include <string>
#include <sstream>

#include "AccessSpecifier.h"
#include "Define.h"

namespace ccrt
{
	class CRRTAPI IRDataField
	{
	public:
		virtual AccessSpecifier GetAccessSpecifier() = 0;
		virtual std::string GetType() = 0;
		virtual std::string GetName() = 0;
		template<typename T>
		void SetValue(T value);
		template<typename T>
		T GetValue();

	protected:
		virtual void SetValue(std::string value) = 0;
		virtual std::string GetValue() = 0;
	};

	template <typename T>
	void IRDataField::SetValue(T value)
	{
		std::ostringstream ss;
		ss << value;
		SetValue(ss.str());
	}

	template <typename T>
	T IRDataField::GetValue()
	{
		T tmp;
		std::istringstream ss(GetValue());
		ss >> tmp;
		return tmp;
	}
}
