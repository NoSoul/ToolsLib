#include "AbstractFactory.h"
#include <iostream>
using namespace std;

int main(int argc,char *argv[])
{
	AbstractFactory *cf1=new ConcreteFactory1();
	AbstractProductA *apa1=cf1->CreateProductA();
	AbstractProductB *apb1=cf1->CreateProductB();
	AbstractFactory *cf2=new ConcreteFactory2();
	AbstractProductA *apa2=cf2->CreateProductA();
	AbstractProductB *apb2=cf2->CreateProductB();
	delete apb2;
	delete apa2;
	delete cf2;
	delete apb1;
	delete apa1;
	delete cf1;
	return 0;
}
