#include "Facade.h"
#include <iostream>
using namespace std;
Subsystem1::Subsystem1()
{
	cout<<"<Subsystem1>"<<endl;
}
Subsystem1::~Subsystem1()
{
	cout<<"</Subsystem1>"<<endl;
}
void Subsystem1::Operation()
{
	cout<<"Subsystem1::Operation..."<<endl;
}
Subsystem2::Subsystem2()
{
	cout<<"<Subsystem2>"<<endl;
}
Subsystem2::~Subsystem2()
{
	cout<<"</Subsystem2>"<<endl;
}
void Subsystem2::Operation()
{
	cout<<"Subsystem2::Operation..."<<endl;
}
Facade::Facade()
{
	cout<<"<Facade>"<<endl;
	this->_subs1=new Subsystem1();
	this->_subs2=new Subsystem2();
}
Facade::~Facade()
{
	delete _subs2;
	delete _subs1;
	cout<<"</Facade>"<<endl;
}
void Facade::OperationWrapper()
{
	this->_subs1->Operation();
	this->_subs2->Operation();
}
