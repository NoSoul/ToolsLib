#ifndef _TEMPLATE_H
#define _TEMPLATE_H
class AbstractClass
{
public:
	virtual ~AbstractClass();
	void TemplateMethod();
protected:
	AbstractClass();
	virtual void PrimitiveOperation1()=0;
	virtual void PrimitiveOperation2()=0;
private:
};
class ConcreteClass1:public AbstractClass
{
public:
	ConcreteClass1();
	~ConcreteClass1();
protected:
	void PrimitiveOperation1();
	void PrimitiveOperation2();
private:
};
class ConcreteClass2:public AbstractClass
{
public:
	ConcreteClass2();
	~ConcreteClass2();
protected:
	void PrimitiveOperation1();
	void PrimitiveOperation2();
private:
};
#endif//~_TEMPLATE_H
