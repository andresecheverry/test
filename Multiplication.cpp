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
#include<math.h>
#include<cmath>



Multiplication::Multiplication(Expression* a, Expression* b)
{
	Expression::setLeftSide(a);
	Expression::setRightSide(b);
};

list<Expression*> Multiplication::getNumeratorFactors()
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

Expression* Multiplication::simplify()
{
	Expression_math calc;
	(Expression::getLeftSide())->simplify();
	(Expression::getRightSide())->simplify();

	return calc.multiply(Expression::getLeftSide(), Expression::getRightSide());
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

	tempString.append("*");
	tempString.append((Expression::getRightSide())->toString());
	tempString.append(")");
	Expression::setString(tempString);
	return Expression::toString();
};
