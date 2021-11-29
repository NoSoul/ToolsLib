#include "Visitor.h"
#include <iostream>
using namespace std;
Visitor::Visitor()
{
	cout<<"<Visitor>"<<endl;
}
Visitor::~Visitor()
{
	cout<<"</Visitor>"<<endl;
}
ConcreteVisitorA::ConcreteVisitorA()
{
	cout<<"<ConcreteVisitorA>"<<endl;
}
ConcreteVisitorA::~ConcreteVisitorA()
{
	cout<<"</ConcreteVisitorA>"<<endl;
}
void ConcreteVisitorA::VisitConcreteElementA(Element *elm)
{
	cout<<"ConcreteVisitorA::VisitConcreteElementA..."<<endl;
}
void ConcreteVisitorA::VisitConcreteElementB(Element *elm)
{
	cout<<"ConcreteVisitorA::VisitConcreteElementB..."<<endl;
}
ConcreteVisitorB::ConcreteVisitorB()
{
	cout<<"<ConcreteVisitorB>"<<endl;
}
ConcreteVisitorB::~ConcreteVisitorB()
{
	cout<<"</ConcreteVisitorB>"<<endl;
}
void ConcreteVisitorB::VisitConcreteElementA(Element *elm)
{
	cout<<"ConcreteVisitorB::VisitConcreteElementA..."<<endl;
}
void ConcreteVisitorB::VisitConcreteElementB(Element *elm)
{
	cout<<"ConcreteVisitorB::VisitConcreteElementB..."<<endl;
}
