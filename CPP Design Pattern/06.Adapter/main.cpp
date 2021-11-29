#include "AdapterObject.h"
//#include "AdapterClass.h"
#include <iostream>
using namespace std;
int main(int argc,char *argv[])
{
	Adaptee *ade=new Adaptee;
	Target *adt=new Adapter(ade);
	adt->Request();
	delete adt;
	delete ade;
// 	Adapter *adt=new Adapter;
// 	adt->Request();
// 	delete adt;
	return 0;
}
