#include "FlyweightFactory.h"
#include <iostream>
#include <string>
using namespace std;
FlyweightFactory::FlyweightFactory()
{
	cout<<"<FlyweightFactory>"<<endl;
}
FlyweightFactory::~FlyweightFactory()
{
	cout<<"</FlyweightFactory>"<<endl;
}
Flyweight *FlyweightFactory::GetFlyweight(const string &key)
{
	vector<Flyweight*>::iterator it;
	for(it=_fly.begin();it!=_fly.end();++it)
	{
		if((*it)->GetIntrinsicState()==key)
		{
			cout<<"Already created by users..."<<endl;
			return *it;
		}
	}
	cout<<"Not Created..."<<endl;
	Flyweight *fn=new ConcreteFlyweight(key);
	_fly.push_back(fn);
	return fn;
}
void FlyweightFactory::DelFlyweight()
{
	vector<Flyweight*>::iterator it;
	for(it=_fly.begin();it!=_fly.end();++it)
	{
		delete *it;
	}
	return;
}