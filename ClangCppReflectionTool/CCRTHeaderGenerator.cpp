#include "CCRTHeaderGenerator.h"
#include <fstream>
#include <vector>
#include <iostream>

#include "CppClassData.h"

int ccrt::CCRTHeaderGenerator::GenerateCCRTHeader(ICppClassData* sourceClass)
{

	CppClassData* cppClass = dynamic_cast<CppClassData*>(sourceClass);

	std::ofstream fileStream(cppClass->GetFileDirectoryPath() + "/" + cppClass->GetName() + ".CCRT.h");


	if (fileStream.is_open())
	{
		std::string result;

		result += "#include \"CCRT.h\"\n";
		result += "#include \"" + cppClass->GetFileName() + "\"\n\n";
		result += "void " + cppClass->GetName() + "::ApplyReflectionData()\n";
		result += "{\n";
		for (auto dataField : cppClass->GetDataFields())
		{
			result += "\tdataFields_.insert(std::make_pair(\"" + dataField->GetName() + "\",new ccrt::RDataField<" + dataField->GetType() + ">(\"" + dataField->GetAccessSpecifier() + "\", " + dataField->GetName() + ")));\n";
		}
		for (auto method : cppClass->GetMethods())
		{
			result += "\tmethods_.insert(std::make_pair(\"" + method->GetName() + "\",ccrt::RMethod<" + method->GetReturnType();
			for (auto argument : method->GetArguments())
			{
				result += "," + argument;
			}
			result += ">::from_method<" + cppClass->GetName() + ",&" + cppClass->GetName() + "::" + method->GetName() + ">(this)));\n";
		}
		result += "}\n";
		fileStream << result;
	}
	else
	{
		return -1;
	}
	return 0;
}



