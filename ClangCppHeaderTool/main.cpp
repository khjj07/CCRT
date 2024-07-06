#include "CCRT.h"


int main(int argc, char* argv[])
{
	ccrt::ClangCppParser parser; //lib-clang ��� CppParser
	ccrt::CCRTHeaderGenerator headerGenerator; //�м��� CppClassData�� �������� Header�� ���� 

	const char* commandLineArgs[] = {
		"-I../ClangCppReflectionTool",
		"-E",
		"-std=c++17"
	}; //lib-clang Translation Arguments

	auto result = parser.GenerateCppClassFromFolder(argv[1], commandLineArgs, 3); // ��� ���Ϸκ��� CppClassData ����

	for (auto cpp_class_data : result)
	{
		headerGenerator.GenerateCCRTHeader(cpp_class_data);
	}

	return 0;
}
