#include <stdio.h>
#include <assert.h>
#include "bigNumber.h"

int main()
{
	BIG_DECIMAL decimal;
	decimal = CreateDecimal("1234567890", 10);

	printDecimal(decimal);

	freeDecimal(decimal);
	return (0);
}
