#include <iostream>

#include "A.hh"
#include "CCRTHeaderGenerator.h"
#include "CCRTManager.h"
#include "ClangCppParser.h"



int main()
{
	ccrt::ClangCppParser parser; //lib-clang ��� CppParser
	ccrt::CCRTHeaderGenerator headerGenerator; //�м��� CppClassData�� �������� Header�� ���� 
	ccrt::CCRTManager ccrtManager; //������ ���÷��� �����͸� �ʱ�ȭ ���ִ� ����(A.CCRT.h)

	const char* commandLineArgs[] = {
		"-I../ClangCppReflectionTool",
		"-E",
		"-std=c++17"
	}; //lib-clang Translation Arguments

	auto result = parser.GenerateCppClassFromFile("../CCRTExample/A.hh", commandLineArgs,3); // ��� ���Ϸκ��� CppClassData ����

	headerGenerator.GenerateCCRTHeader(result);// CppClassData�� �̿��� Header ����

	A* test= new A();
	ccrtManager.Initialize();  //���÷��� ������ �ʱ�ȭ(��� ������ ���� ȣ��Ǿ�� ��)

	test->GetDataField("x")->SetValue("30"); //�̸����� Ŭ������ ������ ���� ����
	int addResult = test->GetMethod("Add")->Invoke<int>(100, 20); //�̸����� �Լ� ȣ�� ����(Invoke<����Ÿ��>(��������))

	std::cout << "x : " << test->x << std::endl;
	std::cout << "Add Result : " << addResult;

	return 0;
}