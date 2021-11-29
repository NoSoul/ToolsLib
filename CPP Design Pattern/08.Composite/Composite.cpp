#include "Composite.h"
#include <iostream>
using namespace std;
Composite::Composite()
{
	cout<<"<Composite>"<<endl;
}
Composite::~Composite()
{
	cout<<"</Composite>"<<endl;
}
void Composite::Operation()
{
	vector<Component*>::iterator comIter;
	for(comIter=comVec.begin();comIter!=comVec.end();++comIter)
	{
		(*comIter)->Operation();
	}
}
void Composite::Add(Component *com)
{
	comVec.push_back(com);
}
void Composite::Remove(Component *com)
{
	comVec.erase(&com);
}
Component *Composite::GetChild(int index)
{
	return comVec[index];
}
