#include "bigNumber.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

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
void printDecimal(BIG_DECIMAL *decimal)
{
	int i;

	if(decimal->sign)
	{
		printf("-");
	}
	for( i = decimal->size - 1; i >= 0; i--)
	{
		printf("%c", decimal->digit[i] + 48);
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

/**
* @author Gunwoo Yun
* @ref Big Number 연산(김세훈)
* @bridef create object of binary
* @param[in] byte string
* @param[in] length of string
* @return BIG_BINARY_st
*/
BIG_BINARY CreateBinary(unsigned char *bytes, unsigned int length)
{
	BIG_BINARY binary;

	binary.byte = (unsigned char *)malloc(length);

	for(int i = 0; i < length; i++)
	{
		binary.byte[i] = bytes[length-1-i];
	}

	binary.size = length;

	return binary;
}

/**
* @author Gunwoo Yun
* @ref Big Number 연산(김세훈)
* @bridef print binary string
* @param[in] BIG_BINARY_st
* @return void
*/
void PrintBinary(BIG_BINARY binary)
{
	unsigned char mask;
	for(int i = binary.size - 1; i >= 0; i--)
	{
		mask = 0x80;
		while(mask > 0)
		{
			if((binary.byte[i] - 48) & mask) printf("1");
			else printf("0");
			mask = mask >> 1;
		}
	}
}

void FreeBinary(BIG_BINARY binary)
{
	if(binary.byte != NULL)
		free(binary.byte);
}

bool IsEqual(BIG_DECIMAL *A, BIG_DECIMAL *B)
{
	if(A->size != B->size)
	{
		return false;
	}

	for(int i= 0; i < A->size; i++)
	{
		if(A->digit[i] != B->digit[i])
			return false;
	}

	return true;
}

BIG_DECIMAL* AddDecimal(BIG_DECIMAL *A, BIG_DECIMAL *B)
{
	if(A == NULL || B == NULL)
		return NULL;

	printDecimal(A);
	printDecimal(B);

	unsigned int length, remain, sum, carry;
	BIG_DECIMAL *largeNum;

	BIG_DECIMAL *decimal = (BIG_DECIMAL *)malloc(sizeof(BIG_DECIMAL));
	assert(decimal != NULL);

	//memset(decimal, 0, sizeof(BIG_DECIMAL));

	if(A->size >= B->size)
	{
		length = A->size;
		remain = B->size;
		largeNum = A;
	}
	else
	{
		length = B->size;
		remain = A->size;
		largeNum = B;
	}

	decimal->digit = (unsigned char *)malloc(length + 1);
	decimal->size = length;
	memset(decimal->digit, 0, length + 1);

	bool carryFlag = false;

	for(int i = 0; i < length; i++)
	{
		if(remain > 0)
		{
			sum = ((A->digit[i]) + (B->digit[i]));
			carry = sum / 10;

			decimal->digit[i] += sum % 10;
			if(carry == 1){
				decimal->digit[i+1] = 1;
				carry = 0;
			}
			remain--;
		}
		else
		{
			if(i < length)
			{
				sum = (decimal->digit[i])  + (largeNum->digit[i]);
				carry = sum / 10;
				decimal->digit[i] = sum % 10;
				if(carry == 1){
					if(i == (length-1)){
						carryFlag = true;
					}
					decimal->digit[i + 1] = 1;
					carry = 0;
				}
			}
		}

	}
	if(carryFlag)
		decimal->size = length + 1;
	return decimal;

bool IsBigger(BIG_DECIMAL *A, BIG_DECIMAL *B)
{
	if(A->size > B->size)
		return true;
	if(A->size < B->size)
		return false;
	for(int i = 0; i < A->size; i++)
	{
		if(A->digit[i] > B->digit[i])
			return true;
		else if(A->digit[i] < B->digit[i])
			return false;
	}
	return false;
}
