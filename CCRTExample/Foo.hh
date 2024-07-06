#pragma once
#include "Bar.hh"
#include "CCRT.h"

UCLASS
class Foo : public ccrt::ReflectedClass
{
	UCLASS_BODY
public:
	UPROPERTY
		int x = 30;
	UPROPERTY
		int y;
	UPROPERTY
		Bar* bar;
public:
	int Add(int a, int b);
};