#include "Invoker.h"
#include <iostream>
using namespace std;
int main(int argc,char *argv[])
{
	Reciever *rev=new Reciever();
	Command *cmd=new ConcreteCommand(rev);
	Invoker *inv=new Invoker(cmd);
	inv->Invoke();
	delete inv;
	delete cmd;
	delete rev;
	return 0;
}
