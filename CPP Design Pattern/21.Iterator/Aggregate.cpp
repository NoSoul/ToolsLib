#include "Aggregate.h"
#include <iostream>
using namespace std;
Aggregate::Aggregate()
{
	cout<<"<Aggregate>"<<endl;
}
Aggregate::~Aggregate()
{
	cout<<"</Aggregate>"<<endl;
}
ConcreteAggregate::ConcreteAggregate()
{
	cout<<"<ConcreteAggregate>"<<endl;
	for(int i=0;i<SIZE;++i)
	{
		_objs[i]=i;
	}
}
ConcreteAggregate::~ConcreteAggregate()
{
	cout<<"</ConcreteAggregate>"<<endl;
}
Iterator *ConcreteAggregate::CreateIterator()
{
	return new ConcreteIterator(this);
}
Object ConcreteAggregate::GetItem(int idx)
{
	if(idx<this->GetSize())
	{
		return _objs[idx];
	}
	return -1;
}
int ConcreteAggregate::GetSize()
{
	return SIZE;
}
