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



   

   freeDecimal(a);
   freeDecimal(b);
   freeDecimal(c);
   return (0);
}
