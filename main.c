#include <stdio.h>
#include <assert.h>
#include "bigNumber.h"

int main()
{

	BIG_DECIMAL a;
	BIG_DECIMAL b;

	a = CreateDecimal("123456789", 9);
	b = CreateDecimal("223456789", 9);

	BIG_DECIMAL *c;
	c = MinusDecimal(&a, &b);
	printDecimal(c);

	freeDecimal(a);
	freeDecimal(b);
	freeDecimal(*c);


	return (0);
}
