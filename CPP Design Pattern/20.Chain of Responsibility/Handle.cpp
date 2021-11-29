#include "Handle.h"
#include <iostream>
using namespace std;
Handle::Handle()
{
	cout<<"<Handle>"<<endl;
	_succ=0;
}
Handle::~Handle()
{
	cout<<"</Handle>"<<endl;
}
Handle::Handle(Handle *succ)
{
	this->_succ=succ;
}
void Handle::SetSuccessor(Handle *succ)
{
	_succ=succ;
}
Handle *Handle::GetSuccessor()
{
	return _succ;
}
ConcreteHandleA::ConcreteHandleA()
{
	cout<<"<ConcreteHandleA>"<<"\t0"<<endl;
}
ConcreteHandleA::ConcreteHandleA(Handle *succ):Handle(succ)
{
	cout<<"<ConcreteHandleA>"<<"\t1"<<endl;
}
ConcreteHandleA::~ConcreteHandleA()
{
	cout<<"</ConcreteHandleA>"<<endl;
}
void ConcreteHandleA::HandleRequest()
{
	if(this->GetSuccessor()!=0)
	{
		cout<<"ConcreteHandleA::HandleRequest...Next..."<<endl;
		this->GetSuccessor()->HandleRequest();
	}
	else
	{
		cout<<"ConcreteHandleA::HandleRequest...End..."<<endl;
	}
}
ConcreteHandleB::ConcreteHandleB()
{
	cout<<"<ConcreteHandleB>"<<"\t0"<<endl;
}
ConcreteHandleB::ConcreteHandleB(Handle *succ):Handle(succ)
{
	cout<<"<ConcreteHandleB>"<<"\t1"<<endl;
}
ConcreteHandleB::~ConcreteHandleB()
{
	cout<<"</ConcreteHandleB>"<<endl;
}
void ConcreteHandleB::HandleRequest()
{
	if(this->GetSuccessor()!=0)
	{
		cout<<"ConcreteHandleB::HandleRequest...Next..."<<endl;
		this->GetSuccessor()->HandleRequest();
	}
	else
	{
		cout<<"ConcreteHandleB::HandleRequest...End..."<<endl;
	}
}
