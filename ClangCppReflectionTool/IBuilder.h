#pragma once
#include "Define.h"

namespace ccrt
{
	template<class T>
	class CRRTAPI IBuilder
	{
	public:
		virtual T* Build() = 0;
	};
}
