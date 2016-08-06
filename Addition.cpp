/*
 * Addition.cpp
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

Addition::Addition(Expression* a, Expression* b)
{
	Expression::setLeftSide(a);
	Expression::setRightSide(b);
};

string Addition::toString()
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
		tempString.append("+");
		(Expression::getRightSide())->setSign(1);
		Expression::getRightSide()->setValue((double)abs(Expression::getRightSide()->getValue()));
	}
	tempString.append((Expression::getRightSide())->toString());
	tempString.append(")");
	Expression::setString(tempString);
	return Expression::toString();
}

list<Expression*> Addition::getAdditiveTerms()
{
	list<Expression*> additiveTerms;
	if(Expression::getExponentNumerator()!= Expression::getExponentDenominator())
	{
		return (Expression::getAdditiveTerms());
	}
	else
	{
		if (Expression::getLeftSide() != NULL)
		{
			list<Expression*> leftTerms = (Expression::getLeftSide())->getAdditiveTerms();
			additiveTerms.insert( additiveTerms.end(), leftTerms.begin(), leftTerms.end() );
		}
		if (Expression::getRightSide() != NULL)
		{
			list<Expression*> rightTerms = (Expression::getRightSide())->getAdditiveTerms();
			additiveTerms.insert( additiveTerms.end(), rightTerms.begin(), rightTerms.end() );
		}
	}
	return additiveTerms;
};

Expression* Addition::simplify()
{
	Expression_math calc;
	cout<< "I am now proceeding to simplify addition: leftside is: "<< (Expression::getLeftSide())->toString() << " = " << (Expression::getLeftSide())->getValue() << endl;
	Expression::setLeftSide((Expression::getLeftSide())->simplify());
	cout << "Simplified left side to: "<< (Expression::getLeftSide())->toString() << " = " << (Expression::getLeftSide())->getValue() << endl;
	cout<< "I am now proceeding to simplify the right side, it is: "<< (Expression::getRightSide())->toString()  << " = " << (Expression::getRightSide())->getValue() <<  endl;
	Expression::setRightSide((Expression::getRightSide())->simplify());
	cout << "Simplified right side to: "<< (Expression::getRightSide())->toString() << " = " << (Expression::getRightSide())->getValue() << endl;

	cout<< "I am now proceeding to add both sides" << endl;
	Expression* sum = calc.add(Expression::getLeftSide(), Expression::getRightSide());
	cout<< "Sum has been concluded" << endl;


	sum->setExponent(this->getExponentNumerator(), this->getExponentDenominator());
	cout<< "Exponent has been transfered to the sum object" << endl;
	if (Expression::mySign() != 1) sum->setSign(-1);

	if(dynamic_cast<Integer*>(sum)!=NULL)
	{
		//Result is an integer, simplify further
		cout<< "I am now simplifying the Simple Expression further" << endl;
		sum = sum->simplify();
		cout << "dynamic cast is done"<< endl;
	} else
	{ // Complex expression: SET VALUE TO NEW VALUE TAKING INTO ACCOUNT EXPONENT AND SIGN

		double leftValue = (sum->getLeftSide())->getValue()*((sum->getLeftSide())->mySign());
		double rightValue=((sum->getRightSide()))->getValue()*((sum->getRightSide())->mySign());

		double newValue = leftValue+rightValue;

		cout << "New Complex Expression value: " << newValue<< endl;
		cout << "left value was: " << leftValue << endl;
		cout << "right value was: " << rightValue << endl;

		if((sum->getExponentDenominator()%2==0) && (newValue<0))
		{
			cerr<< "Error: cannot take the even root of a negative value" << endl;
			sum=NULL;
			throw runtime_error("Error: cannot take the even root of a negative value");
		} else
		{
			sum->setValue(pow((newValue),(double)sum->getExponentNumerator()/(double)sum->getExponentDenominator()));
		}
	}
	return sum;
};


