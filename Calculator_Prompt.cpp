/*
 * main.cpp
 *
 *  Created on: Jun 25, 2016
 *      Author: andres.echeverry
 */

#include<iostream>
#include<vector>
#include<stdexcept>
#include"Token.h"
#include"Expression.h"
#include"SimpleExpression.h"
#include<list>
#include<sstream>
#include<fstream>
#include<utility>
#include<tuple>

using namespace std;


list<Token> sh_yard(string);
Expression* process_expression(list<Token>, ofstream&);
void displayHelp();
string getInput(bool begining)
{
	string input;
	bool emptyInput = false;
	begining =true;

	do
	{
		cout << endl ;
		if (begining)
		{
			cout << "Please enter new Expression, or enter \"h\" for Help," << endl;
			cout << "\"pe\" to review Previous Expressions and float values, \"quit\" to quit."<< endl<<endl;
		}
		cout << "> ";

		getline(cin, input);

		if (input.empty())
		{
			cout << "No input provided." << endl;
			emptyInput = true;
		} else emptyInput = false;

	} while (emptyInput);

	return input;
}

string getPreviousExpression(vector<pair<string,float> > previousExpressions, ofstream &logFile)
{
	string previousExpression ="()";
	vector<pair<string,float> >::iterator iter;
	int ans;
	string input="";

	int count = 0;

	for(iter = previousExpressions.begin(); iter!=previousExpressions.end(); iter++)
	{
		if (count==0)
		{
			cout << "id\tExpression\t\t\t\tFloating Point Value" << endl;
		}
		count++;
		cout << count << ":\t" << ((*iter).first) << "\t\t = \t\t" << ((*iter).second) << endl;
	}

	if (count == 0) cout << "There are no previous expressions to display"<< endl;
	else
	{
		cout << "Enter the expression number \"ans\" should be set to, " << endl;
		cout << "or type \"back\" to return to the previous menu:" << endl;
		cout << "> ";

		getline(cin, input);

		while (input !="back")
		{
			stringstream stream(input);
			try
			{
				stream >> ans;
				if (ans>=1)
				{
					previousExpression.insert(1,(previousExpressions[ans-1].first));
					input="back";
				}
				else throw runtime_error("Unexpected entry.");
			} catch (runtime_error &err)
			{
				cout << "Unexpected entry. Try again" << endl;
				cout << "> ";
				getline(cin, input);
			}

		}
	}

	return previousExpression;
}

int main()
{
	ofstream logFile;
	logFile.open("Calculator_log.txt", ofstream::app);

	logFile<< "#######################################" << endl;
	logFile<< "#####     Begin new Session.      #####" << endl;
	logFile<< "#######################################" << endl;

	string input;
	string ans="()";
	string previousExpression;
	bool beginning = true;

	Expression* output;

	list<Token> tokenList;

	vector<pair<string,float> > previousExpressions;

	// Collect a string from the console

	input = getInput(beginning);
	beginning = false;


	while (input != "quit")
	{
		if(input == "h") displayHelp();
		else
		{
			int ansAt = input.find("ans");
			if(ansAt != -1)
			{
				// the input string has ans in it, replace it with
				// the current string of ans
				input.erase(ansAt,3);
				input.insert(ansAt,ans);
			}

			if(input == "pe")
			{
				previousExpression = getPreviousExpression(previousExpressions, logFile);
				if (previousExpression!="()")
				{
					ans = previousExpression;
					cout << "The token \"ans\" has been set to: " << previousExpression << endl;
				}
			}
			else
			{ // this is a new expression
				try
				{
					tokenList = sh_yard(input);
					list<Token>::iterator iter=tokenList.begin();

					while(iter!=tokenList.end())
					{
							cout<<iter->getString() << " ";
							iter++;
					}
				cout<< endl;

					output = (process_expression(tokenList, logFile));
					if (output!=NULL)
					{
						pair<string,double> newOutput(output->toString(),output->getValue());
						previousExpressions.push_back(newOutput);
						ans = "(";
						ans.append(output->toString());
						ans.append(")");
						cout << endl << "Result = " << output->toString() << endl;
					} else
					{
						cerr << "Unable to process expression." << endl;
					}

				} catch (runtime_error &err)
				{
					cerr << endl << err.what()<< endl;
				}
			}
		}

		input = getInput(beginning);

	}
	logFile.close();
	return 0;
}

