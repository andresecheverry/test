/*
 * Multiplication.cpp
 *
 *  Created on: Aug 5, 2016
 *      Author: andres.echeverry
 */

#include"Expression.h"
#include"Expression_math.h"
#include <sstream>
#include <string>
#include<stdexcept>
#include<iostream>
//#include<math.h>
#include<cmath>

Multiplication::Multiplication(Expression* a, Expression* b)
{
	Expression::setLeftSide(a);
	Expression::setRightSide(b);
};

string Multiplication::toString()
{
	string tempString = "(";
	tempString.append((Expression::getLeftSide())->toString());
	int rightSideInternalSign=1;

	if(dynamic_cast<SimpleExpression*>(Expression::getRightSide())!=NULL)
	{
		if ((Expression::getRightSide())->getValue()<0) rightSideInternalSign=-1;
	}

	if((Expression::getRightSide())->mySign()*rightSideInternalSign==1)
	{
		(Expression::getRightSide())->setSign(1);
		Expression::getRightSide()->setValue((double)abs(Expression::getRightSide()->getValue()));
	}

	tempString.append("*");

	tempString.append((Expression::getRightSide())->toString());
	tempString.append(")");
	Expression::setString(tempString);
	return Expression::toString();
};

list<Expression*> Multiplication::getFactors()
{
	list<Expression*> factors;

	if (Expression::getLeftSide() != NULL)
	{
		list<Expression*> leftTerms = (Expression::getLeftSide())->getNumeratorFactors();
		factors.insert( factors.end(), leftTerms.begin(), leftTerms.end() );
	}
	if (Expression::getRightSide() != NULL)
	{
		list<Expression*> rightTerms = (Expression::getRightSide())->getNumeratorFactors();
		factors.insert( factors.end(), rightTerms.begin(), rightTerms.end() );
	}

	return factors;

};

list<Expression*> Multiplication::getNumeratorFactors()
{
	list<Expression*> factors = Multiplication::getFactors();

	list<Expression*>::iterator iter;

	for (iter = factors.begin();iter!=factors.end();iter++)
	{
		if((*iter)->getExponentNumerator()<0)
		{
			iter=factors.erase((iter));
			iter--;
		}
	}
	return factors;
};

list<Expression*> Multiplication::getDenominatorFactors()
{
	list<Expression*> factors = Multiplication::getFactors();

	list<Expression*>::iterator iter;

	for (iter = factors.begin();iter!=factors.end();iter++)
	{
		if((*iter)->getExponentNumerator()>=0)
		{
			iter=factors.erase((iter));
			iter--;
		}
	}
	return factors;
};

Expression* Multiplication::simplify()
{
	Expression_math calc;
	Expression::setLeftSide((Expression::getLeftSide())->simplify());
	Expression::setRightSide((Expression::getRightSide())->simplify());

	Expression* product = calc.multiply(Expression::getLeftSide(), Expression::getRightSide());

	return product;
};

