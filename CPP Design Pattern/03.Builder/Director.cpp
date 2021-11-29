#include "Director.h"
#include <iostream>
using namespace std;

Director::Director(Builder *bld)
{
	_bld=bld;
	cout<<"<Director>"<<endl;
}
Director::~Director()
{
	cout<<"</Director>"<<endl;
}
void Director::Construct()
{
	Product *p=_bld->GetProduct();
	delete p;
	_bld->BuildPartA("user-defined");
	_bld->BuildPartB("user-defined");
	_bld->BuildPartC("user-defined");
}
