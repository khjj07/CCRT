#pragma once
#include <string>
#include <vector>
#include "Define.h"
#include "IMacro.h"

namespace ccrt
{
	class MacroManager
	{
	public:
		void AddMacro(std::vector<std::string>&& macroTokens,unsigned line);
		std::shared_ptr<IMacro> GetCurrentMacro(unsigned line) const;
		void Reset();

	public:
		std::vector<std::shared_ptr<IMacro>> macros;
	};
}
