#include <stdio.h>
#include <assert.h>
//#include <stdlib.h>
#include "bigNumber.h"

int main()
{

   BIG_DECIMAL a;
   BIG_DECIMAL b;
   BIG_DECIMAL c;
   //a.digit = malloc(10);

   a = CreateDecimal("2", 1);
   printDecimal(&a);
   b = CreateDecimal("2", 1);
   printDecimal(&b);
   
   c = MultiDecimal(&a, &b);
   
   printDecimal(&c);

   unsigned char data[9] = {0x10, 0x35, 0xb3, 0x7f, 0x94, 0xa9, 0x7e, 0x11, 0x93};
   BIG_BINARY bin = CreateBinary(data, sizeof(data));
   PrintBinary(bin);
   //unsigned char *ptr = bin.byte;
   BIG_DECIMAL d = GetDecimalFromBinary(&bin);
   printf("size : %d\n", d.size);
   printDecimal(&d);






   

   freeDecimal(a);
   freeDecimal(b);
   freeDecimal(c);
   freeDecimal(d);
   FreeBinary(bin);
   return (0);
}
