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

	return (0);
}
