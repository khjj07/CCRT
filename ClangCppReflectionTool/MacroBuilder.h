#pragma once
#include "IBuilder.h"
#include "IMacro.h"

namespace ccrt
{
	class CRRTAPI MacroBuilder : IBuilder<IMacro>
	{
	public:
		friend class Macro;
		IMacro* Build() override;
		std::shared_ptr<IMacro> BuildShared();
		MacroBuilder& SetType(std::string token);
		MacroBuilder& SetLine(unsigned line);

	public:
		IMacro::Type type;
		unsigned line;
	};
}

