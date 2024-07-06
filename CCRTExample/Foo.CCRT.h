#include "CCRT.h"
#include "Foo.hh"

void Foo::ApplyReflectionData()
{
	AddDataField("x",new ccrt::RDataField<int>(ccrt::Public, "x", x));
	AddDataField("y",new ccrt::RDataField<int>(ccrt::Public, "y", y));
	AddDataField("bar",new ccrt::RDataField<Bar *>(ccrt::Public, "bar", bar));
	AddMethod("Add", ccrt::RMethod<int,int,int>::Create<Foo,&Foo::Add>(this, ccrt::Public, "Add"));
}
std::ostream& operator<<(std::ostream& out, Foo*& reflectedClass)
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

std::istream& operator>>(std::istream& in, Foo*& reflectedClass)
{
	std::string id;
	in >> id;
	reflectedClass = ccrt::CCRTManager::Find<Foo>(id);
	return in;
}
