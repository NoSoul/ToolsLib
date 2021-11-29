#include "Context.h"
#include <iostream>
using namespace std;
Context::Context(Strategy *stg)
{
	_stg=stg;
	cout<<"<Context>"<<endl;
}
Context::~Context()
{
	if(!_stg)
	{
		delete _stg;
	}
	cout<<"</Context>"<<endl;
}
void Context::DoAction()
{
	_stg->AlgrithmInterface();
}
