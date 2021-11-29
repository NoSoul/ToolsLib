#include "Strategy.h"
#include <iostream>
using namespace std;
Strategy::Strategy()
{
	cout<<"<Strategy>"<<endl;
}
Strategy::~Strategy()
{
	cout<<"</Strategy>"<<endl;
}
void Strategy::AlgrithmInterface()
{
	cout<<"Strategy...AlgrithmInterface."<<endl;
}
ConcreteStrategyA::ConcreteStrategyA()
{
	cout<<"<ConcreteStrategyA>"<<endl;
}
ConcreteStrategyA::~ConcreteStrategyA()
{
	cout<<"</ConcreteStrategyA>"<<endl;
}
void ConcreteStrategyA::AlgrithmInterface()
{
	cout<<"test ConcreteStrategyA..."<<endl;
}
ConcreteStrategyB::ConcreteStrategyB()
{
	cout<<"<ConcreteStrategyB>"<<endl;
}
ConcreteStrategyB::~ConcreteStrategyB()
{
	cout<<"</ConcreteStrategyB>"<<endl;
}
void ConcreteStrategyB::AlgrithmInterface()
{
	cout<<"test ConcreteStrategyB..."<<endl;
}
