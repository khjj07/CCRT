#include "ReflectedClass.h"

#include <assert.h>
#include <iostream>
#include "CCRTManager.h"
#include "RDataField.h"

ccrt::ReflectedClass::ReflectedClass()
{
	CCRTManager::Register(this);
}

void ccrt::ReflectedClass::SetID(std::string id)
{
	this->id = id;
}

std::string ccrt::ReflectedClass::GetID()
{
	return id;
}

ccrt::IRMethod* ccrt::ReflectedClass::GetMethod(std::string name)
{
	return methods_[name];
}

ccrt::IRDataField* ccrt::ReflectedClass::GetDataField(std::string name)
{
	return dataFields_[name];
}

void ccrt::ReflectedClass::AddDataField(std::string name, IRDataField* dataField)
{
	dataFields_.insert(std::make_pair(name,dataField));
}

void ccrt::ReflectedClass::AddMethod(std::string name, IRMethod* method)
{
	methods_.insert(std::make_pair(name,method));
}

void ccrt::ReflectedClass::ShowAllReflectedData()
{
	std::cout << "DataFields :\n";
	for (auto dataField : dataFields_)
	{
		IRDataField* field = dataField.second;
	}
}

void ccrt::ReflectedClass::ApplyReflectionData()
{
	assert(false,"must be reflected");
}
