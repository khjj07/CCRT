#pragma once
#include <string>
#include <unordered_map>

#include "Define.h"
#include "IReflectedClass.h"

namespace ccrt
{
	class CRRTAPI CCRTManager
	{
	public:
		static void Register(IReflectedClass* reflectedClass);
		template <typename T>
		static T* Find(std::string id);
		void Initialize();


	private:
		static std::unordered_map<std::string, ccrt::IReflectedClass*>  reflectedClasses_;
	};

	template <typename T>
	T* CCRTManager::Find(std::string id)
	{
		return dynamic_cast<T*>(reflectedClasses_.at(id));
	}

	
}
