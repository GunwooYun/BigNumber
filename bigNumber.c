#include "bigNumber.h"
//#include "core.h"

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

	if(decimal->size == 0)
	{
		printf("0");
	}
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

/**
* @author Gunwoo Yun
* @ref Big Number 연산(김세훈)
* @bridef print binary string
* @param[in] pointer BIG_DECIMAL_st
* @param[in] pointer BIG_DECIMAL_st
* @return pointer of BIG_DECIMAL_st
*/
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
	decimal->sign = 0;
	return decimal;
}

/**
* @author Gunwoo Yun
* @ref Big Number 연산(김세훈)
* @bridef example of book & very simple
* @param[in] pointer BIG_DECIMAL_st
* @param[in] pointer BIG_DECIMAL_st
* @return BIG_DECIMAL_st
*/
BIG_DECIMAL PLUS(BIG_DECIMAL *A, BIG_DECIMAL *B)
{
	BIG_DECIMAL result;

	unsigned int min, max;

	BIG_DECIMAL *biggerNum = A->size > B->size ? A : B;

	min = A->size > B->size ? B->size : A->size;
	max = A->size > B->size ? A->size : B->size;

	unsigned int size = max + 1; // For carry space
	result.digit = (unsigned char *)malloc(size);

	unsigned int i = 0;
	unsigned char temp = 0;

	for(;i < min; i++) // keep i value
	{
		result.digit[i] = A->digit[i] + B->digit[i] + temp;
		if(result.digit[i] > 0x09)
		{
			temp = 1;
		}
		else
		{
			temp = 0;
		}
		result.digit[i] %= 0x0A;
	}
	for(;i < max; i++) // keep i value
	{
		result.digit[i] = biggerNum->digit[i] + temp;
		if(result.digit[i] > 0x09)
		{
			temp = 1;
		}
		else
		{
			temp = 0;
		}
		result.digit[i] %= 0x0A;
	}
	if(temp)
	{
		result.digit[i] = temp;
		result.size = size;
	}
	else
	{
		result.size = size - 1;
	}
	result.sign = 0;

	return result;
}

/**
* @author Gunwoo Yun
* @ref Big Number 연산(김세훈)
* @bridef decimal plus digit
* @param[in] pointer BIG_DECIMAL_st
* @param[in] char
* @return void
*/
void AddDigit(BIG_DECIMAL *A, unsigned char digit)
{
	unsigned char carry = 0;
	unsigned int newSize = A->size;
	BIG_DECIMAL tmp;

	/* clone A */
	tmp.digit = (unsigned char *)malloc(A->size+1);
	memset(tmp.digit, 0, A->size+1);
	memcpy(tmp.digit, A->digit, A->size);

	tmp.digit[0] += digit;
	if(tmp.digit[0] > 0x09) 
	{
		tmp.digit[0] %= 0x0A;
		carry = 1;
		for(int i = 1; i < A->size; i++)
		{
			if(carry)
			{
				tmp.digit[i] += carry;
				if(tmp.digit[i] > 0x09) carry = 1;
				else carry = 0;
				tmp.digit[i] %= 0x0A;
			}
			else
				break;
		}
		if(carry)
		{
			tmp.digit[A->size] += carry;
			newSize++;
			A->digit = (unsigned char*)realloc(A->digit, newSize);
		}
	}

	memcpy(A->digit, tmp.digit, newSize);
	A->size = newSize;
}

/**
* @author Gunwoo Yun
* @ref Big Number 연산(김세훈)
* @brief Minus for decimal, A - B
* @param[in] pointer BIG_DECIMAL_st
* @param[in] pointer BIG_DECIMAL_st
* @return void
*/

BIG_DECIMAL* MinusDecimal(BIG_DECIMAL *A, BIG_DECIMAL *B)
{
	BIG_DECIMAL *big = NULL;
	BIG_DECIMAL *small = NULL;
	unsigned char borrow = 0;
	unsigned char tmp = 0;
	int sum = 0;

	int i = 0;
	unsigned int size = 0;

	BIG_DECIMAL *decimal = (BIG_DECIMAL *)malloc(sizeof(BIG_DECIMAL));
	assert(decimal != NULL);

	memset(decimal, 0x00, sizeof(BIG_DECIMAL));

	/* Check bigger */
	if(A->size > B->size)
	{
		big = A;
		small = B;
	}
	else if(B->size > A->size)
	{
		big = B;
		small = A;
	}
	else
	{
		while(i < A->size)
		{
			if(A->digit[i] > B->digit[i])
			{
				big = A;
				small = B;
				break;
			}
			else if(A->digit[i] < B->digit[i])
			{
				big = B;
				small = A;
				break;
			}
			i++;
		}

		if(i == A->size)
		{
			/* A and B same */
			return decimal;	
		}
	}

	decimal->digit = (unsigned char *)malloc(big->size);

	for(i = 0; i < big->size; i++)
	{
		if(i < small->size)
		{
			sum = big->digit[i] - small->digit[i] - borrow;
		}
		else
		{
			sum = big->digit[i] - borrow;
		}
		borrow = 0;
		if(sum < 0)
		{
			borrow = 1;
			sum += 10;
		}
		decimal->digit[i] = (unsigned char)sum;
		if(sum > 0)
		{
			decimal->size = i + 1;
		}
	}

	if(B == big)
	{
		decimal->sign = true;
	}
	else
	{
		decimal->sign = false;
	}
	return decimal;
}


