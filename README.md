# ClangCppReflectionTool(CCRT)

## 개요
UnrealEngine의 PropertySystem을 참고하여 LLVM lib-clang을 기반으로 한 C++ 구문분석 리플랙션 도구를 개발

## 구현 설명



## 예시
### 1. Setup
---
* main.cpp
````C++
#include "CCRTHeaderGenerator.h"
#include "CCRTManager.h"
#include "ClangCppParser.h"
#include "A.hh"

int main()
{
  	ccrt::ClangCppParser parser; //lib-clang 기반 CppParser
  	ccrt::CCRTHeaderGenerator headerGenerator; //분석한 CppClassData를 바탕으로 Header를 생성 
  	ccrt::CCRTManager ccrtManager; //생성된 리플랙션 데이터를 초기화 해주는 역할(A.CCRT.h)
  
  	const char* commandLineArgs[] = {
  		"-I../ClangCppReflectionTool",
  		"-E",
  		"-std=c++17"
  	}; //lib-clang Translation Arguments
  
  	auto result = parser.GenerateCppClassFromFile("../CCRTExample/A.hh", commandLineArgs,3); // 헤더 파일로부터 CppClassData 생성
        headerGenerator.GenerateCCRTHeader(result);// CppClassData를 이용해 Header 생성

  	A* test= new A();
  	ccrtManager.Initialize();  //리플랙션 데이터 초기화(모든 생성자 이후 호출되어야 함)
}
````
### 2. UCLASS,UCLASS_BODY,UPROPERTY 매크로를 이용해 Reflection될 Class를 지정할수 있음
---
* A.hh(clang 제약 조건으로 인해 hh 파일형식을 사용)
````C++
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
````


* A.CCRT.h(CCRTHeaderGenerator을 통해 만들어진 헤더파일)
````C++
#include "CCRT.h"
#include "A.hh"

void A::ApplyReflectionData()
{
	dataFields_.insert(std::make_pair("x",new ccrt::RDataField<int>("public", x)));
	dataFields_.insert(std::make_pair("y",new ccrt::RDataField<int>("public", y)));
	dataFields_.insert(std::make_pair("z",new ccrt::RDataField<int>("public", z)));
	methods_.insert(std::make_pair("Add",ccrt::RMethod<int,int,int>::from_method<A,&A::Add>(this)));
}
````


* A.cpp
````C++
#include "A.CCRT.h"

int A::Add(int a, int b)
{
	return a+b;
}
````


### 3. 멤버변수와 멤버함수에 이름을 통해 접근 가능
---
* main.cpp(main문 안쪽)
 ````C++
  A* test= new A();
	ccrtManager.Initialize();  //리플랙션 데이터 초기화(모든 생성자 이후 호출되어야 함)

	test->GetDataField("x")->SetValue("30"); //이름으로 클래스의 변수에 접근 가능
	int addResult = test->GetMethod("Add")->Invoke<int>(100, 20); //이름으로 함수 호출 가능(Invoke<리턴타입>(가변인자))

	std::cout << "x : " << test->x << std::endl;
	std::cout << "Add Result : " << addResult;
````
---
* main.cpp(전체)
````C++
#include <iostream>

#include "A.hh"
#include "CCRTHeaderGenerator.h"
#include "CCRTManager.h"
#include "ClangCppParser.h"



int main()
{
	ccrt::ClangCppParser parser; //lib-clang 기반 CppParser
	ccrt::CCRTHeaderGenerator headerGenerator; //분석한 CppClassData를 바탕으로 Header를 생성 
	ccrt::CCRTManager ccrtManager; //생성된 리플랙션 데이터를 초기화 해주는 역할(A.CCRT.h)

	const char* commandLineArgs[] = {
		"-I../ClangCppReflectionTool",
		"-E",
		"-std=c++17"
	}; //lib-clang Translation Arguments

	auto result = parser.GenerateCppClassFromFile("../CCRTExample/A.hh", commandLineArgs,3); // 헤더 파일로부터 CppClassData 생성

	headerGenerator.GenerateCCRTHeader(result);// CppClassData를 이용해 Header 생성

	A* test= new A();
	ccrtManager.Initialize();  //리플랙션 데이터 초기화(모든 생성자 이후 호출되어야 함)

	test->GetDataField("x")->SetValue("30"); //이름으로 클래스의 변수에 접근 가능
	int addResult = test->GetMethod("Add")->Invoke<int>(100, 20); //이름으로 함수 호출 가능(Invoke<리턴타입>(가변인자))

	std::cout << "x : " << test->x << std::endl;
	std::cout << "Add Result : " << addResult;

	return 0;
}
````

