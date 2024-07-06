#pragma once
#include <unordered_map>
#include <ostream>
#include <istream>
#include "IRDataField.h"
#include "IReflectedClass.h"
#include "IRMethod.h"
#include "Define.h"


namespace ccrt
{
	class CRRTAPI ReflectedClass : public IReflectedClass
	{
	public:
		ReflectedClass();

	public:
		void SetID(std::string id) override;
		std::string GetID() override;
		IRMethod* GetMethod(std::string name);
		IRDataField* GetDataField(std::string name);

		void AddDataField(std::string name, IRDataField* dataField);
		void AddMethod(std::string name, IRMethod* method);

		void ShowAllReflectedData();

		template<typename ReturnType, typename... Args>
		ReturnType Invoke(std::string name, Args... a1);

		template<typename T>
		void Set(std::string name, T value);

		template<typename T>
		T Get(std::string name);
		void ApplyReflectionData() override;


		std::string id;

	private:
		std::unordered_map<std::string, IRDataField*> dataFields_;
		std::unordered_map<std::string, IRMethod*> methods_;
	};


	template <typename ReturnType, typename ... Args>
	ReturnType ReflectedClass::Invoke(std::string name, Args... a1)
	{
		return GetMethod(name)->Invoke<int>(a1...);
	}

	template <typename T>
	void ReflectedClass::Set(std::string name, T value)
	{
		GetDataField(name)->SetValue(value);
	}

	template <typename T>
	T ReflectedClass::Get(std::string name)
	{
		return GetDataField(name)->GetValue<T>();
	}
}
