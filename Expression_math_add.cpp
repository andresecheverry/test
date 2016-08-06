/*
 * Expression_math.cpp
 *
 *  Created on: Jul 24, 2016
 *      Author: andres.echeverry
 */

#include"Expression.h"
#include"SimpleExpression.h"
#include "Expression_math.h"
#include<cmath>

using namespace std;

Integer* sum_int_int(Integer*, Integer*);
Expression* sum_two_of_the_same(Expression*, Expression*);
Addition* sum_two_different(Expression*, Expression*);

Integer* sum_int_int(Integer* a, Integer* b)
{
	int temp;
	temp = (a->getValue())*a->mySign()+(b->getValue())*b->mySign();
	Integer* sum = new Integer(temp);
	return sum;
};

Expression* sum_two_of_the_same(Expression* a, Expression* b)
{
	Expression* sum;

	int quantity = a->getInternalSign()*a->mySign()+a->getInternalSign()*a->mySign();

	Integer* qty = new Integer(quantity);

	if (quantity<0) b->setSign(-1);
	else b->setSign(1);

	sum = new Multiplication(qty,b);

	return sum;
};

Addition* sum_two_different(Expression* a, Expression* b)
{
	Addition* sum;
	list<Expression*> additiveTerms_a = a->getAdditiveTerms();
	list<Expression*> additiveTerms_b = b->getAdditiveTerms();
	Expression_math calc;

	list<Expression*>::iterator iter_a;
	list<Expression*>::iterator iter_b;

	for(iter_a= additiveTerms_a.begin(); iter_a!= additiveTerms_a.end(); iter_a++)
	{
		for(iter_b = additiveTerms_b.begin(); iter_b!= additiveTerms_b.end(); iter_b++)
		{
			if(additiveTerms_a.size()==1 && additiveTerms_b.size()==1) continue;
			else
			{
				bool sameExponent;

				double aExponent = (double)((a->getExponentNumerator())/(a->getExponentDenominator()));
				double bExponent = (double)((b->getExponentNumerator())/(b->getExponentDenominator()));
				sameExponent = (aExponent == bExponent);

				if (sameExponent)
				{
					Expression* temp = calc.add(*(iter_a),*(iter_b));

					SimpleExpression* simpleExp = dynamic_cast<SimpleExpression*>(temp);
					Multiplication* multipExp = dynamic_cast<Multiplication*>(temp);

					if(simpleExp !=NULL || multipExp != NULL)
					{// term from a matches term b, remove additive terms from BOTH a and b
						iter_a = additiveTerms_a.erase(iter_a);
						iter_b = additiveTerms_b.erase(iter_b);
						iter_a--;
						iter_b--;
					}
					if(simpleExp!=NULL)
					{// replace with single additive term into a
						additiveTerms_a.push_back(simpleExp);
					}

					if(multipExp!=NULL)
					{// term from a matches term b
						additiveTerms_a.push_back(multipExp);
					}
				}
			}
		}
	}
	// at the end of this loop, we have additiveTerms_a and b consolidated
		// we can now build the addition objects.

	list<Expression*>::iterator iter_c;
	list<Expression*>::iterator iter_d;
	Expression* last;

	int count = 0;

	for(iter_c= additiveTerms_a.begin(); iter_c!= additiveTerms_a.end(); iter_c++)
	{
		count++;
		if(count==1) // first term
		{
			last = *(iter_c);
			continue;
		} else //
		{
			double leftValue = last->getValue()*(last->mySign());
			double rightValue=(*(iter_c))->getValue()*(*(iter_c))->mySign();

			last = new Addition(last,*(iter_c));

			double newValue = leftValue+rightValue;

			last->setValue((newValue));

		}
	}

	for(iter_d= additiveTerms_b.begin(); iter_d!= additiveTerms_b.end(); iter_d++)
	{
		count++;
		if(count==1) // first term
		{
			last = *(iter_d);
			continue;
		} else //
		{
			double leftValue = last->getValue()*(last->mySign());
			double rightValue=(*(iter_d))->getValue()*(*(iter_d))->mySign();

			last = new Addition(last,*(iter_d));

			double newValue = leftValue+rightValue;

			last->setValue((newValue));

		}
	}

	// now consolidate fractions

	list<Expression*>::iterator iter_leftFactors;
	list<Expression*>::iterator iter_rightFactors;

	list<Expression*> factorsLeftSide = (last->getLeftSide())->getFactors();
	list<Expression*> factorsRightSide = (last->getRightSide())->getFactors();

	iter_leftFactors = factorsLeftSide.begin();
	iter_rightFactors = factorsRightSide.begin();



	Addition* newAddition = dynamic_cast<Addition*>(last);
	return newAddition;
};

Expression* Expression_math::add(Expression* a, Expression* b)
{
	Expression* sum;
	bool foundType=false;
	bool sameExponent;

	double aExponent = ((double)(a->getExponentNumerator())/(double)(a->getExponentDenominator()));
	double bExponent = ((double)(b->getExponentNumerator())/(double)(b->getExponentDenominator()));

	double diff = aExponent-bExponent;

	sameExponent = ((std::abs(diff)) < 0.0001);

	if(dynamic_cast<Integer*>(a) != NULL && a->getExponentDenominator()==1)
	{ // a is an integer

		foundType =true;

		if(dynamic_cast<Integer*>(b) != NULL && b->getExponentDenominator()==1)
		{ // b is an integer
			sum = sum_int_int(dynamic_cast<Integer*>(a),dynamic_cast<Integer*>(b));
		} else
		{
			sum = sum_two_different(a,b);
		}
	}
	if(dynamic_cast<pi*>(a) != NULL)
	{// a is pi
		foundType=true;

		if(dynamic_cast<pi*>(b) != NULL && sameExponent)
		{// b is pi of same Exponent
			sum = sum_two_of_the_same(a,b);
		} else
		{
			sum = sum_two_different(a,b);
		}
	}

	if(dynamic_cast<e*>(a) != NULL)
	{// a is e
		foundType=true;
		if(dynamic_cast<e*>(b) != NULL && sameExponent)
		{// b is e with same exponent
			sum = sum_two_of_the_same(a,b);
		} else
		{
			sum = sum_two_different(a,b);
		}
	}

	if (foundType==false)
	{
		sum = sum_two_different(a,b);
	}


	return sum;
};
