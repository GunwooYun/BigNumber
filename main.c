#include <stdio.h>
#include <assert.h>
#include "bigNumber.h"

int main()
{

	BIG_DECIMAL a;
	BIG_DECIMAL b;

	a = CreateDecimal("9999999999999999", 16);
	b = CreateDecimal("99999999", 8);

	BIG_DECIMAL *c;
	c = MultiDecimal(&a, &b);
	printDecimal(c);

	freeDecimal(a);
	freeDecimal(b);
	freeDecimal(*c);


	return (0);
}
