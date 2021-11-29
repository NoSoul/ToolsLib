#include "Observer.h"
#include <iostream>
#include <string>
using namespace std;
Observer::Observer()
{
	cout<<"<Observer>"<<endl;
	_st='\0';
}
Observer::~Observer()
{
	cout<<"</Observer>"<<endl;
}
ConcreteObserverA::ConcreteObserverA(Subject *sub)
{
	cout<<"<ConcreteObserverA>"<<endl;
	_sub=sub;
	_sub->Attach(this);
}
ConcreteObserverA::~ConcreteObserverA()
{
	_sub->Detach(this);
	cout<<"</ConcreteObserverA>"<<endl;
}
Subject *ConcreteObserverA::GetSubject()
{
	return _sub;
}
void ConcreteObserverA::PrintInfo()
{
	cout<<"ConcreteObserverA::PrintInfo..."<<_sub->GetState()<<endl;
}
void ConcreteObserverA::Update(Subject *sub)
{
	_st=sub->GetState();
	PrintInfo();
}
ConcreteObserverB::ConcreteObserverB(Subject *sub)
{
	cout<<"<ConcreteObserverB>"<<endl;
	_sub=sub;
	_sub->Attach(this);
}
ConcreteObserverB::~ConcreteObserverB()
{
	_sub->Detach(this);
	cout<<"</ConcreteObserverB>"<<endl;
}
Subject *ConcreteObserverB::GetSubject()
{
	return _sub;
}
void ConcreteObserverB::PrintInfo()
{
	cout<<"ConcreteObserverB::PrintInfo..."<<_sub->GetState()<<endl;
}
void ConcreteObserverB::Update(Subject *sub)
{
	_st=sub->GetState();
	PrintInfo();
}