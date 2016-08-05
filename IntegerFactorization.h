/*
 * IntegerFactorization.h
 *
 *  Created on: Aug 4, 2016
 *      Author: andres.echeverry
 */

#ifndef INTEGERFACTORIZATION_H_
#define INTEGERFACTORIZATION_H_


#include<vector>

using namespace std;

class IntegerFactorization
{
	public:
		IntegerFactorization(int);
		~IntegerFactorization();
		int getFactorExp(int);
		vector<std::pair<int,int> > getAllFactors();
		pair<int,int> getRoot(int);

	private:
		int myInt;
		vector<std::pair<int, int>> allFactors;
};

#endif /* INTEGERFACTORIZATION_H_ */
