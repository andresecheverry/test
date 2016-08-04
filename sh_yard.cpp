/*
 * sya.cpp
 *
 *  Created on: Jun 25, 2016
 *      Author: andres.echeverry
 */


#include<iostream>
#include<vector>
#include<list>
#include<stdexcept>
#include"Token.h"

using namespace std;

int tokenize(string, list<Token>*);
int interpretNegatives(list<Token>*);
Token readToken(vector<char>, int*);
bool sameToken(char, char);

list<Token> sh_yard(string input)
{
	// Created a list of tokens in the heap
	// so it can be used by all the functions
	// here.

	list<Token>* tokenList = new list<Token>;

	int tokenizeOutcome, interpretTokens;

	tokenizeOutcome = tokenize(input, tokenList);

	interpretTokens = interpretNegatives(tokenList);

	list<Token> outputQueue;
	list<Token> stack;

	list<Token>::iterator it;

	// Run Shunting-yard Algorithm per Wikipedia Reference Given

	for(it = (*tokenList).begin(); it != (*tokenList).end(); it++)
	{
		if ((*it).isNumber() || it->isAns()) (outputQueue).push_back(*it);
		if ((*it).isFunction()) (stack).push_front(*it);
		if ((*it).isOperator())
		{
			list<Token>::iterator stack_it = stack.begin();

			if (stack_it != stack.end() && stack_it->isOperator())
			{
				// two operators in stack, checking precedence

				bool check1, check2;

				check1 = ((*it).isLeftAssociative()) && ((*it).operatorPrecedence() <= (*stack_it).operatorPrecedence()) ;
				check2 = (!(*it).isLeftAssociative()) && ((*it).operatorPrecedence() < (*stack_it).operatorPrecedence()) ;

				while ((*stack_it).isOperator() && (check1 || check2) && stack_it != stack.end())
				{
					// there is another operator at the top of the stack and conditions are met
					// to move operator out of stack

					(outputQueue).push_back(*stack_it);

					// prepare the next one to check conditions again
					stack_it++;
					stack.pop_front();
					check1 = ((*it).isLeftAssociative()) && ((*it).operatorPrecedence() <= (*stack_it).operatorPrecedence()) ;
					check2 = (!(*it).isLeftAssociative()) && ((*it).operatorPrecedence() < (*stack_it).operatorPrecedence()) ;
				}
			}
			(stack).push_front(*it);
		}

		if ((*it).isLeftParenthesis()) (stack).push_front(*it);
		if ((*it).isRightParenthesis())
		{

			list<Token>::iterator stack_it = stack.begin();

			if (stack_it != stack.end())
			{

				bool foundLeftParenthesis = false;

				while(!(stack_it->isLeftParenthesis()) && stack_it != stack.end())
				{
					(outputQueue).push_back(*stack_it);
					stack_it++;
					stack.pop_front();
				}

				if (stack_it->isLeftParenthesis() && stack_it != stack.end())
				{
					stack_it++;
					stack.pop_front();
					foundLeftParenthesis = true;
					continue;
				}

				if (stack_it->isFunction() && stack_it != stack.end())
				{
					(outputQueue).push_back(*stack_it);
					stack_it++;
					stack.pop_front();
				}

				if (!foundLeftParenthesis)
				{
					throw runtime_error("Error: unmatched right parenthesis!");
				}
			} else
			{
				throw runtime_error("Error: unmatched right parenthesis!");
			}

		}


/*
// 	 	THIS SECTION WAS USED TO DEBUG

		string outputQueueString("");
		list<Token>::iterator temp_it;

		temp_it = (outputQueue).begin();

		while(temp_it != (outputQueue).end())
		{
			outputQueueString.append(temp_it->getString());
			outputQueueString.append(" ");
			temp_it++;
		}

		string stackString("");

		temp_it = (stack).begin();

		while(temp_it != (stack).end())
		{
			stackString.append(temp_it->getString());
			stackString.append(" ");
			temp_it++;
		}

		cout << "Tokens read: " << count << endl;
		cout << "Output Queue is " << outputQueueString << endl;
		cout << "Stack is " << stackString <<endl;
		cout << "__________________________" << endl;
		count++;
*/

	}// finished reading the  tokens

	if(stack.size()>0) // process the stack
	{

	list<Token>::iterator stack_it = stack.begin();

		// now we proceed to clear out the stack
		while (stack_it != stack.end())
		{
			if (stack_it->isLeftParenthesis() || stack_it->isRightParenthesis())
			{
				// there are leftover parenthesis in the stack;
				throw runtime_error("Error: unmatched left parenthesis");
			} else
			{
				(outputQueue).push_back(*stack_it);
				stack_it++;
				stack.pop_front();
			}

		}
	}
/*	// FINISHED: outputQueue is ready

	list<Token>::iterator iter;
	string outputString("");
	int numbers = 0, operators = 0, count=0;

	for(iter = (outputQueue).begin(); iter != (outputQueue).end(); iter++)
	{
		if (iter->isNumber()) numbers++;
		if (iter->isOperator()) operators++;
		outputString.append(iter->getString());
		outputString.append(" ");
	}
	if ((numbers-operators) != 1)
	{

		outputQueue.begin();

		throw runtime_error("Operator Error.");
	}
*/
	return outputQueue;
}

