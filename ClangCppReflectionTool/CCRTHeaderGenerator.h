#pragma once
#include "Define.h"
#include "ICppClassData.h"
#include <utility>

namespace ccrt
{
	class CRRTAPI CCRTHeaderGenerator
	{
	public:
		int GenerateCCRTHeader(ICppClassData* cppClass);

	};
}
