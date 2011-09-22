#include <stdlib.h>
#include <stdio.h>

int b[3], g[3], c[3];

int bgc(int a1, int a2, int a3)
{
  
  /*printf("b%d g%d c%d\n", b[a1],g[a2],c[a3]);*/
  return b[a1] + g[a2] + c[a3];
}

int main()
{
  int count;
  while (scanf("%d %d %d %d %d %d %d %d %d", b, g, c, b+1, g+1, c+1, b+2, g+2, c+2) == 9)
  {
    int best, n, sum;
    char * o = "BCG";
    best = bgc(0,2,1);
    if ((n = bgc(0,1,2)) > best)
    {
      best = n;
      o = "BGC";
    }
    if ((n = bgc(1,2,0)) > best)
    {
      best = n;
      o = "CBG";
    }
    if ((n = bgc(2,1,0)) > best)
    {
      best = n;
      o = "CGB";
    }
    if ((n = bgc(1,0,2)) > best)
    {
      best = n;
      o = "GBC";
    }
    if ((n = bgc(2,0,1)) > best)
    {
      best = n;
      o = "GCB";
    }
    sum = b[0]+b[1]+b[2]+c[0]+c[1]+c[2]+g[0]+g[1]+g[2];
    printf("%s %d\n", o, sum-best);
  }
  return 0;
}

