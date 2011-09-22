/*
 * Author: Jeremy Meador
 * Problem: 11839 Optical Reader
 *
 */


#include <stdlib.h>
#include <stdio.h>

#define DEBUG 0
#define printd if (DEBUG) printf



void run()
{
  char key[7] = {'*', 'A', 'B', 'C', 'D', 'E', '*'};
  int n=0, j, a[5];
  scanf("%d %d %d %d %d", &a[0], &a[1], &a[2], &a[3], &a[4]); 
  for (j=0;j<5;j++)
  {
    if (a[j] <= 127)
    {
      if (n == 0)
        n = j+1;
      else
        n = 6;
    }
  }
  printf("%c\n", key[n]);
}

int main()
{
  int count, j;
  scanf("%d", &count);
  while (count != 0)
  {
    for (j=0;j<count;j++)
    {
      printd("%d\n",count);
      run();
    }
    scanf("%d", &count);
  }
}


