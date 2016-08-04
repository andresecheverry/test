/*
 * Expression_math.h
 *
 *  Created on: Jul 24, 2016
 *      Author: andres.echeverry
 */

#ifndef EXPRESSION_MATH_H_
#define EXPRESSION_MATH_H_

#include"Expression.h"
#include"SimpleExpression.h"

class Expression_math
{
	public:
		Expression* add(Expression*, Expression*);
		Expression* multiply(Expression*, Expression*);
};


#endif /* EXPRESSION_MATH_H_ */
