#include "Element.h"
#include <iostream>
using namespace std;
Element::Element()
{
	cout<<"<Element>"<<endl;
}
Element::~Element()
{
	cout<<"</Element>"<<endl;
}
ConcreteElementA::ConcreteElementA()
{
	cout<<"<ConcreteElementA>"<<endl;
}
ConcreteElementA::~ConcreteElementA()
{
	cout<<"</ConcreteElementA>"<<endl;
}
void ConcreteElementA::Accept(Visitor *vis)
{
	cout<<"ConcreteElementA::Accept..."<<endl;
	vis->VisitConcreteElementA(this);
}
ConcreteElementB::ConcreteElementB()
{
	cout<<"<ConcreteElementB>"<<endl;
}
ConcreteElementB::~ConcreteElementB()
{
	cout<<"</ConcreteElementB>"<<endl;
}
void ConcreteElementB::Accept(Visitor *vis)
{
	cout<<"ConcreteElementB::Accept..."<<endl;
	vis->VisitConcreteElementB(this);
}