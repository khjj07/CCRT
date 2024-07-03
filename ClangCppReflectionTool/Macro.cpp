#include "Macro.h"

ccrt::Macro::Macro(const MacroBuilder& macroBuilder)
	:type_(macroBuilder.type),
	 line_(macroBuilder.line) {}

unsigned ccrt::Macro::GetLine()
{
	return line_;
}

ccrt::IMacro::Type ccrt::Macro::GetType()
{
	return type_;
}

bool ccrt::Macro::GetFlag()
{
	return flag_;
}

void ccrt::Macro::SetFlag(bool flag)
{
	flag_ = flag;
}
