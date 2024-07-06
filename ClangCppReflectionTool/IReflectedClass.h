#pragma once
#include "Define.h"

namespace ccrt
{
	class IReflectedClass
	{
	public:
		virtual void ApplyReflectionData() = 0;
		virtual void SetID(std::string id) = 0;
		virtual std::string GetID() = 0;
	};
}
