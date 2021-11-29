#include "Invoker.h"
#include <iostream>
using namespace std;
Invoker::Invoker(Command *cmd)
{
	cout<<"<Invoker>"<<endl;
	this->_cmd=cmd;
}
Invoker::~Invoker()
{
	cout<<"</Invoker>"<<endl;
}
void Invoker::Invoke()
{
	_cmd->Excute();
}
