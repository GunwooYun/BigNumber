#ifndef __BIG_NUMBER_H__
#define __BIG_NUMBER_H__

#include <stdbool.h>

#define INT_SIZE sizeof(int)
#define MASK(num) (num >> (INT_SIZE * 8 - 1))
#define ABS(num) (num + MASK(num)) ^ MASK(num)

#define true 1
#define false 0

typedef struct BIG_DECIMAL
{
	unsigned char *digit; // value
	unsigned int size; // size of big number
	bool sign; // plus or minus
}BIG_DECIMAL;

typedef struct BIG_BINARY
{
	unsigned char *byte; // store data in byte
	unsigned int size;
}BIG_BINARY;

extern BIG_DECIMAL CreateDecimal(unsigned char *str, unsigned int size);
extern void printDecimal(BIG_DECIMAL *decimal);
extern void freeDecimal(BIG_DECIMAL decimal);

extern BIG_BINARY CreateBinary(unsigned char *str, unsigned int size);
extern void PrintBinary(BIG_BINARY binary);
extern void FreeBinary(BIG_BINARY binary);

extern bool IsEqual(BIG_DECIMAL *A, BIG_DECIMAL *B);
extern BIG_DECIMAL* AddDecimal(BIG_DECIMAL *A, BIG_DECIMAL *B);
extern bool IsBigger(BIG_DECIMAL *A, BIG_DECIMAL *B);
extern BIG_DECIMAL PLUS(BIG_DECIMAL *A, BIG_DECIMAL *B);

extern void AddDigit(BIG_DECIMAL *A, unsigned char digit);

extern BIG_DECIMAL* MinusDecimal(BIG_DECIMAL *A, BIG_DECIMAL *B);

extern BIG_DECIMAL MultiDecimal(BIG_DECIMAL *A, BIG_DECIMAL *B);

extern BIG_DECIMAL* DivideDecimal(BIG_DECIMAL *A, BIG_DECIMAL *B);

extern BIG_DECIMAL* ModuloDecimal(BIG_DECIMAL *A, BIG_DECIMAL *B);
bool IsPrimeNumber(BIG_DECIMAL *num);

extern BIG_DECIMAL GetDecimalFromBinary(BIG_BINARY *binary);
#endif
