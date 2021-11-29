#include "Template.h"
#include <iostream>
using namespace std;
int main(int argc,char *argv[])
{
	AbstractClass *p1=new ConcreteClass1();
	AbstractClass *p2=new ConcreteClass2();
	p1->TemplateMethod();
	p2->TemplateMethod();
	delete p2;
	delete p1;
	return 0;
}
