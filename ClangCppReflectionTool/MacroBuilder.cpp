#include "Macro.h"
#include "MacroBuilder.h"

ccrt::IMacro* ccrt::MacroBuilder::Build()
{
	return new Macro(*this);
}

std::shared_ptr<ccrt::IMacro> ccrt::MacroBuilder::BuildShared()
{
	return std::make_shared<Macro>(*this);
}

ccrt::MacroBuilder& ccrt::MacroBuilder::SetType(std::string token)
{
	if(token == "UCLASS")
	{
		type = IMacro::Uclass;
	}
	else if(token == "UPROPERTY")
	{
		type = IMacro::Uproperty;
	}
	return *this;
}

ccrt::MacroBuilder& ccrt::MacroBuilder::SetLine(unsigned line)
{
	this->line = line;
	return *this;
}
