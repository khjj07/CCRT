#pragma once
#include "Define.h"
#include "ReflectedClass.h"

UCLASS
class A : public ccrt::ReflectedClass
{
UCLASS_BODY

public:
	UPROPERTY
		int x;
	UPROPERTY
		int y;
	UPROPERTY
		int z;
		int w;

public:
	int Add(int a, int b);
};