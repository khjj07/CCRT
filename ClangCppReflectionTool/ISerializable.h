#pragma once
#include <sstream>
#include "Define.h"

namespace ccrt
{
	class CRRTAPI ISerializable
	{
	public:
		virtual void Serialize(std::ostringstream& stream) = 0;
		virtual void Deserialize(std::istringstream& stream) = 0;
	};

}
