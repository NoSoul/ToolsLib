#include "Mediator.h"
#include <iostream>
using namespace std;
Mediator::Mediator()
{
	cout<<"<Mediator>"<<endl;
}
Mediator::~Mediator()
{
	cout<<"</Mediator>"<<endl;
}
ConcreteMediator::ConcreteMediator()
{
	cout<<"<ConcreteMediator>"<<"\t0"<<endl;
}
ConcreteMediator::ConcreteMediator(Colleage *clgA,Colleage *clgB)
{
	cout<<"<ConcreteMediator>"<<"\t1"<<endl;
	this->_clgA=clgA;
	this->_clgB=clgB;
}
ConcreteMediator::~ConcreteMediator()
{
	cout<<"</ConcreteMediator>"<<endl;
}
void ConcreteMediator::SetConcreteColleageA(Colleage *clgA)
{
	this->_clgA=clgA;
}
void ConcreteMediator::SetConcreteColleageB(Colleage *clgB)
{
	this->_clgB=clgB;
}
Colleage *ConcreteMediator::GetConcreteColleageA()
{
	return _clgA;
}
Colleage *ConcreteMediator::GetConcreteColleageB()
{
	return _clgB;
}
void ConcreteMediator::IntroColleage(Colleage *clgA,Colleage *clgB)
{
	this->_clgA=clgA;
	this->_clgB=clgB;
}
void ConcreteMediator::DoActionFromAtoB()
{
	_clgB->SetState(_clgA->GetState());
}
void ConcreteMediator::DoActionFromBtoA()
{
	_clgA->SetState(_clgB->GetState());
}
