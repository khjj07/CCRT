#include "AccessSpecifier.h"
#include <string>

std::string ccrt::AccessSpecifierToString(ccrt::AccessSpecifier access_specifier)
{
	switch (access_specifier)
	{
	case ccrt::Public:
		return "ccrt::Public";
	case ccrt::Protected:
		return "ccrt::Protected";
	case ccrt::Private:
		return "ccrt::Private";
	default:;
	}
	return {};
}
