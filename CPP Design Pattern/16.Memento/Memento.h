#ifndef _MEMENTO_H_
#define _MEMENTO_H_
#include <string>
using namespace std;
typedef string State;
class Memento;
class Originator
{
public:
	Originator();
	~Originator();
	Memento *CreateMemento();
	void SetMemento(Memento *men);
	void RestoreToMemento(Memento *mt);
	State GetState();
	void SetState(const State &sdt);
	void PrintState();
protected:
private:
	State _sdt;
	Memento *_mt;
};
class Memento
{
public:
	~Memento();
protected:
private:
	friend class Originator;
	State _sdt;
	Memento(const State &sdt);
	void SetState(const State &sdt);
	State GetState();
};
#endif//~_MEMENTO_H_
