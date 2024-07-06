#include "CCRT.h"


int main(int argc, char* argv[])
{
	ccrt::ClangCppParser parser; //lib-clang 기반 CppParser
	ccrt::CCRTHeaderGenerator headerGenerator; //분석한 CppClassData를 바탕으로 Header를 생성 

	const char* commandLineArgs[] = {
		"-I../ClangCppReflectionTool",
		"-E",
		"-std=c++17"
	}; //lib-clang Translation Arguments

	auto result = parser.GenerateCppClassFromFolder(argv[1], commandLineArgs, 3); // 헤더 파일로부터 CppClassData 생성

	for (auto cpp_class_data : result)
	{
		headerGenerator.GenerateCCRTHeader(cpp_class_data);
	}

	return 0;
}
