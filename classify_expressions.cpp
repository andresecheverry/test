/*
 * classify_expressions.cpp
 *
 *  Created on: Jul 29, 2016
 *      Author: andres.echeverry
 */

// This function takes expression pointers and returns information
// about their type
#include"Expression.h"
#include"SimpleExpression.h"
#include "Expression_math.h"
#include<string>

using namespace std;

string classify_one(Expression* a)
{
	string a_type;

	if(dynamic_cast<Integer*>(a) != NULL)
	{
		a_type = "Integer";
	}

	if(dynamic_cast<pi*>(a) != NULL)
	{
		a_type ="pi";
	}

	if(dynamic_cast<e*>(a) != NULL)
	{
		a_type="e";
	}

	if(dynamic_cast<Addition*>(a) != NULL)
	{
		a_type="Addition";
	}

	if(dynamic_cast<Multiplication*>(a) != NULL)
	{
		a_type="Multiplication";
	}
}


string classify_two(Expression* a, Expression* b)
{
	string a_type=classify_one(a);
	string b_type=classify_one(b);
	string combined_type;

	a_type.append(",");

	combined_type = a_type.append(b_type);

	return combined_type;
}

