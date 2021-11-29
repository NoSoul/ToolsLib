#include "Component.h"
#include <iostream>
using namespace std;
Component::Component()
{
	cout<<"<Component>"<<endl;
}
Component::~Component()
{
	cout<<"</Component>"<<endl;
}
void Component::Add(const Component &com)
{
	cout<<"Component::Add..."<<endl;
}
void Component::Remove(const Component &com)
{
	cout<<"Component::Remove..."<<endl;
}
Component *Component::GetChild(int index)
{
	return 0;
}
