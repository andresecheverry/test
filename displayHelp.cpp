/*
 * displayHelp.cpp
 *
 *  Created on: Jul 31, 2016
 *      Author: andres.echeverry
 */

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

void displayFile(string);

void displayHelp()
{
	displayFile("Help_Menu.txt");

	int input=0;

	cout << ">";
	cin >> input;
	string lineReturn;

	while ( input != 5)
	{
		switch(input)
		{
			case 1:
				displayFile("QuickStart.txt");
				cin>> lineReturn;
				break;
			case 2:
				displayFile("NumberTypes.txt");
				cin >>lineReturn;
				break;
			case 3:
				displayFile("Operators.txt");
				cin >> lineReturn;
				break;
			case 4:
				displayFile("Examples.txt");
				cin >> lineReturn;
				break;
			case 5:
				break;
			default:
				cout << "Error: Please enter a number 1-5"<< endl;
				cout << ">";
				cin >> input;
				break;
		}
		if (input==5)
		{
			continue;
		}
		else
		{
			// Back to Main Menu
			displayFile("Help_Menu.txt");
			cout << ">";
			cin >> input;
		}
	}
}



void displayFile(string fileName)
{
	ifstream helpFile(fileName.c_str());

	if (helpFile.is_open())
	{
		while(!helpFile.eof())
		{
			string getContent;
			getline(helpFile,getContent);
			cout << getContent << endl;
		}
	helpFile.close();
	}
}
