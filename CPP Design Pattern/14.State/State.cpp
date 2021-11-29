#include "State.h"
#include <iostream>
using namespace std;
State::State()
{
	cout<<"<State>"<<endl;
}
State::~State()
{
	cout<<"</State>"<<endl;
}
void State::OperationInterface(Context *con)
{
	cout<<"State::OperationInterface..."<<endl;
}
void State::OperationChangeState(Context *con)
{
	cout<<"State::OperationChangeState..."<<endl;
}
bool State::ChangeState(Context *con,State *st)
{
	con->ChangeState(st);
	return true;
}
ConcreteStateA::ConcreteStateA()
{
	cout<<"<ConcreteStateA>"<<endl;
}
ConcreteStateA::~ConcreteStateA()
{
	cout<<"</ConcreteStateA>"<<endl;
}
void ConcreteStateA::OperationInterface(Context *con)
{
	cout<<"ConcreteStateA::OperationInterface..."<<endl;
}
void ConcreteStateA::OperationChangeState(Context *con)
{
	OperationInterface(con);
	this->ChangeState(con,new ConcreteStateB());
}
ConcreteStateB::ConcreteStateB()
{
	cout<<"<ConcreteStateB>"<<endl;
}
ConcreteStateB::~ConcreteStateB()
{
	cout<<"</ConcreteStateB>"<<endl;
}
void ConcreteStateB::OperationInterface(Context *con)
{
	cout<<"ConcreteStateB::OperationInterface..."<<endl;
}
void ConcreteStateB::OperationChangeState(Context *con)
{
	OperationInterface(con);
	this->ChangeState(con,new ConcreteStateA());
}
