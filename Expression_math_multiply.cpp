/*
 * Expression_math_multiply.cpp
 *
 *  Created on: Jul 29, 2016
 *      Author: andres.echeverry
 */

#include"Expression.h"
#include"SimpleExpression.h"
#include "Expression_math.h"
#include"IntegerFactorization.h"
#include<iostream>

Expression* multiply_int_int(Integer*, Integer*);
Expression* multiply_two_of_the_same(Expression*, Expression*);
Expression* multiply_two_different(Expression*, Expression*);

pair<int,int> addFactions(pair<int,int> a,pair<int,int> b)
{
	pair<int,int> result;

	result.first = a.first*b.second+b.first*a.second;
	result.second = a.second*b.second;

	cout<<"Going through Add Fractions result.: "<<result.first <<"," << result.second << endl;

	IntegerFactorization* resultNumeratorFactorization = new IntegerFactorization(result.first);
	IntegerFactorization* resultDenominatorFactorization = new IntegerFactorization(result.second);

	vector<pair<int,int>> resultNumeratorFactors = resultNumeratorFactorization->getAllFactors();
	vector<pair<int,int>> resultDenominatorFactors = resultDenominatorFactorization->getAllFactors();

	vector<pair<int,int>>::iterator iterNumeratorFactors;
	vector<pair<int,int>>::iterator iterDenominatorFactors;

	int numerator=0;
	int denominator=1;

	for(iterNumeratorFactors = resultNumeratorFactors.begin(); iterNumeratorFactors!=resultNumeratorFactors.end(); iterNumeratorFactors++)
	{
		cout<< "Going through Add Fractions: Numerator Factor: " << (*iterNumeratorFactors).first << "^" << (*iterNumeratorFactors).second<< endl;

		numerator = 1;

		for(iterDenominatorFactors = resultDenominatorFactors.begin(); iterDenominatorFactors!=resultDenominatorFactors.end(); iterDenominatorFactors++)
		{
			cout<< "Going through Add Fractions: Denominator Factor: " << (*iterDenominatorFactors).first << "^" << (*iterDenominatorFactors).second<< endl;
			denominator =1;
			if((*iterNumeratorFactors).first == (*iterDenominatorFactors).first)
			{// shared factor is found
				cout << "shared factor found: " << (*iterNumeratorFactors).first << endl;

				if((*iterNumeratorFactors).second >= (*iterDenominatorFactors).second)
				{	// subtract denominator exponent from numerator
					(*iterNumeratorFactors).second = (*iterNumeratorFactors).second - (*iterDenominatorFactors).second;

					// remove the factor from the denominator
					(*iterDenominatorFactors).first = 1;
					(*iterDenominatorFactors).second = 1;
					numerator = numerator*pow((*iterNumeratorFactors).first,(*iterNumeratorFactors).second);
				} else
				{// subtract numerator exponent from denominator
					(*iterDenominatorFactors).second = -(*iterNumeratorFactors).second + (*iterDenominatorFactors).second;

					// remove the factor from the numerator
					(*iterNumeratorFactors).first = 1;
					(*iterNumeratorFactors).second = 1;
					denominator = denominator*pow((*iterDenominatorFactors).first,(*iterDenominatorFactors).second);
				}
			}
		} // ended going through the denominator factors
	} // at this point the numerator and denominator factors are ready

	for(iterNumeratorFactors = resultNumeratorFactors.begin(); iterNumeratorFactors!=resultNumeratorFactors.end(); iterNumeratorFactors++)
	{
		numerator = numerator*pow((*iterNumeratorFactors).first,(*iterNumeratorFactors).second);
	}

	for(iterDenominatorFactors = resultDenominatorFactors.begin(); iterDenominatorFactors!=resultDenominatorFactors.end(); iterDenominatorFactors++)
	{
		denominator = denominator*pow((*iterDenominatorFactors).first,(*iterDenominatorFactors).second);
	}
	cout << "addFaction has added: " << a.first <<","<< a.second <<" and " << b.first << ","<< b.second <<endl;
	cout << "numerator: " << numerator << " and denominator: " << denominator << endl;

	result.first=numerator;
	result.second=denominator;

	return result;
}

