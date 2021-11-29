#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include "Subject.h"
#include <string>
using namespace std;
typedef string State;
class Subject;
class Observer
{
public:
	virtual ~Observer();
	virtual void Update(Subject *sub)=0;
	virtual void PrintInfo()=0;
protected:
	Observer();
	State _st;
private:
};
class ConcreteObserverA:public Observer
{
public:
	ConcreteObserverA(Subject *sub);
	virtual ~ConcreteObserverA();
	virtual Subject *GetSubject();
	void Update(Subject *sub);
	void PrintInfo();
protected:
private:
	Subject *_sub;
};
class ConcreteObserverB:public Observer
{
public:
	ConcreteObserverB(Subject *sub);
	virtual ~ConcreteObserverB();
	virtual Subject *GetSubject();
	void Update(Subject *sub);
	void PrintInfo();
protected:
private:
	Subject *_sub;
};
#endif//~_OBSERVER_H_
