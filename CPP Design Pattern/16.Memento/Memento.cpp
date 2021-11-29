#include "Memento.h"
#include <iostream>
using namespace std;
typedef string State;
Originator::Originator()
{
	cout<<"<Originator>"<<endl;
	_sdt="";
	_mt=0;
}
Originator::~Originator()
{
	cout<<"</Originator>"<<endl;
}
Memento *Originator::CreateMemento()
{
	return new Memento(_sdt);
}
State Originator::GetState()
{
	return _sdt;
}
void Originator::SetState(const State &sdt)
{
	_sdt=sdt;
}
void Originator::PrintState()
{
	cout<<"Originator::PrintState..."<<this->_sdt<<endl;
}
void Originator::SetMemento(Memento *men)
{
	cout<<"Originator::SetMemento..."<<endl;
}
void Originator::RestoreToMemento(Memento *mt)
{
	this->_sdt=mt->GetState();
}
Memento::Memento(const State &sdt)
{
	cout<<"<Memento>"<<endl;
	_sdt=sdt;
}
Memento::~Memento()
{
	cout<<"</Memento>"<<endl;
}
State Memento::GetState()
{
	return _sdt;
}
void Memento::SetState(const State &sdt)
{
	_sdt=sdt;
}
