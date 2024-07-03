#pragma once
#include <string>

namespace ccrt
{
	//접근 지정자
	enum AccessSpecifier
	{
		Public,
		Protected,
		Private
	};

	std::string AccessSpecifierToString(AccessSpecifier access_specifier);
	
}
