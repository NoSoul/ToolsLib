#include "Reciever.h"
#include <iostream>
using namespace std;
Reciever::Reciever()
{
	cout<<"<Reciever>"<<endl;
}
Reciever::~Reciever()
{
	cout<<"</Reciever>"<<endl;
}
void Reciever::Action()
{
	cout<<"Reciever::Action..."<<endl;
}