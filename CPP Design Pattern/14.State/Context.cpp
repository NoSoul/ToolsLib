#include "Context.h"
#include <iostream>
using namespace std;
Context::Context()
{
	cout<<"<Context>:0"<<endl;
}
Context::Context(State *state)
{
	this->_state=state;
	cout<<"<Context>:1"<<endl;
}
Context::~Context()
{
	delete _state;
	cout<<"</Context>"<<endl;
}
void Context::OperationInterface()
{
	_state->OperationInterface(this);
}
bool Context::ChangeState(State *state)
{
	delete this->_state;
	this->_state=state;
	return true;
}
void Context::OperationChangeState()
{
	_state->OperationChangeState(this);
}
