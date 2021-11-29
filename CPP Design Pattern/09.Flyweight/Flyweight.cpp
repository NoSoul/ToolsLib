#include "Flyweight.h"
#include <iostream>
using namespace std;
Flyweight::Flyweight(string intrinsicState)
{
	this->_intrinsicState=intrinsicState;
	cout<<"<Flyweight>"<<endl;
}
Flyweight::~Flyweight()
{
	cout<<"</Flyweight>"<<endl;
}
void Flyweight::Operation(const string &extrinsicState)
{
	cout<<"Flyweight::Operation..."<<endl;
}
string Flyweight::GetIntrinsicState()
{
	return this->_intrinsicState;
}
ConcreteFlyweight::ConcreteFlyweight(string intrinsicState):Flyweight(intrinsicState)
{
	cout<<"<ConcreteFlyweight>"<<"\t"<<intrinsicState<<endl;
}
ConcreteFlyweight::~ConcreteFlyweight()
{
	cout<<"</ConcreteFlyweight>"<<endl;
}
void ConcreteFlyweight::Operation(const string &extrinsicState)
{
	cout<<"ConcreteFlyweight::Operation..."<<endl;
}
