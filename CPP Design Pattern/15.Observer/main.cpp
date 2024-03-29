#include "Observer.h"
#include <iostream>
using namespace std;
int main(int argc,char *argv[])
{
	ConcreteSubject *sub=new ConcreteSubject();
	Observer *o1=new ConcreteObserverA(sub);
	Observer *o2=new ConcreteObserverB(sub);
	sub->SetState("old");
	sub->Notify();
	sub->SetState("new");
	sub->Notify();
	delete o2;
	delete o1;
	delete sub;
	return 0;
}
