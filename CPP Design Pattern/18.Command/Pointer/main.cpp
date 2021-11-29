#include "Command.h"
#include <iostream>
using namespace std;
int main(int argc,char *argv[])
{
	Reciever *rev=new Reciever();
	Command *cmd=new SimpleCommand<Reciever>(rev,&Reciever::Action);
	cmd->Excute();
	delete cmd;
	delete rev;
	return 0;
}
