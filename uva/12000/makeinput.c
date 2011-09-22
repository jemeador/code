#include <stdlib.h>
#include <stdio.h>

#define DEBUG 1

int main()
{
  int i,j;
  printf("%d\n", 1001*3);
  for (i=0;i<=1000;i++)
    for(j=1;j<=3;j++)
      printf("%d %d\n", i, j);
  return 0;    
}

