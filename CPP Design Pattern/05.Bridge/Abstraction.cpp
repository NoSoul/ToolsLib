#include "Abstraction.h"
#include <iostream>
using namespace std;
Abstraction::Abstraction()
{
	cout<<"<Abstraction>"<<endl;
}
Abstraction::~Abstraction()
{
	cout<<"</Abstraction>"<<endl;
}
RefinedAbstraction::RefinedAbstraction(AbstractionImp *imp)
{
	_imp=imp;
	cout<<"<RefinedAbstraction>"<<endl;
}
RefinedAbstraction::~RefinedAbstraction()
{
	cout<<"</RefinedAbstraction>"<<endl;
}
void RefinedAbstraction::Operation()
{
	_imp->Operation();
}
