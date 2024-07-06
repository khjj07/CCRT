#pragma once
#include "Define.h"
#include "ISerializable.h"

namespace ccrt
{
	class IMacro
	{
	public:
		enum Type
		{
			Uclass,
			Uproperty
		};
	public:
		virtual unsigned GetLine() = 0;
		virtual Type GetType() = 0;
		virtual bool GetFlag() = 0;
		virtual void SetFlag(bool flag) = 0;
	};
}
