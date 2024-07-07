# ClangCppReflectionTool(CCRT)

## 개요
UnrealEngine의 PropertySystem을 참고하여 LLVM lib-clang을 기반으로 한 C++ 구문분석 리플랙션 도구를 개발

## 구현 설명
1. lib-clang의 TranslationUnit을 통해 소스 헤더파일을 분석하고 Clang-AST트리로 토큰화
2. clang_visitChildren 함수를 이용해 재귀적으로 순회하며 CppClassData를 생성
3. 빌드 전 이벤트로 ClangCppHeaderTool.exe를 리플렉션 목표 프로젝트 경로를 인자로 실행하여 Reflection된 정보를 바탕으로 헤더파일(CCRT.h)을 생성
4. CCRTManager에서 각 클래스의 Reflection된 정보를 등록하는 ApplyReflectionData 멤버함수를 호출

## CCRTExample(사용 예시)
* Foo.hh(clang 제약 조건으로 인해 hh 파일형식을 사용)
````C++
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
		Bar* bar; //리플랙션된 클래스에 한해서 UPROPERTY로 사용할 수 있음
public:
	int Add(int a, int b);
};
````

* Foo.cpp
````C++
#include "Foo.hh"

int Foo::Add(int a, int b)
{
	return a+b;
}
````

* Bar.hh
````C++
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
````

* main.cpp(전체)
````C++
#include <iostream>

#include "Bar.hh"
#include "Foo.hh"
#include "Bar.CCRT.h"
#include "Foo.CCRT.h"
#include "CCRT.h"

int main()
{
	ccrt::CCRTManager ccrtManager; //생성된 리플랙션 데이터를 초기화 해주는 역할(A.CCRT.h)

	Foo* foo= new Foo();
	Bar* bar = new Bar();

	ccrtManager.Initialize();  //리플랙션 데이터 초기화(모든 ReflectedClass를 상속받은 클래스 생성자 이후에 호출되어야 함)

	foo->Set("x", 50);
	foo->Set("y", 100);
	std::cout << "foo->Get<int>(\"x\") :" << foo->Get<int>("x") << std::endl << std::endl;
	std::cout << "foo->Get<int>(\"y\") :" << foo->Get<int>("y") << std::endl << std::endl;
	std::cout << "foo->Invoke<int>(\"Add\", 1000, 500) :" << foo->Invoke<int>("Add", 1000, 500) << std::endl << std::endl;

	foo->Set("bar", bar);
	std::cout << "bar->GetID() : "<< bar->GetID() <<std::endl << std::endl;
	std::cout << "foo->bar->GetID() : " << foo->bar->GetID() << std::endl << std::endl;
	std::cout << "foo->Get<Bar*>(\"bar\")->GetID() : " << foo->Get<Bar*>("bar")->GetID() << std::endl << std::endl;

	return 0;
}
````

