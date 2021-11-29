#ifndef _COMMAND_H_
#define _COMMAND_H_
#include "Reciever.h"
#include <iostream>
using namespace std;
class Command
{
public:
	virtual ~Command()
	{
		cout<<"</Command>"<<endl;
	}
	virtual void Excute()=0;
protected:
	Command()
	{
		cout<<"<Command>"<<endl;
	}
private:
};
template<class Reciever>
class SimpleCommand:public Command
{
public:
	typedef void(Reciever::*Action)();
	SimpleCommand(Reciever *rev,Action act)
	{
		cout<<"<SimpleCommand>"<<endl;
		_rev=rev;
		_act=act;
	}
	~SimpleCommand()
	{
		cout<<"</SimpleCommand>"<<endl;
	}
	virtual void Excute()
	{
		(_rev->*_act)();
	}
protected:
private:
	Reciever *_rev;
	Action _act;
};
#endif//_COMMAND_H_
