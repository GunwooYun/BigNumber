#include <stdio.h>
#include <assert.h>
#include "bigNumber.h"

int main()
{
	BIG_DECIMAL decimal;
	BIG_BINARY binary;
	decimal = CreateDecimal("1234567890", 10);

	printDecimal(decimal);

	freeDecimal(decimal);

	binary = CreateBinary("12345ABCDE", 10);

	PrintBinary(binary);

	FreeBinary(binary);

	BIG_DECIMAL a;
	BIG_DECIMAL b;

	a = CreateDecimal("1234567890", 10);
	b = CreateDecimal("1234567891", 10);

	if(IsEqual(&a, &b))
		printf("a and b equal\n");
	else
		printf("a and b not equal\n");


	freeDecimal(a);
	freeDecimal(b);


	return (0);
}
