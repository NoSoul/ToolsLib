#include "Subject.h"
#include <iostream>
#include <list>
using namespace std;
typedef string State;
Subject::Subject()
{
	cout<<"<Subject>"<<endl;
	_obvs=new list<Observer*>;
}
Subject::~Subject()
{
	delete _obvs;
	cout<<"</Subject>"<<endl;
}
void Subject::Attach(Observer *obv)
{
	_obvs->push_back(obv);
}
void Subject::Detach(Observer *obv)
{
	if(obv!=NULL)
	{
		_obvs->remove(obv);
	}
}
void Subject::Notify()
{
	list<Observer*>::iterator it;
	for(it=_obvs->begin();it!=_obvs->end();++it)
	{
		(*it)->Update(this);
	}
}
ConcreteSubject::ConcreteSubject()
{
	cout<<"<ConcreteSubject>"<<endl;
	_st='\0';
}
ConcreteSubject::~ConcreteSubject()
{
	cout<<"</ConcreteSubject>"<<endl;
}
State ConcreteSubject::GetState()
{
	return _st;
}
void ConcreteSubject::SetState(const State &st)
{
	_st=st;
}
