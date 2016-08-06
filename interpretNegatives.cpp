/*
 * interpret.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: andres.echeverry
 */

#include<iostream>
#include<vector>
#include<list>
#include <math.h>
#include <string>
#include <sstream>

#include"Token.h"

using namespace std;

int interpretNegatives(list<Token>* tokenList)
{ 	// this function grabs a list of Tokens
	// and interprets it to construct negative
	// numbers as necessary

	list<Token>::iterator it;
	int count =0;
	string priorTokenString;

	for(it = (*tokenList).begin(); it != (*tokenList).end(); it++)
	{
		string tokenString(it->getString());

		// Now deal with first digit being a negative sign

		if(((((((count == 0 ||
				priorTokenString == "(") ||
				priorTokenString == "*") ||
				priorTokenString == "/") ||
				priorTokenString == "^") ||
				priorTokenString == "rt") ||
				priorTokenString == "+")     && (tokenString=="-"))
		{
			// if the next token is a number
			it++;
			if(it->isNumber())
			{	// go back to the negative sign token
				it--;
				// this is a leading negative, erase it
				it = tokenList->erase(it);

				// take the negative sign and append the next number token
				tokenString.append(it->getString());

				vector<char> newChars(tokenString.begin(), tokenString.end());

				it->setChars(newChars);
			}
			// if the next token is a left parenthesis
			if(it->isLeftParenthesis())
			{	// go back to the negative sign token
				it--;
				// this is a leading negative, change it for a new
				// token: {-1}
				tokenString.append("1");
				vector<char> newChars(tokenString.begin(), tokenString.end());
				it->setChars(newChars);
				it->classifyToken();

				// and add the * token
				it++;
				vector<char> input;
				input.push_back('*');

				it == (*tokenList).insert(it, Token(input));
			}
		}

		count = count +1;
		priorTokenString = tokenString;
	}

	return 0;
}


