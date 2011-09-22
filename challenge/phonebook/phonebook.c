/*
 * Author: Jeremy Meador
 * Problem: Read a list of phone numbers in one pass (7 digits) and sort 
 *         them
 *
 */


#include <stdlib.h>
#include <stdio.h>
#define DEBUG 0
#define printd if (DEBUG) printf

/*Where the heck is the pow function in C? It isnt in math.h*/
int mypow(int x, int n)
{
  int j, p=1;
  if (n ==0)
    return 1;
  for (j=0;j<n;j++)
  {
    p *= x;
  }
  return p;
}

int main()
{
  int num,j;
  int * data = calloc(((10000000/32)+1),sizeof(int));
  while (scanf("%d",&num) == 1)
  {
    data[num/32] += 1<<(num%32);
  }
  for (j=0;j<10000000;j++)
  {
    if (data[j/32]&(1<<(j%32)))
    {
      int i;
      for (i=6;i>=1;i--)
      {

        printd("%d\n",mypow(10,i));
        if (j < mypow(10,i))
          printf("0");
        else break;  
      }
      printf("%d\n",j);
    }
  }
}


