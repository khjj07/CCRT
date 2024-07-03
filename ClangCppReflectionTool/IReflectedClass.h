#pragma once
#include "Define.h"

namespace ccrt
{
	class CRRTAPI IReflectedClass
	{
	public:
		virtual void ApplyReflectionData() = 0;
	};
}