/**
* @author Gunwoo Yun
* @ref Big Number 연산(김세훈)
* @brief Multiply for decimal, A x B
* @param[in] pointer BIG_DECIMAL_st
* @param[in] pointer BIG_DECIMAL_st
* @return void
*/
BIG_DECIMAL* MultiDecimal(BIG_DECIMAL *A, BIG_DECIMAL *B)
{
	if(A == NULL || B == NULL)
	{
		printf("Parameter NULL error\n");
		return NULL;
	}

	int carry = 0;
	int sum = 0;
	int i = 0, j = 0, k = 0;
	BIG_DECIMAL *big = NULL;
	BIG_DECIMAL *small = NULL;

	BIG_DECIMAL *decimal = (BIG_DECIMAL *)malloc(sizeof(BIG_DECIMAL));
	assert(decimal != NULL);

	if((A->size == 1 && A->digit[0] == 0) || (B->size == 1 && B->digit[0] == 0))
	{
		return decimal;
	}

	memset(decimal, 0x00, sizeof(BIG_DECIMAL));

	/* Check bigger */
	if(A->size > B->size)
	{
		big = A;
		small = B;
	}
	else if(B->size > A->size)
	{
		big = B;
		small = A;
	}
	else
	{
		while(i < A->size)
		{
			if(A->digit[i] > B->digit[i])
			{
				big = A;
				small = B;
				break;
			}
			else if(A->digit[i] < B->digit[i])
			{
				big = B;
				small = A;
				break;
			}
			i++;
		}
	}
	int quotient = 0;
	int remainder = 0;
	int index = 0;
	unsigned char *temp = NULL;

	decimal->digit = (unsigned char *)malloc(big->size + small->size);
	temp = (unsigned char *)malloc(big->size + small->size);
	memset(decimal->digit, 0, big->size + small->size);
	memset(temp, 0, big->size + small->size);

	for(i = 0; i < small->size; i++)
	{
		index = i; /* index for sum, 1, 10, 100, ...*/
		for(j = 0; j < big->size; j++)
		{
			sum = small->digit[i] * big->digit[j] + quotient;
			quotient = sum / 0x0A; /* 올림수 */
			remainder = sum % 0x0A; /* 나머지 */
			temp[index++] = remainder;
		}
		if(quotient > 0)
		{
			temp[index++] = quotient;
		}
		for(k = i; k < index; k++)
		{
			sum = decimal->digit[k] + temp[k] + carry;
			carry = 0;
			if(sum > 0x09)
			{
				carry = 1;
				sum -= 0x0A;
			}
			decimal->digit[k] = sum;
		}
		quotient = 0;
		decimal->size = index; /* Last index is size */
		memset(temp, 0, big->size + small->size);
	}
	free(temp);

	return decimal;
}

BIG_DECIMAL* checkBigger(BIG_DECIMAL *A, BIG_DECIMAL *B)
{
	/* Check bigger */
	if(A->size > B->size)
	{
		return A;
	}
	else if(B->size > A->size)
	{
		return B;
	}
	else
	{
		while(i < A->size)
		{
			if(A->digit[i] > B->digit[i])
			{
				return A;
			}
			else if(A->digit[i] < B->digit[i])
			{
				return B;
			}
			i++;
		}
	}
	return NULL;
}

int minusForDivide(unsigned char *a, BIG_DECIMAL *B)
{
	unsigned int i = B->size;
	while(i > 0)
	{
		if(a[i] > B->digit[i])
		{
			return A;
		}
		else if(A->digit[i] < B->digit[i])
		{
			return B;
		}
		i--;
	}

}

/**
* @author Gunwoo Yun
* @ref Big Number 연산(김세훈)
* @brief Divide for decimal, A / B
* @param[in] pointer BIG_DECIMAL_st
* @param[in] pointer BIG_DECIMAL_st
* @return void
*/
BIG_DECIMAL* DivideDecimal(BIG_DECIMAL *A, BIG_DECIMAL *B)
{
	if(A == NULL || B == NULL)
	{
		printf("Parameter NULL error\n");
		return NULL;
	}

	/* A / 0 error */
	if((B->size == 1 && B->digit[0] == 0))
	{
		printf("divide 0 error\n");
		return NULL;
	}

	BIG_DECIMAL *decimal = (BIG_DECIMAL *)malloc(sizeof(BIG_DECIMAL));
	assert(decimal != NULL);

	memset(decimal, 0x00, sizeof(BIG_DECIMAL));

	if((A->size == 1 && A->digit[0] == 0) || B == checkBigger(A, B))
	{
		decimal->digit = malloc(1);
		assert(decimal->digit != NULL);
		decimal->digit[0] = 0;
		decimal->size = 1;
		return decimal;
	}

	if(checkBigger(A, B) == NULL)
	{
		decimal->digit = malloc(1);
		assert(decimal->digit != NULL);
		decimal->digit[0] = 1;
		decimal->size = 1;
		return decimal;
	}

	unsigned char *tmp = (unsigned char *)malloc(A->size);
	assert(tmp != NULL);
	memset(tmp, 0x00, A->size); 



}
