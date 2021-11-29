#include "Interpret.h"
#include <iostream>
using namespace std;
AbstractExpression::AbstractExpression()
{
	cout<<"<AbstractExpression>"<<endl;
}
AbstractExpression::~AbstractExpression()
{
	cout<<"</AbstractExpression>"<<endl;
}
void AbstractExpression::Interpret(const Context &c)
{
	cout<<"AbstractExpression::Interpret..."<<endl;
}
TerminalExpression::TerminalExpression(const string &statement)
{
	cout<<"<TerminalExpression>"<<endl;
	this->_statement=statement;
}
TerminalExpression::~TerminalExpression()
{
	cout<<"</TerminalExpression>"<<endl;
}
void TerminalExpression::Interpret(const Context &c)
{
	cout<<this->_statement<<"\tTerminalExpression::Interpret..."<<endl;
}
NonterminalExpression::NonterminalExpression(AbstractExpression *expression,int times)
{
	cout<<"<NonterminalExpression>"<<endl;
	this->_expression=expression;
	this->_times=times;
}
NonterminalExpression::~NonterminalExpression()
{
	cout<<"</NonterminalExpression>"<<endl;
}
void NonterminalExpression::Interpret(const Context &c)
{
	for(int i=0;i<_times;++i)
	{
		this->_expression->Interpret(c);
	}
}