#include "Colleage.h"
#include <iostream>
using namespace std;
Colleage::Colleage()
{
	cout<<"<Colleage>"<<"\t0"<<endl;
}
Colleage::Colleage(Mediator *mdt)
{
	cout<<"<Colleage>"<<"\t1"<<endl;
	this->_mdt=mdt;
}
Colleage::~Colleage()
{
	cout<<"</Colleage>"<<endl;
}
ConcreteColleageA::ConcreteColleageA()
{
	cout<<"<ConcreteColleageA>"<<"\t0"<<endl;
}
ConcreteColleageA::ConcreteColleageA(Mediator *mdt):Colleage(mdt)
{
	cout<<"<ConcreteColleageA>"<<"\t1"<<endl;
}
ConcreteColleageA::~ConcreteColleageA()
{
	cout<<"</ConcreteColleageA>"<<endl;
}
string ConcreteColleageA::GetState()
{
	return _sdt;
}
void ConcreteColleageA::SetState(const string &sdt)
{
	_sdt=sdt;
}
void ConcreteColleageA::Action()
{
	_mdt->DoActionFromAtoB();
	cout<<"State of ConcreteColleageA:"<<this->GetState()<<endl;
}
ConcreteColleageB::ConcreteColleageB()
{
	cout<<"<ConcreteColleageB>"<<"\t0"<<endl;
}
ConcreteColleageB::ConcreteColleageB(Mediator *mdt):Colleage(mdt)
{
	cout<<"<ConcreteColleageB>"<<"\t1"<<endl;
}
ConcreteColleageB::~ConcreteColleageB()
{
	cout<<"</ConcreteColleageB>"<<endl;
}
string ConcreteColleageB::GetState()
{
	return _sdt;
}
void ConcreteColleageB::SetState(const string &sdt)
{
	_sdt=sdt;
}
void ConcreteColleageB::Action()
{
	_mdt->DoActionFromBtoA();
	cout<<"State of ConcreteColleageB:"<<this->GetState()<<endl;
}