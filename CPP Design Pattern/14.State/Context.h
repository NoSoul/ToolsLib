#ifndef _CONTEXT_H_
#define _CONTEXT_H_
#include "State.h"
class State;
class Context
{
public:
	Context();
	Context(State *state);
	~Context();
	void OperationInterface();
	void OperationChangeState();
protected:
private:
	friend class State;
	bool ChangeState(State *state);
	State *_state;
};
#endif//~_CONTEXT_H_
