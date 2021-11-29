#include "Iterator.h"
#include <iostream>
using namespace std;
Iterator::Iterator()
{
	cout<<"<Iterator>"<<endl;
}
Iterator::~Iterator()
{
	cout<<"</Iterator>"<<endl;
}
ConcreteIterator::ConcreteIterator(Aggregate *ag,int idx)
{
	cout<<"<ConcreteIterator>"<<endl;
	this->_ag=ag;
	this->_idx=idx;
}
ConcreteIterator::~ConcreteIterator()
{
	cout<<"</ConcreteIterator>"<<endl;
}
Object ConcreteIterator::CurrentItem()
{
	return _ag->GetItem(_idx);
}
void ConcreteIterator::First()
{
	_idx=0;
}
void ConcreteIterator::Next()
{
	if(_idx<_ag->GetSize())
	{
		++_idx;
	}
}
bool ConcreteIterator::IsDone()
{
	return (_idx==_ag->GetSize());
}
