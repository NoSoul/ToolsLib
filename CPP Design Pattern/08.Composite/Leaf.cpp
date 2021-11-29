#include "Leaf.h"
#include <iostream>
using namespace std;
Leaf::Leaf()
{
	cout<<"<Leaf>"<<endl;
}
Leaf::~Leaf()
{
	cout<<"</Leaf>"<<endl;
}
void Leaf::Operation()
{
	cout<<"Leaf::operation..."<<endl;
}