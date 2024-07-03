#pragma once
#include "Define.h"
#include "ICppClassData.h"
#include <utility>

namespace ccrt
{
	class CRRTAPI CCRTHeaderGenerator
	{
		using Token = std::pair<std::string, std::string>;
	public:
		int GenerateCCRTHeader(ICppClassData* cppClass);

	};
}
