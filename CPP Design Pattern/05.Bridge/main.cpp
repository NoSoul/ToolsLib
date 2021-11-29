#include "Abstraction.h"
#include <iostream>
using namespace std;
int main(int argc,char *argv[])
{
	AbstractionImp *imp=new ConcreteAbstractionImpA();
	Abstraction *abs=new RefinedAbstraction(imp);
	abs->Operation();
	delete abs;
	delete imp;
	imp=new ConcreteAbstractionImpB();
	abs=new RefinedAbstraction(imp);
	abs->Operation();
	delete abs;
	delete imp;
	return 0;
}
