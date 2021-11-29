#include "Proxy.h"
#include <iostream>
using namespace std;
Subject::Subject()
{
	cout<<"<Subject>"<<endl;
}
Subject::~Subject()
{
	cout<<"</Subject>"<<endl;
}
ConcreteSubject::ConcreteSubject()
{
	cout<<"<ConcreteSubject>"<<endl;
}
ConcreteSubject::~ConcreteSubject()
{
	cout<<"</ConcreteSubject>"<<endl;
}
void ConcreteSubject::Request()
{
	cout<<"ConcreteSubject::Request..."<<endl;
}
Proxy::Proxy(Subject *sub)
{
	cout<<"<Proxy>"<<endl;
	_sub=sub;
}
Proxy::~Proxy()
{
	cout<<"</Proxy>"<<endl;
}
void Proxy::Request()
{
	cout<<"Proxy::Request..."<<endl;
	_sub->Request();
}
