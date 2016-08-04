/*
 * ComplexExpression.h
 *
 *  Created on: Jul 24, 2016
 *      Author: andres.echeverry
 */

#ifndef SIMPLEEXPRESSION_H_
#define SIMPLEEXPRESSION_H_

#include<vector>
#include<iostream>
#include"Expression.h"

using namespace std;

class SimpleExpression: public Expression
{
	public:
		virtual Expression* simplify() {return this;};
};

class Integer final: public SimpleExpression
{
	public:
		Integer(int);
		Expression* simplify();
};

class pi final: public SimpleExpression
{
	public:
		pi();
		Expression* simplify();
};

class e final: public SimpleExpression
{
	public:
		e();
		Expression* simplify();
};

#endif /* SIMPLEEXPRESSION_H_ */
