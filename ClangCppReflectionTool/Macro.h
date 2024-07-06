#pragma once
#include "IMacro.h"
#include "MacroBuilder.h"

namespace ccrt
{
	class Macro : public IMacro
	{
	public:
		Macro(const MacroBuilder& macroBuilder);

	public:
		unsigned GetLine() override;
		Type GetType() override;
		bool GetFlag() override;
		void SetFlag(bool flag) override;

	private:
		Type type_;
		unsigned line_;
		bool flag_=false;
	};
}
