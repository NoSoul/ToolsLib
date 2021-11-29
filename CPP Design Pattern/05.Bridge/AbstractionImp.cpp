#include "AbstractionImp.h"
#include <iostream>
using namespace std;
AbstractionImp::AbstractionImp()
{
	cout<<"<AbstractionImp>"<<endl;
}
AbstractionImp::~AbstractionImp()
{
	cout<<"</AbstractionImp>"<<endl;
}
void AbstractionImp::Operation()
{
	cout<<"AbstractionImp...imp.."<<endl;
}
ConcreteAbstractionImpA::ConcreteAbstractionImpA()
{
	cout<<"<ConcreteAbstractionImpA>"<<endl;
}
ConcreteAbstractionImpA::~ConcreteAbstractionImpA()
{
	cout<<"</ConcreteAbstractionImpA>"<<endl;
}
void ConcreteAbstractionImpA::Operation()
{
	cout<<"ConcreteAbstractionImpA...imp..."<<endl;
}
ConcreteAbstractionImpB::ConcreteAbstractionImpB()
{
	cout<<"<ConcreteAbstractionImpB>"<<endl;
}
ConcreteAbstractionImpB::~ConcreteAbstractionImpB()
{
	cout<<"</ConcreteAbstractionImpB>"<<endl;
}
void ConcreteAbstractionImpB::Operation()
{
	cout<<"ConcreteAbstractionImpB...imp..."<<endl;
}