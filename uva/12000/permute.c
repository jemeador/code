#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int permute(int * a, int size, int i, int k)
{
  int j;
  int total = 0;
  int x = size-i;
  int low=0;
  int high=size;
  if (i == 0)
  {
/*    for (j=0;j<size;j++)
      printf("%d, ", a[j]);
    printf("\n");
*/    return 1;
  }
  if (x-k>0)
    low = x-k;
  if (x+k+1<size)
    high = x+k+1;
  for (j=low;j<high;j++)
  {
    int b[size];
    memcpy(b,a,size*sizeof(int));
    if (b[j] == 0)
    {
      b[j] = x+1;
      total += permute(b,size,i-1,k);
    }
  }
  return total;
}

int main() 
{
  int n, k, j, y, z;
  int * arr;
  /*scanf("%d %d", &n,&k);*/ k=2;
  for (n=0;n<20;n++)
  {
    int empty[n];
    for (j=0;j<n;j++)
      empty[j] = 0;
    arr = empty;  
    z = permute(arr, n, n, k);
    printf("%d\n",z);
  }
  return 0;
}
