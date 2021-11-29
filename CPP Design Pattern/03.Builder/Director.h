#ifndef _DIRECTOR_H_
#define _DIRECTOR_H_
#include "Builder.h"
class Builder;
class Director
{
public:
	Director(Builder *bld);
	~Director();
	void Construct();
protected:
private:
	Builder *_bld;
};
#endif//~_DIRECTOR_H_
