#include "AccessSpecifier.h"
#include <string>

std::string ccrt::AccessSpecifierToString(ccrt::AccessSpecifier access_specifier)
{
	switch (access_specifier)
	{
	case ccrt::Public:
		return "public";
	case ccrt::Protected:
		return "protected";
	case ccrt::Private:
		return "private";
	default:;
	}
	return {};
}
