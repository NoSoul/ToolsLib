#include "Singleton.h"
#include <iostream>
using namespace std;
Singleton *Singleton::_instance=0;
Singleton::Singleton()
{
	cout<<"<Singleton>"<<endl;
}
Singleton::~Singleton()
{
	cout<<"</Singleton>"<<endl;
}
Singleton *Singleton::Instance()
{
	if(_instance==0)
	{
		_instance=new Singleton();
		delete _instance;
		_instance=0;
	}
	return _instance;
}
