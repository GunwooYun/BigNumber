#include "bigNumber.h"

#include <stdlib.h>
#include <stdio.h>

/**
* @author Gunwoo Yun
* @ref Big Number 연산(김세훈)
* @bridef Create decimal structure
* @param[in] str string of number
* @param[in] size length of string
* @return BIG_DECIMAL
*/
BIG_DECIMAL CreateDecimal(unsigned char *str, unsigned int size)
{
	BIG_DECIMAL decimal;

	decimal.digit = (unsigned char *)malloc(size);
	if(decimal.digit == NULL)
	{
		printf("digit malloc failed\n");
		return decimal;
	}

	for(int i = 0; i < size; i++)
	{
		decimal.digit[i] = str[size - i - 1] - 48; // char - ascii dec
	}

	decimal.size = size;
	decimal.sign = false;

	return decimal;
}

/**
* @author Gunwoo Yun
* @ref Big Number 연산(김세훈)
* @bridef print big number
* @param[in] decimal BIG_DECIMAL structure
* @return void
*/
void printDecimal(BIG_DECIMAL decimal)
{
	int i;

	if(decimal.sign)
	{
		printf("-");
	}
	for( i = decimal.size - 1; i >= 0; i--)
	{
		printf("%c", decimal.digit[i] + 48);
	}
	printf("\n");
}

void freeDecimal(BIG_DECIMAL decimal)
{
	if(decimal.digit != NULL)
	{
		free(decimal.digit);
	}
}
