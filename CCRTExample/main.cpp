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