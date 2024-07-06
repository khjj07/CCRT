#include <unordered_map>
#include "Util.h"
#include "CCRTManager.h"

std::unordered_map<std::string,ccrt::IReflectedClass*> ccrt::CCRTManager::reflectedClasses_;

void ccrt::CCRTManager::Register(IReflectedClass* reflectedClass)
{
	std::string guid = GenerateGUID();
	reflectedClass->SetID(guid);
	reflectedClasses_.insert(std::make_pair(guid, reflectedClass));
}


void ccrt::CCRTManager::Initialize()
{
	for (auto reflectedClass : reflectedClasses_)
	{
		reflectedClass.second->ApplyReflectionData();
	}
}
