/*
 * Expression.h
 *
 *  Created on: Jul 24, 2016
 *      Author: andres.echeverry
 */

#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include<list>
#include<iostream>
#include<math.h>

using namespace std;

class Expression
{
	public:

		Expression();
		virtual ~Expression()
		{
			delete leftSide;
			delete rightSide;
		};

		// Calculates the value of the expression.
		virtual double getValue() {return myValue;};

		// Returns the requested operand for this expression component.
		Expression* getLeftSide() {return leftSide;};

		// Returns the requested operand for this expression component.
		Expression* getRightSide() {return rightSide;};

		// Returns the individual multiplicative factors of the expression
		// - only those of a positive power.
		// (Thus, belonging in the numerator if fractional.)
		virtual list<Expression*> getNumeratorFactors();

		virtual list<Expression*> getFactors();

		virtual list<Expression*> getDenominatorFactors();

		// If the expression is the result of addition or subtraction, returns the individual terms
		virtual list<Expression*> getAdditiveTerms();

		// Signals the expression to produce a simplified version
		// of itself put into lowest terms.
		virtual Expression* simplify();

		// Returns a string version of the expression
		virtual string toString();
		string getExponentString();

		// Returns components of the exponent
		int getExponentNumerator() { return exponentNumerator;};
		void setExponent(int a, int b) {
			if (a%b==0)
			{
				exponentNumerator = a/b;
				exponentDenominator = 1;
			} else // exponent is not Rational
			{
				exponentNumerator = a;
				exponentDenominator = b;
			}
		};

		int getExponentDenominator() { return exponentDenominator;};

		void setValue(double a) { myValue = a;};
		void setString(string input){ myString = input;};

		void setLeftSide(Expression* left){ leftSide = left;};
		void setRightSide(Expression* right){ rightSide = right;};
		int mySign() {return _mySign;};
		void setSign(int a){ _mySign = a;};
		int getInternalSign() {return internalSign;};
		void setInternalSign(int a) { internalSign = a;};



	private:
		int internalSign=1;
		Expression* leftSide=NULL;
		Expression* rightSide=NULL;
		list<Expression*> numeratorFactors;
		list<Expression*> denominatorFactors;
		list<Expression*> additiveTerms;
		double myValue;
		string myString;
		int exponentNumerator = 1;
		int exponentDenominator = 1;
		int _mySign=1;
};

class Addition: public Expression
{
	public:
		Addition(Expression* a, Expression* b);
		list<Expression*> getAdditiveTerms();
		Expression* simplify();
		string toString();
};

class Multiplication: public Expression
{
	public:
		Multiplication(Expression* a, Expression* b);
		list<Expression*> getNumeratorFactors();
		list<Expression*> getDenominatorFactors();
		list<Expression*> getFactors();
		Expression* simplify();
		string toString();
};

#endif /* EXPRESSION_H_ */
