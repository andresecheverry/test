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

list<Expression*> Expression::getFactors()
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
	if (!(dynamic_cast<Multiplication*>(this) !=NULL) && (this->getExponentNumerator() <0))
	{// this is NOT a multiplication expression
		// but it has a negative exponent, therefore
		// build the fraction for display
//		tempString.insert(0,"(1/");
//		tempString.append(")");
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

			read << (this->exponentNumerator); // removed abs from here
			exponentString.append(read.str());
			exponentString.append("/");

			ostringstream read2;

			read2 << this->exponentDenominator;
			exponentString.append(read2.str());
			exponentString.append(")");
		} else
		{
			ostringstream read;
			read << (this->exponentNumerator); // removed abs from here
			exponentString.append(read.str());
		}
	}
	return exponentString;

};

Expression* Expression::simplify()
{
	cout << "ERROR: Main expression Object trying to Simplify" << endl;
	throw runtime_error("Main expression Object trying to Simplify");
	return this;
}

