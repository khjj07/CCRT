#pragma once
#include <unordered_map>
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
		IRMethod* GetMethod(std::string name);
		IRDataField* GetDataField(std::string name);
		void ShowAllReflectedData();

	protected:
		std::unordered_map<std::string, IRDataField*> dataFields_;
		std::unordered_map<std::string, IRMethod*> methods_;
	};
}
