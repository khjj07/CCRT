#pragma once
#include <string>
#include <istream>
#include <ostream>
#include <sstream>

#include "AccessSpecifier.h"
#include "Define.h"
#include "IRDataField.h"

namespace ccrt
{
	template<typename T>
	class RDataField : public IRDataField
	{
	public:
		RDataField(std::string  accessSpecifier, T& value);

	public:
		std::string GetType() override;
		std::string GetValue() override;
		std::string GetAccessSpecifier() override;
		void SetValue(std::string value) override;

	private:
		T& value_;
		std::string  accessSpecifier_;
	};

	template <typename T>
	RDataField<T>::RDataField(std::string  accessSpecifier, T& value)
		:accessSpecifier_(accessSpecifier),value_(value) {}

	template <typename T>
	std::string RDataField<T>::GetType()
	{
		return typeid(decltype(value_)).name();
	}

	template <typename T>
	std::string RDataField<T>::GetValue()
	{
		std::ostringstream ss;
		ss << value_;
		return ss.str();
	}

	template <typename T>
	std::string  RDataField<T>::GetAccessSpecifier()
	{
		return accessSpecifier_;
	}

	template <typename T>
	void RDataField<T>::SetValue(std::string value)
	{
		std::istringstream ss(value);
		ss >> value_;
	}
}

