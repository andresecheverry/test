/*
 * IntegerFactorization.cpp
 *
 *  Created on: Aug 4, 2016
 *      Author: andres.echeverry
 */

// This class will take a number and return
// its prime factors and exponents

#include<vector>
#include <unordered_map>
#include<math.h>
#include"IntegerFactorization.h"
#include<iostream>

using namespace std;

vector<int> getPrimesFor(int myInt)
{
	vector<int> myPrimes;

	if (myInt>=2) myPrimes.push_back(2);
	if (myInt>=3) myPrimes.push_back(3);

	for (int i=1;(6*i-1)<=(myInt/2); i++)
	{
		for (int k = -1; k<=1; k=k+2)
		{
			int candidate = 6*i+k;
			bool success = true;

			for (int j = 0; myPrimes[j] <= pow(candidate, 0.5); j++)
			{
				if (candidate % myPrimes[j] == 0 )
				{
					success=false;
					break;
				}
			}// at this point the candidate has been tested against possible roots
			if (success) // candidate is a prime
			{
				myPrimes.push_back(candidate);
			}
		}
	}

	return myPrimes;

};

IntegerFactorization::IntegerFactorization(int a)
{
	myInt = a;

	vector<int> factorCandidates = getPrimesFor(myInt);
	vector<int>::iterator iter;
	int remainingFactor = myInt;

	for(iter = factorCandidates.begin(); iter!=factorCandidates.end();iter++)
	{
		int count = 0;
		int candidateFactor = *iter;
		while (remainingFactor %candidateFactor ==0)
		{
			count++;
			remainingFactor = remainingFactor/candidateFactor;
		}
		if(count > 0)
		{
			pair<int, int> newPair = {candidateFactor,count};
			allFactors.push_back(newPair);
		}

	}
}

IntegerFactorization::~IntegerFactorization()
{
	;
}

pair<int,int> IntegerFactorization::getRoot(int a)
{
	cout << "computing "<< a <<"th root of " << myInt << endl;

	vector<std::pair<int,int>>::iterator iter;
	int outsideTheRoot=1;
	int remainder = myInt;
	pair<int,int> result;

	for(iter = allFactors.begin(); iter!=allFactors.end(); iter++)
	{// go through list of allFactors
		if (((*iter).second >= a)) // thisFactor's exponent allows it to come out of the root
		{
			int newExponent = ((int)(*iter).second / (int)a);
			remainder = remainder / (int)pow((*iter).first,newExponent*a); // reduce the remainder
			outsideTheRoot = outsideTheRoot*pow((*iter).first,newExponent);
		}
	}
	pair<int, int> newPair = {outsideTheRoot,remainder};

	cout << "root result is " << outsideTheRoot << " outside the root and " << remainder << " inside the root" << endl;
	cout << newPair.first << " and " << newPair.second << endl;
	return newPair;
}

vector<std::pair<int, int>> IntegerFactorization::getAllFactors()
{
	return allFactors;
}

int IntegerFactorization::getFactorExp(int a)
{
	int myFactorExponent=0;

	vector<std::pair<int,int>>::iterator iter;
	for(iter = allFactors.begin(); iter!=allFactors.end(); iter++)
	{// go through list of allFactors
		if ((*iter).first == a) myFactorExponent = (*iter).second;
	}
	return myFactorExponent;
}
