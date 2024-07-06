#pragma once
#include "Define.h"
#include "CCRT.h"

UCLASS
class Bar : public ccrt::ReflectedClass
{
	UCLASS_BODY
public:
	UPROPERTY
		int a;
	UPROPERTY
		int b;
};
