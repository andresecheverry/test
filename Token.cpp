/*
 * token.cpp
 *
 *  Created on: Jun 25, 2016
 *      Author: andres.echeverry
 */

#include "Token.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Token::Token(vector<char> input){
	token = input;
	classifyToken();
//	cout << "New Token:" << getString() << endl;
//	print();
}

Token::~Token(){
	token.clear();
}

bool Token::isNumber()
{
	return _isNumber;
}

bool Token::isPi()
{
	return _isPi;
}

bool Token::isExp()
{
	return _isExp;
}

bool Token::isAns()
{
	return _isAns;
}

bool Token::isFunction()
{
	return _isFunction;
}

bool Token::isRt()
{
	return _isRt;
}

bool Token::isLog()
{
	return _isLog;
}

float Token::getBase()
{
	return base;
}

void Token::setBase(float x)
{
	this->base = x;
}

bool Token::isOperator()
{
	return _isOperator;
}

void Token::setChars(vector<char> newChars)
{
	token = newChars;
}

int Token::operatorPrecedence()
{
	return _operatorPrecedence;
}

bool Token::isLeftAssociative()
{
	return _isLeftAssociative;
}

bool Token::isLeftParenthesis()
{
	return _isLeftParenthesis;
}

bool Token::isRightParenthesis()
{
	return _isRightParenthesis;
}

string Token::getString()
{
	string str(token.begin(),token.end());
	return str;
}

int Token::size(){
	return token.size();
}

void Token::print(){
	for (vector<char>::const_iterator i = token.begin(); i != token.end(); ++i)
	{
	    cout << *i;
	}
	cout << endl;
    cout << "is Ans: " << _isAns << endl;
	cout << "is Number: " << _isNumber << endl;
    cout << "is Function: " << _isFunction << endl;
    cout << "is Root: " << _isRt << endl;
    cout << "is Log: " << _isLog << endl;
    cout << "is Operator: " << _isOperator << endl;
    cout << "operator precedence: " << _operatorPrecedence << endl;
    cout << "is left associative: " << _isLeftAssociative << endl;
    cout << "is LeftParenthesis: " << _isLeftParenthesis << endl;
    cout << "is RightParenthesis: " << _isRightParenthesis << endl;
    cout << "size: " << token.size() << endl;

}

void Token::classifyToken()
{
	_isAns = false;
	_isPi=false;
	_isExp=false;
	_isNumber = false;
	_isFunction = false;
	_isRt = false;
	_isLog = false;
	_isOperator = false;
	_operatorPrecedence = 0;
	_isLeftAssociative = false;
	_isLeftParenthesis = false;
	_isRightParenthesis = false;
	_isPlus=false;
	_isMinus=false;
	_isMultiply=false;
	_isDivide=false;
	_isExponentiate=false;

	switch (token[0])
	{
		case 40:
			_isLeftParenthesis = true;
			break;

		case 41:
			_isRightParenthesis = true;
			break;

		case 42: // *
			_isOperator = true;
			_operatorPrecedence = 3;
			_isLeftAssociative = true;
			_isMultiply=true;
			break;

		case 43: // +
			_isOperator = true;
			_operatorPrecedence = 2;
			_isLeftAssociative = true;
			_isPlus=true;
			break;

		case 45: // -
			if(token.size()>1)
			{
				if(token[1]>47 && token[1]<58)
				{// this is a negative number
					_isNumber=true;
				} else throw runtime_error("Error: Token not recognized");
			} else
			{
				_isOperator = true;
				_operatorPrecedence = 2;
				_isLeftAssociative = true;
				_isMinus=true;
			}
			break;

		case 47: // "/" division
			_isOperator = true;
			_operatorPrecedence = 3;
			_isLeftAssociative = true;
			_isDivide = true;
			break;

		case 48: // 0
			_isNumber = true;
			break;

		case 49: // 1
			_isNumber = true;
			break;

		case 50: // 2
			_isNumber = true;
			break;

		case 51: // 3
			_isNumber = true;
			break;

		case 52: // 4
			_isNumber = true;
			break;

		case 53: // 5
			_isNumber = true;
			break;

		case 54: // 6
			_isNumber = true;
			break;

		case 55: // 7
			_isNumber = true;
			break;

		case 56: // 8
			_isNumber = true;
			break;

		case 57: // 9
			_isNumber = true;
			break;

		case 94: // ^
			_isOperator = true;
			_operatorPrecedence = 4;
			_isLeftAssociative = false;
			_isExponentiate=true;
			break;

		case 97: // a
			if (token[1] == 110 && token[2] == 115) // ans
			{
				_isAns = true;
				_isNumber = true;
			}
			break;

		case 101: // e
				_isNumber = true;
				_isExp = true;
			break;


		case 112: // pi
			if (token[1] == 105)
			{
				_isNumber = true;
				_isPi = true;
			}
			break;

		case 114: // r
			if (token[1] == 116) // t
			{
//				_isFunction = true;
				_isOperator = true;
				_operatorPrecedence = 4;
				_isLeftAssociative = false;
				_isRt = true;
				base = 0;
			}
			break;


		case 108: // log?
			if (token[1] == 111 && token[2] == 103) // og
			{
//				_isFunction = true;
				_isOperator = true;
				_operatorPrecedence = 4;
				_isLeftAssociative = false;
				_isLog = true;
				base = 0;
			}
			break;

		default:
			throw runtime_error("Error: Token not recognized");
			break;
	}
}

bool Token::isPlus()
{
	return _isPlus;
}

bool Token::isMinus()
{
	return _isMinus;
}

bool Token::isMultiply()
{
	return _isMultiply;
}

bool Token::isDivide()
{
	return _isDivide;

}

bool Token::isExponentiate()
{
	return _isExponentiate;
}



