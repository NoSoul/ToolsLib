#include "Command.h"
#include <iostream>
using namespace std;
Command::Command()
{
	cout<<"<Command>"<<endl;
}
Command::~Command()
{
	cout<<"</Command>"<<endl;
}
ConcreteCommand::ConcreteCommand(Reciever *rev)
{
	cout<<"<ConcreteCommand>"<<endl;
	this->_rev=rev;
}
ConcreteCommand::~ConcreteCommand()
{
	cout<<"</ConcreteCommand>"<<endl;
}
void ConcreteCommand::Excute()
{
	_rev->Action();
}
