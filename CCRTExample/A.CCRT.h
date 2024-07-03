#include "CCRT.h"
#include "A.hh"

void A::ApplyReflectionData()
{
	dataFields_.insert(std::make_pair("x",new ccrt::RDataField<int>("public", x)));
	dataFields_.insert(std::make_pair("y",new ccrt::RDataField<int>("public", y)));
	dataFields_.insert(std::make_pair("z",new ccrt::RDataField<int>("public", z)));
	methods_.insert(std::make_pair("Add",ccrt::RMethod<int,int,int>::from_method<A,&A::Add>(this)));
}
