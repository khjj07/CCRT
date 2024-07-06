#include <iostream>

#include "Bar.hh"
#include "Foo.hh"
#include "Bar.CCRT.h"
#include "Foo.CCRT.h"
#include "CCRT.h"

int main()
{
	ccrt::CCRTManager ccrtManager; //생성된 리플랙션 데이터를 초기화 해주는 역할(A.CCRT.h)

	Foo* foo= new Foo();
	Bar* bar = new Bar();

	ccrtManager.Initialize();  //리플랙션 데이터 초기화(모든 생성자 이후 호출되어야 함)

	foo->Set("x", 50);
	foo->Set("y", 100);
	std::cout << "foo->Get<int>(\"x\") :" << foo->Get<int>("x") << std::endl << std::endl;
	std::cout << "foo->Get<int>(\"y\") :" << foo->Get<int>("y") << std::endl << std::endl;
	std::cout << "foo->Invoke<int>(\"Add\", 1000, 500) :" << foo->Invoke<int>("Add", 1000, 500) << std::endl << std::endl;

	foo->Set("bar", bar);
	std::cout << "bar->GetID() : "<< bar->GetID() <<std::endl << std::endl;
	std::cout << "foo->bar->GetID() : " << foo->bar->GetID() << std::endl << std::endl;
	std::cout << "foo->Get<Bar*>(\"bar\")->GetID() : " << foo->Get<Bar*>("bar")->GetID() << std::endl << std::endl;

	return 0;
}