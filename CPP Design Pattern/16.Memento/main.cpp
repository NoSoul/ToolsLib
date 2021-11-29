#include "Memento.h"
#include <iostream>
using namespace std;
int main(int argc,char *argv[])
{
	Originator *o=new Originator();
	o->SetState("old");
	o->PrintState();
	Memento *m=o->CreateMemento();
	o->SetState("new");
	o->PrintState();
	o->RestoreToMemento(m);
	o->PrintState();
	delete m;
	delete o;
	return 0;
}
