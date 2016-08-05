/*
 * Expression.cpp
 *
 *  Created on: Jul 24, 2016
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

Expression:: Expression()
{
	numeratorFactors.push_back(this);
	additiveTerms.push_back(this);
}


list<Expression*> Expression::getDenominatorFactors()
{
	return denominatorFactors;
};


list<Expression*> Expression::getNumeratorFactors()
{
	return numeratorFactors;
};

list<Expression*> Expression:: getAdditiveTerms()
{
	return additiveTerms;
};


string Expression::toString()
{
	string tempString = myString;
	if(!(this->exponentNumerator ==1 && this->exponentDenominator==1))
	{
		tempString.insert(0,"(");
		tempString.append(")");
		tempString.append(this->getExponentString());
		if((this->mySign() !=1))
		{
			tempString.insert(0,"-");
		}
	} else
	{
		if(((this->mySign()*this->getInternalSign()) !=1))
		{
			tempString.insert(0,"(");
			tempString.append(")");
			tempString.insert(0,"-");
		}
	}
	return tempString;
};

string Expression::getExponentString()
{
	string exponentString="";
	if(!(this->exponentNumerator ==1 && this->exponentDenominator==1))
	{
		exponentString.append("^");
		if (this->exponentDenominator != 1)
		{
			ostringstream read;   // stream used for the conversion

			exponentString.append("(");

			read << this->exponentNumerator;
			exponentString.append(read.str());
			exponentString.append("/");

			ostringstream read2;

			read2 << this->exponentDenominator;
			exponentString.append(read2.str());
			exponentString.append(")");
		} else
		{
			ostringstream read;
			read << this->exponentNumerator;
			exponentString.append(read.str());
		}
	}
	return exponentString;

};

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

	if((Expression::getRightSide())->mySign()*rightSideInternalSign==1) tempString.append("+");
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
			cerr<< "Error: cannot take the root" << endl;
			sum=NULL;
			throw runtime_error("Error: cannot take the root");
		} else
		{
			sum->setValue(pow((newValue),(double)sum->getExponentNumerator()/(double)sum->getExponentDenominator()));
		}
	}
	return sum;
};

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

Expression* Expression::simplify()
{
	cout << "ERROR: Main expression Object trying to Simplify" << endl;
	throw runtime_error("Main expression Object trying to Simplify");
	return this;
}

