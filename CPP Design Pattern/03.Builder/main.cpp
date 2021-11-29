#include "Director.h"
#include <iostream>
using namespace std;

int main(int argc,char *argv[])
{
	Builder *b=new ConcreteBuilder();
	Director *d=new Director(b);
	d->Construct();
	delete d;
	delete b;
    return 0;
}
