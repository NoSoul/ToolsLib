#ifndef _CONTEXT_H_
#define _CONTEXT_H_
#include "Strategy.h"
class Strategy;
class Context
{
public:
	Context(Strategy *stg);
	~Context();
	void DoAction();
protected:
private:
	Strategy *_stg;
};
#endif//~_CONTEXT_H_
