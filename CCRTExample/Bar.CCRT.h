#include "CCRT.h"
#include "Bar.hh"

void Bar::ApplyReflectionData()
{
	AddDataField("a",new ccrt::RDataField<int>(ccrt::Public, "a", a));
	AddDataField("b",new ccrt::RDataField<int>(ccrt::Public, "b", b));
}
std::ostream& operator<<(std::ostream& out, Bar*& reflectedClass)
{
	if(reflectedClass)
	{
		out << reflectedClass->GetID();
	}
	else
	{
		out << "nullptr";
	}
	return out;
}

std::istream& operator>>(std::istream& in, Bar*& reflectedClass)
{
	std::string id;
	in >> id;
	reflectedClass = ccrt::CCRTManager::Find<Bar>(id);
	return in;
}
