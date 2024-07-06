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
			result += "\tAddDataField(\"" + dataField->GetName() + "\",new ccrt::RDataField<" + dataField->GetType() + ">(" + AccessSpecifierToString(dataField->GetAccessSpecifier()) + ", \"" + dataField->GetName() + "\", " + dataField->GetName() + "));\n";
		}
		for (auto method : cppClass->GetMethods())
		{
			result += "\tAddMethod(\"" + method->GetName() + "\", ccrt::RMethod<" + method->GetReturnType();
			for (auto argument : method->GetArguments())
			{
				result += "," + argument;
			}
			result += ">::Create<" + cppClass->GetName() + ",&" + cppClass->GetName() + "::" + method->GetName() + ">(this, " + AccessSpecifierToString(method->GetAccessSpecifier()) + ", \"" + method->GetName() + "\"));\n";
		}
		result += "}\n";

		result += "std::ostream& operator<<(std::ostream& out, "+cppClass->GetName()+"*& reflectedClass)\n";
		result += "{\n";
		result += "\tif(reflectedClass)\n";
		result += "\t{\n";
		result += "\t\tout << reflectedClass->GetID();\n";
		result += "\t}\n";
		result += "\telse\n";
		result += "\t{\n";
		result += "\t\tout << \"nullptr\";\n";
		result += "\t}\n";
		result += "\treturn out;\n";
		result += "}\n\n";

		result += "std::istream& operator>>(std::istream& in, "+ cppClass->GetName() + "*& reflectedClass)\n";
		result += "{\n";
		result += "\tstd::string id;\n";
		result += "\tin >> id;\n";
		result += "\treflectedClass = ccrt::CCRTManager::Find<"+ cppClass->GetName() +">(id);\n";
		result += "\treturn in;\n";
		result += "}\n";

		fileStream << result;
	}
	else
	{
		return -1;
	}
	return 0;
}



