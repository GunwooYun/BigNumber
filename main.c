#include <stdio.h>
#include <assert.h>
#include "bigNumber.h"

int main()
{

	BIG_DECIMAL a;
	BIG_DECIMAL b;

	a = CreateDecimal("99887721", 8);
	b = CreateDecimal("99", 2);

	BIG_DECIMAL *c;
	c = ModuloDecimal(&a, &b);
	printDecimal(c);

	//printDecimal(&a);

	freeDecimal(a);
	freeDecimal(b);
	freeDecimal(*c);


	return (0);
}
