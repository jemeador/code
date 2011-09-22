/*
 * Author: Jeremy Meador
 * Problem: 
 *
 */


#include <stdlib.h>
#include <stdio.h>

#define DEBUG 1
#define printd if (DEBUG) printf


int main()
{
  int count, j;
  for (j=10000000-1;j>=0;j--)
  {
    printf("%d\n",j);
  }
}


