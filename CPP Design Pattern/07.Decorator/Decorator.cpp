#include "Decorator.h"
#include <iostream>
using namespace std;
Component::Component()
{
	cout<<"<Component>"<<endl;
}
Component::~Component()
{
	cout<<"</Component>"<<endl;
}
void Component::Operation()
{
	cout<<"Component::Operation..."<<endl;
}
ConcreteComponent::ConcreteComponent()
{
	cout<<"<ConcreteComponent>"<<endl;
}
ConcreteComponent::~ConcreteComponent()
{
	cout<<"</ConcreteComponent>"<<endl;
}
void ConcreteComponent::Operation()
{
	cout<<"ConcreteComponent::Operation..."<<endl;
}
Decorator::Decorator(Component *com)
{
	this->_com=com;
	cout<<"<Decorator>"<<endl;
}
Decorator::~Decorator()
{
	cout<<"</Decorator>"<<endl;
}
void Decorator::Operation()
{
	cout<<"Decorator::Operation..."<<endl;
}
ConcreteDecorator::ConcreteDecorator(Component *com):Decorator(com)
{
	cout<<"<ConcreteDecorator>"<<endl;
}
ConcreteDecorator::~ConcreteDecorator()
{
	cout<<"</ConcreteDecorator>"<<endl;
}
void ConcreteDecorator::AddedBehavior()
{
	cout<<"ConcreteDecorator::AddedBehavior..."<<endl;
}
void ConcreteDecorator::Operation()
{
	_com->Operation();
	this->AddedBehavior();
}
