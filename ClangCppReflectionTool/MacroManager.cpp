#include "MacroManager.h"
#include "Macro.h"

void ccrt::MacroManager::AddMacro(std::vector<std::string>&& macroTokens, unsigned line)
{
	MacroBuilder builder;
	builder.SetType(macroTokens[0])
		.SetLine(line);
	macros.push_back(builder.BuildShared());
}

std::shared_ptr<ccrt::IMacro> ccrt::MacroManager::GetCurrentMacro(unsigned line) const
{
	std::shared_ptr<IMacro> currentMacro;
	for (auto macro : macros)
	{
		if(!macro->GetFlag())
		{
			if (macro->GetLine() > line)
			{
				return currentMacro;
			}
			currentMacro = macro;
		}
	}
	return currentMacro;
}
