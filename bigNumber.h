#ifndef __BIG_NUMBER_H__
#define __BIG_NUMBER_H__

#include <stdbool.h>

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
extern void printDecimal(BIG_DECIMAL decimal);
extern void freeDecimal(BIG_DECIMAL decimal);

extern BIG_BINARY CreateBinary(unsigned char *str, unsigned int size);
extern void PrintBinary(BIG_BINARY binary);
extern void FreeBinary(BIG_BINARY binary);

extern bool IsEqual(BIG_DECIMAL *A, BIG_DECIMAL *B);
#endif
