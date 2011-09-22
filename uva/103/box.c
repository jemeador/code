#include <stdlib.h>
#include <stdio.h>

#define DEBUG 1
#define printd if (DEBUG) printf

int compare(const void *a, const void *b)
{
  return ( *(int*)b-*(int*)a);
}

int compareSum(const void *a, const void *b)
{
  int i, asum, bsum;
  for(i=0;i<sizeof(*(int**)a);i++) 
  {      
    asum += (*(int**)a)[i];
    bsum += (*(int**)b)[i];
  }
  return bsum-asum;
}

int chain(int a[][4], int n, int k)
{
  int i, j, l, c;
  int bestchain = 1;
  for (i=j+1;i<k;i++)
  {
    int fit = 1;
    for (l=0;l<n;l++)
    {
      if (a[0][l]<=a[i][l])
      {
        fit = 0;
      }
    }
    if (fit)
      c = 1 + chain(a+1,n,k-1);
    if (c > bestchain)
      bestchain = c;
  }
  return bestchain;
}

int main()
{
  int count, j ,i, n, k;
  while (scanf("%d %d", &k, &n) == 2)
  {
    int d[k][n];
    int sum[k];
    for (j=0;j<k;j++)
    {
      sum[j] = 0;
      for (i=0;i<n;i++)
      {
        scanf("%d", &d[j][i]);
        sum[j] += d[j][i];
      }
      qsort(d[j],n,sizeof(int),compare);
    }
    qsort(d,n,sizeof(int)*n,compare);
    int c, bestchain = 0;
    for (j=0;j<k;j++)
    {
      for (i=0;i<n;i++)
        printd("%d ",d[j][i]);
      printd("\n");
    }
    printf("%d", chain(d,n,k));
  }
}

