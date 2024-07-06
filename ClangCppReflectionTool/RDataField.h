#pragma once
#include <string>
#include <sstream>
#include "AccessSpecifier.h"
#include "IRDataField.h"

namespace ccrt
{
	template<typename T>
	class RDataField : public IRDataField
	{
	public:
		RDataField(AccessSpecifier accessSpecifier, std::string name, T& value);

	public:
		std::string GetName() override;
		std::string GetType() override;
		AccessSpecifier GetAccessSpecifier() override;

	protected:
		std::string GetValue() override;
		void SetValue(std::string value) override;

	private:
		T& value_;
		std::string name_;
		AccessSpecifier accessSpecifier_;
	};

	template <typename T>
	RDataField<T>::RDataField(AccessSpecifier accessSpecifier,std::string name, T& value)
		:accessSpecifier_(accessSpecifier), name_(name),value_(value) {}

	template <typename T>
	std::string RDataField<T>::GetName()
	{
		return name_;
	}

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
	AccessSpecifier RDataField<T>::GetAccessSpecifier()
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

