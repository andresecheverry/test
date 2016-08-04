/*
 * token.h
 *
 *  Created on: Jun 25, 2016
 *      Author: andres.echeverry
 */

#ifndef TOKEN_H_
#define TOKEN_H_
#include<vector>
#include<iostream>

using namespace std;

class Token
{
	public:
		Token(vector<char> input);
		~Token();
		bool isAns();
		bool isPi();
		bool isExp();
		bool isNumber();
		bool isFunction();
		bool isRt();
		bool isLog();
		float getBase(); // used for rt and log
		void setBase(float);
		bool isOperator();
		int operatorPrecedence();
		bool isLeftAssociative();
		bool isLeftParenthesis();
		bool isRightParenthesis();
		string getString();
		void setChars(vector<char> newChars);
		void print();
		int size();
		void classifyToken();
		bool isPlus();
		bool isMinus();
		bool isMultiply();
		bool isDivide();
		bool isExponentiate();


	private:
		vector<char> token;
		int type;
		bool _isPi;
		bool _isExp;
		bool _isAns;
		bool _isNumber;
		bool _isFunction;
		bool _isRt;
		bool _isLog;
		float base; // used for rt and log bases
		bool _isOperator;
		int _operatorPrecedence;
		bool _isLeftAssociative;
		bool _isLeftParenthesis;
		bool _isRightParenthesis;
		bool _isPlus;
		bool _isMinus;
		bool _isMultiply;
		bool _isDivide;
		bool _isExponentiate;

};

#endif /* TOKEN_H_ */
