#include "Factory.h"
#include <iostream>
using namespace std;
int main(int argc,char *argv[])
{
	Factory *fac=new ConcreteFactory();
	Product *p=fac->CreateProduct();
	delete p;
	delete fac;
	return 0;
}
