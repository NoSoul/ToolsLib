#ifndef _ADAPTEROBJECT_H_
#define _ADAPTEROBJECT_H_
class Target
{
public:
	Target();
	virtual ~Target();
	virtual void Request();
protected:
private:
};
class Adaptee
{
public:
	Adaptee();
	~Adaptee();
	void SpecificRequest();
protected:
private:
};
class Adapter:public Target
{
public:
	Adapter(Adaptee *ade);
	~Adapter();
	void Request();
protected:
private:
	Adaptee *_ade;
};
#endif//~_ADAPTEROBJECT_H_
