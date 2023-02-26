#include <stdio.h>
#include <assert.h>
#include "bigNumber.h"

int main()
{

	BIG_DECIMAL a;
	BIG_DECIMAL b;

	a = CreateDecimal("1000000000", 10);
	b = CreateDecimal("9999", 4);

	BIG_DECIMAL *c;
	c = DivideDecimal(&a, &b);
	printDecimal(c);

	freeDecimal(a);
	freeDecimal(b);
	freeDecimal(*c);


	return (0);
}