int tokenize(string input, list<Token>* tokenList)
{
	// This function grabs an input string and creates the
	// token list for it
	// First we convert the input string into a vector<char>

	vector<char> inputVect(input.begin(), input.end());
	vector<char> outputVect;

	// The entire input string will be broken down into multiple
	// token objects that will be strung together
	// as a linked list.

	// The "int i" below is a referenced
	// location that will be used throughout multiple functions
	// as they move through the inputVect string

	int* i = new int(0);

	while (*i<inputVect.size())
	{
		// Grab the inputVect, the current location,
		// and reads the inputVect to
		// create the next Token from it.

		(*tokenList).push_back(readToken(inputVect, i));

		// this process is repeated as many times as
		// it takes to reach the end of the inputVect string
		// NOTE: as you move forward, the *i location
		// is incremented each time you run the readToken function.
	}

	// Now we string tokens that are part of the same expression
	// such as rt and log

	*i = 0;


	return 0;
}

Token readToken(vector<char> inputVect, int* i)
{
	// This function grabs an input char vector and a location i
	// and creates a Token based on the char found at
	// location i (and after)

	vector<char> preToken;
	char thisChar, nextChar;

	while (*i < inputVect.size())
	{
		// Advance until non space char
		if (inputVect[*i] == ' ')
		{
			*i = *i+1;
			continue;
		};

		thisChar = inputVect[*i];

		if((*i+1) < inputVect.size())
		{	// there are more characters left in the string
			// get the next char

			nextChar = inputVect[*i+1];

			if (!sameToken(thisChar, nextChar))
				// next char is NOT part of this Token
				// the preToken while loop needs to end
			{
				preToken.push_back(thisChar);
				*i = *i+1;
				break;
			}
		}
		// add thisChar to the preToken

		preToken.push_back(thisChar);

		*i = *i+1;

		// This loop will continue until you
		// either get to the end of the input string
		// or get to a char that is not part of this
		// token

	}

	Token* token;

	token = new Token(preToken);

	return *token;
}

bool sameToken(char thisChar, char nextChar)
{
	// this function takes two Chars and evaluates
	// whether they are part of the same token or not

	bool sameToken = true;

	if (thisChar < 48 || thisChar > 57) // thisChar is NOT a digit
	{
		vector<char> twoChars;
		twoChars.push_back(thisChar);
		twoChars.push_back(nextChar);

		string charString(twoChars.begin(), twoChars.end());

		if (charString != "rt" &&
			charString != "an" &&
			charString != "ns" &&
			charString != "lo" &&
			charString != "pi" &&
			charString != "og")
		{
//			Two Chars aren't any of the known sequences
			sameToken = false;
		}

	} else // thisChar is a digit
	{
		if(nextChar<48 || nextChar > 57) // nextChar is NOT a digit
		{
			sameToken = false;
		}
	}

	return sameToken;
}
