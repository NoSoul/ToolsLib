#include "Context.h"
#include <iostream>
using namespace std;
int main(int argc,char *argv[])
{
	State *st=new ConcreteStateA();
	Context *con=new Context(st);
	con->OperationChangeState();
	con->OperationChangeState();
	con->OperationChangeState();
	delete con;
	return 0;
}
