/*
 * Process_Expression.cpp
 *
 *  Created on: Jul 29, 2016
 *      Author: andres.echeverry
 */
// This Function grabs a list of tokens and
// creates the Expression objects

#include"Token.h"
#include"Expression.h"
#include"SimpleExpression.h"
#include<string>
#include<stdexcept>
#include<list>
#include<sstream>
#include<iostream>
#include<fstream>

using namespace std;

Expression* process_expression(list<Token> tokenList, ofstream &logFile)
{
	list<Token>::iterator iter;
	Expression* result;
	Expression* thisExpression;
	Expression* lastExpression;
	Expression* twoExpressionsBack;
	Expression* threeExpressionsBack;
	Expression* fourExpressionsBack;
	Expression* fiveExpressionsBack;

	// First, lets make sure we have a proper set of operators and
	// numbers:
	logFile << "Begin process_expression:" << endl;

	int numbers = 0, operators = 0, count=0;

	for(iter = (tokenList).begin(); iter != (tokenList).end(); iter++)
	{
		if (iter->isNumber()) numbers++;
		if (iter->isOperator()) operators++;
	}
	if ((numbers-operators) != 1)
	{
		throw runtime_error("Syntax Error.");
	} else
	{
		// go through the tokenList and create Expression Objects
		try
		{
			int beforeOperator = 0;
			for(iter = (tokenList).begin(); iter != (tokenList).end(); iter++)
			{
				int tokenFound = 0;
				if (iter->isNumber())
				{
					if(iter->isPi())
					{
						thisExpression = new pi();
						if ((iter->getString()).at(0)=='-') (thisExpression)->setInternalSign(-1);
						tokenFound++;
					} else
					{
						if(iter->isExp())
						{
							thisExpression = new e();
							if ((iter->getString()).at(0)=='-') (thisExpression)->setInternalSign(-1);
							tokenFound++;
						} else
						{
							int myInt;
							stringstream stream(iter->getString());
							stream >> myInt;
							thisExpression = new Integer(myInt);
							tokenFound++;
						}
					}
					beforeOperator++;
				} // Finished processing Numbers
				else
				{
					if (iter->isOperator())
					{
						if (beforeOperator<2)
						{
							throw runtime_error("Incorrect syntax");
						}

						beforeOperator--;
						if(iter->isPlus())
						{
							thisExpression = new Addition(twoExpressionsBack , lastExpression);
							lastExpression=threeExpressionsBack;
							twoExpressionsBack=fourExpressionsBack;
							threeExpressionsBack = fiveExpressionsBack;
							tokenFound++;
						}
						if(iter->isMinus())
						{
							lastExpression->setSign(-1);
							thisExpression = new Addition(twoExpressionsBack , lastExpression);
							lastExpression=threeExpressionsBack;
							twoExpressionsBack=fourExpressionsBack;
							threeExpressionsBack = fiveExpressionsBack;
							tokenFound++;
						}
						if(iter->isMultiply())
						{
							thisExpression = new Multiplication(twoExpressionsBack , lastExpression);
							lastExpression=threeExpressionsBack;
							twoExpressionsBack=fourExpressionsBack;
							threeExpressionsBack = fiveExpressionsBack;
							tokenFound++;
						}
						if(iter->isDivide())
						{
/*							thisExpression = new Division(twoExpressionsBack , lastExpression);
							lastExpression=threeExpressionsBack;
							twoExpressionsBack=fourExpressionsBack;
							threeExpressionsBack = fiveExpressionsBack;
*/							tokenFound++;
						}
						if(iter->isRt())
						{
							lastExpression->setExponent(1,twoExpressionsBack->getValue());
							thisExpression = lastExpression;
							lastExpression=threeExpressionsBack;
							twoExpressionsBack=fourExpressionsBack;
							threeExpressionsBack = fiveExpressionsBack;
							tokenFound++;
						}
						if(iter->isLog())
						{
	//						thisExpression = new Logarithm(twoExpressionsBack,lastExpression);
							tokenFound++;
						}
						if(iter->isExponentiate())
						{
							list<Expression*>::iterator iterNumerator;
							list<Expression*>::iterator iterDenominator;

							list<Expression*> exponentNumeratorFactors = ((lastExpression)->getNumeratorFactors());
							list<Expression*> exponentDenominatorFactors = ((lastExpression)->getDenominatorFactors());

							iterNumerator = exponentNumeratorFactors.begin();
							int exponentNumerator = (int)(*(iterNumerator))->getValue();
							int exponentDenominator;

							if (!exponentDenominatorFactors.empty())
							{
								iterDenominator = ((lastExpression)->getDenominatorFactors()).begin();

								exponentDenominator = (int)(*(iterDenominator))->getValue();
							} else
							{
								exponentDenominator = 1;
							}
							cout << twoExpressionsBack->toString()<< " is getting the exponent "<< endl;
							twoExpressionsBack->setExponent(exponentNumerator,exponentDenominator);
							delete lastExpression;
							thisExpression = twoExpressionsBack;
							lastExpression=threeExpressionsBack;
							twoExpressionsBack=fourExpressionsBack;
							threeExpressionsBack = fiveExpressionsBack;
							cout << "Finalized assigning exponent" << endl;
							cout <<"The expression is: " << thisExpression->toString()<< endl;
							tokenFound++;
						}

					}
				} // finished processing Operators

				if(tokenFound != 1)
				{
					throw runtime_error("Syntax Error: Cannot process expression");
				}

				fiveExpressionsBack = fourExpressionsBack;
				fourExpressionsBack = threeExpressionsBack ;
				threeExpressionsBack = twoExpressionsBack;
				twoExpressionsBack = lastExpression;
				lastExpression = thisExpression;
			}
		} catch (runtime_error &err)
		{
			throw runtime_error("Invalid arguments");
		}

	} // At this point we have created all the Expression objects;
	cout << "finished reading tokens"<< endl;

	if (result!=NULL)
	{
		cout << "Result was not null"<< endl;
		try
		{
			cout <<"Before simplify, the expression is: " << thisExpression->toString()<< endl;
			cout << "Attempting to simplify Expression" << endl;
			result = (thisExpression->simplify());
			cout << "Apparently simplified expression"<< endl;
		} catch (runtime_error &err)
		{
			return NULL;
		}
	}
	return result;
}




