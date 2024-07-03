#include "CCRTManager.h"

std::vector<ccrt::IReflectedClass*> ccrt::CCRTManager::classes;

void ccrt::CCRTManager::Register(IReflectedClass* reflectedClass)
{
	classes.push_back(reflectedClass);
}

void ccrt::CCRTManager::Initialize()
{
	for (auto reflectedClass : classes)
	{
		reflectedClass->ApplyReflectionData();
	}
}