Expression* multiply_int_int(Integer* a, Integer* b)
{
	int temp;
	bool sameExponent;
	Expression* product;

	cout<< "comparing exponents: "<< a->getExponentNumerator() << ","<< a->getExponentDenominator() << endl;
	cout<< "comparing exponents: "<< b->getExponentNumerator() << ","<< b->getExponentDenominator() << endl;

	double aExponent = ((double)(a->getExponentNumerator())/(double)(a->getExponentDenominator()));
	double bExponent = ((double)(b->getExponentNumerator())/(double)(b->getExponentDenominator()));

	sameExponent = (fabs(aExponent - bExponent)<0.000001);

	if (sameExponent)
	{
		cout << "both multiplication factors have same exponent" << endl;
		temp = (a->getBaseInt())*a->mySign()*(b->getBaseInt())*b->mySign();
		product = new Integer(temp);
		product->setExponent(a->getExponentNumerator(),a->getExponentDenominator());
		product = product->simplify();
	} else
	{// two integers have different exponents
		if(fabs(a->getBaseInt())==fabs(b->getBaseInt()))
		{// but they share the same base
			cout << "both multiplication factors have diff exponent but same base" << endl;
			int newInternalSign = (int)(fabs(a->getValue()*b->getValue())/(a->getValue()*b->getValue())+0.01);
			int newExternalSign = a->mySign()*b->mySign()*newInternalSign;

			int temp = fabs(a->getBaseInt())*newExternalSign;
			product = new Integer (temp);

			pair<int,int> exponent1 = {a->getExponentNumerator(),a->getExponentDenominator()};
			pair<int,int> exponent2 = {b->getExponentNumerator(),b->getExponentDenominator()};

			pair<int,int> newExponent = addFactions(exponent1,exponent2);

			product->setExponent(newExponent.first,newExponent.second);
			product = product->simplify();
		}
		else
		{ // they do not share neither exponent nor base
			cout << "multiplication factors have diff exponent and diff base" << endl;
			product = new Multiplication(a,b);

			double aValue = pow((a->getValue()*a->mySign()),(((double)a->getExponentNumerator())/(double)a->getExponentDenominator()));
			double bValue = pow((b->getValue()*b->mySign()),(((double)b->getExponentNumerator())/(double)b->getExponentDenominator()));
			product->setValue(aValue*bValue);
		}
	}
	return product;
}

Expression* multiply_two_of_the_same(Expression* a, Expression* b)
{
	Expression* product;

	pair<int,int> exponent1 = {a->getExponentNumerator(),a->getExponentDenominator()};
	pair<int,int> exponent2 = {b->getExponentNumerator(),b->getExponentDenominator()};

	pair<int,int> newExponent = addFactions(exponent1,exponent2);

	product = a;
	delete b;

	product->setExponent(newExponent.first,newExponent.second);
	product = product->simplify();

	return product;
}

Expression* multiply_two_different(Expression* a, Expression* b)
{
	Expression* product = new Multiplication(a,b);
	return product;
}

Expression* Expression_math::multiply(Expression* a, Expression* b)
{
	Expression* product;
	bool foundType=false;

	if(dynamic_cast<Integer*>(a)!=NULL)
	{ // a is an integer

		foundType =true;

		if(dynamic_cast<Integer*>(b) !=NULL)
		{ // b is an integer
			cout <<"found two ints, trying to multiply them" << endl;
			product = multiply_int_int(dynamic_cast<Integer*>(a),dynamic_cast<Integer*>(b));
		} else
		{
			product = multiply_two_different(a,b);
		}
	}
	if(dynamic_cast<pi*>(a) != NULL)
	{// a is pi
		foundType=true;

		if(dynamic_cast<pi*>(b) != NULL)
		{// b is pi
			product = multiply_two_of_the_same(a,b);
		} else
		{
			product = multiply_two_different(a,b);
		}
	}

	if(dynamic_cast<e*>(a) != NULL)
	{// a is e
		foundType=true;
		if(dynamic_cast<e*>(b) != NULL)
		{// b is e
			product = multiply_two_of_the_same(a,b);
		} else
		{
			product = multiply_two_different(a,b);
		}
	}

	if (foundType==false)
	{
		product = multiply_two_different(a,b);
	}

	return product;
};


