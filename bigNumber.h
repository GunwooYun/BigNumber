#ifndef __BIG_NUMBER_H__
#define __BIG_NUMBER_H__

#include <stdbool.h>

typedef struct BIG_DECIMAL
{
	unsigned char *digit; // value
	unsigned int size; // size of big number
	bool sign; // plus or minus
}BIG_DECIMAL;

extern BIG_DECIMAL CreateDecimal(unsigned char *str, unsigned int size);
extern void printDecimal(BIG_DECIMAL decimal);
extern void freeDecimal(BIG_DECIMAL decimal);


#endif
