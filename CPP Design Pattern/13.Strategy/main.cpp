#include "Context.h"
#include <iostream>
using namespace std;
int main(int argc,char *argv[])
{
	Strategy *ps=new ConcreteStrategyA();
	Context *pc=new Context(ps);
	pc->DoAction();
	delete pc;
	delete ps;
	ps=new ConcreteStrategyB();
	pc=new Context(ps);
	pc->DoAction();
	delete pc;
	delete ps;
	return 0;
}
