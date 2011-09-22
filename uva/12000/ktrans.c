#include <stdlib.h>
#include <stdio.h>

#define M 73405

const int z1 = -1;
const int z2 = 3;
const int depth = 5;
const int defaultk = 2;

int fib(int n)
{
  if (n<1)
  {
    printf("fib: unexpected value n=%d", n);
    return 1;
  }
  if (n==1)
    return 1;
  if (n==2)
    return 2;
  return fib(n-1)+fib(n-2);
}

int linear(int count, int *c, int csize, int k)
{
  int success = 0;
  int i,j;
  if (count ==0)
  {
    int t,t2;
    for (i=2;i<20;i++)
    {
      t=0;
      for (j=0;j<csize;j++)
      {
        int next = c[j]*magic(i-(j+1),k);
        printf("%d ",c[j],next);
        t+=next;
      }
      t2 = magic(i, k);
      printf(", %d ?= %d\n",t,t2);
      if (t % M !=t2)
        return 0;
    }
    return 1;
   }
   for (j=z1;!success&&j<z2;j++)
   {
     c[count-1]=j;
     success = linear(count-1,c,csize,k);
   }
   if (success)
   {
     printf("Found!\n");
     for (j=0;j<csize;j++)
       if (c[j] != 0)
         printf("%d*f(n-%d,%d) +\n", c[j],j+1,k);
     printf(" = f(n,k)\n");
   }
   return 0;
}
int magic(int n, int k)
{
  if (n<0)
    return 0;
  if (n<=1)
    return 1;
  if (n==2)
    return 2;
  if (k==1)
    return (magic(n-1,k) + magic(n-2,k)) % 73405;
  if (k==2)
  {
    int i, j;
    int neg[6];
    neg[5]=0;
    neg[4]=0;
    neg[3]=1;
    neg[2]=1;
    neg[1]=2;
    for (j=3;j<=n;j++)
    {
      neg[0] = (2*(neg[1]) +2*(neg[3]) - neg[5] + M) % M;
      for (i=5;i>0;i--)
      {
        neg[i] = neg[i-1];
      }
    }
    return neg[0];
    /*return 2*magic(n-1,k)+2*magic(n-3,k)-magic(n-5,k) % 73405;*/
  }
  if (k==3)
  {
    int arr[] = {1,1,2,6,24,78,230,675,2064};
    if (n <= 8)
      return arr[n];
  }
  return 0;  
}

void run()
{
  int n, k, csize;
  /*scanf("%d %d", &n, &k);
  printf("%d\n", magic(n,k));*/
  int c[depth];
  csize = depth;
  linear(csize,c,csize,defaultk);
}

int main()
{
  int count, j;
  scanf("%d", &count);
  for (j=0;j<count;j++)
  {
    run();
  }
}
