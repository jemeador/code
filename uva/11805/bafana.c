#include <stdlib.h>
#include <stdio.h>

void run(int j)
{
  int n, k, p, x;
  scanf("%d %d %d",&n, &k, &p);
  x = (p + k) % n;
  if (x == 0)
    x = n;
  printf("Case %d: %d\n", j+1, x);
}

int main()
{
  int count, j;
  scanf("%d", &count);
  for (j=0;j<count;j++)
  {
    run(j);
  }
}

