#pragma once
#include <vector>

#include "Define.h"
#include "IReflectedClass.h"

namespace ccrt
{
	class CRRTAPI CCRTManager
	{
	public:
		static void Register(IReflectedClass* reflectedClass);
		void Initialize();


	private:
		static std::vector<IReflectedClass*> classes;
	};
}
