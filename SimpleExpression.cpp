/*
 * SimpleExpression.cpp
 *
 *  Created on: Jul 25, 2016
 *      Author: andres.echeverry
 */

#include"SimpleExpression.h"

#include"IntegerFactorization.h"

#include<sstream>
#include<math.h>
#include<cmath>
#include<stdexcept>

Integer::Integer(int a)
{
	Expression::setValue((a));

	ostringstream read;
	read << (Expression::getValue());
	Expression::setString(string(read.str()));
};

pi::pi()
{
	Expression::setValue(M_PI);
	Expression::setString("pi");
};

e::e()
{
	Expression::setValue(exp(1));
	Expression::setString("e");
}

Expression* Integer::simplify()
{

	if (Expression::getExponentDenominator() != 1)
	{ // the exponent is not an integer
		Expression* parent = this;
		if((Expression::getExponentDenominator()%2==0) && (Expression::getValue()<0))
		{
			cerr<< "Error: cannot take the root" << endl;
			throw runtime_error("Error: cannot take the root");
		}

		IntegerFactorization myFactors(abs((int)Expression::getValue()));

		pair<int,int> root = myFactors.getRoot(Expression::getExponentDenominator());

		int outsideTheRoot = root.first;

		int insideTheRoot = root.second;

		if((root.first !=1) && (root.second!=1)) //it simplifies to a multiplication
		{
			cout << "creating new multiplication" << endl;
			// create a new integer with the value outside the root
			Integer* newInteger = new Integer(pow(outsideTheRoot,Expression::getExponentNumerator()));
			cout << "new integer: " << newInteger->toString();
			// change the value of the current integer to the remainder inside the root;
			Expression::setValue(insideTheRoot);

			ostringstream read;
			read << (Expression::getValue());
			Expression::setString(string(read.str()));
			cout << "set new Value inside existing root to: " << Expression::toString();

			Multiplication* newFactor = new Multiplication(newInteger,this);
			cout<< "new multiplication expression: " << newFactor->toString();

			parent = newFactor;
		}
		if(root.first !=1 && root.second==1) //it simplifies to an integer
		{
			cout << "updating integer" << endl;
			// create a new integer with the value outside the root

			int currentSign = 1;
			if(Expression::getValue() < 0) currentSign = -1;

			// change the value of the current integer to the remainder inside the root;
			Expression::setValue(pow(outsideTheRoot*currentSign,Expression::getExponentNumerator()));

			ostringstream read;
			read << (Expression::getValue());
			Expression::setString(string(read.str()));

			Expression::setExponent(1,1);

			cout << "set new Value inside existing root to: " << Expression::toString();

			return parent;
		}

		double newValue=pow(Expression::getValue(), (double)Expression::getExponentNumerator()/(double)Expression::getExponentDenominator());
		Expression::setValue((newValue));
		return parent;
	} else
	{ // the exponent is an integer, perform the exponentiation
		double newValue=pow(Expression::getValue(), Expression::getExponentNumerator());
		Expression::setValue((newValue));
		Expression::setExponent(1,1);

		// update the string
		ostringstream read;
		read << (Expression::getValue());
		Expression::setString(string(read.str()));

		Expression* parent = this;
		return parent;
	}

}

Expression* pi::simplify()
{
		double newValue=pow(M_PI*Expression::getInternalSign(), (double)Expression::getExponentNumerator()/(double)Expression::getExponentDenominator());
		Expression::setValue((newValue));

		int exponent = (double)Expression::getExponentNumerator()/(double)Expression::getExponentDenominator();

		if ((exponent%2)==0)
			Expression::setInternalSign(1);

		Expression* parent = this;
		return parent;
}

Expression* e::simplify()
{
	double newValue=pow(exp(1)*Expression::getInternalSign(), (double)Expression::getExponentNumerator()/(double)Expression::getExponentDenominator());
	Expression::setValue((newValue));

	int exponent = (double)Expression::getExponentNumerator()/(double)Expression::getExponentDenominator();

	if ((exponent%2)==0)
		Expression::setInternalSign(1);

	Expression* parent = this;
	return parent;
}
