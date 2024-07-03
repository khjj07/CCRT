#include "ReflectedClass.h"

#include <iostream>
#include "CCRTManager.h"

ccrt::ReflectedClass::ReflectedClass()
{
	CCRTManager::Register(this);
}

ccrt::IRMethod* ccrt::ReflectedClass::GetMethod(std::string name)
{
	return methods_[name];
}

ccrt::IRDataField* ccrt::ReflectedClass::GetDataField(std::string name)
{
	return dataFields_[name];
}

void ccrt::ReflectedClass::ShowAllReflectedData()
{
	std::cout << "DataFields :\n";
	for (auto dataField : dataFields_)
	{
		IRDataField* field = dataField.second;
		std::cout << field->GetType() << " "<<field->GetValue();
	}
}
