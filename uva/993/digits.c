#include <stdio.h>
#include <stdlib.h>

void printnumber(int n,int twos,int threes,int fives, int sevens)
{
  int j, i;
  int digit[10];
  for (j=0;j<10;j++)
    digit[j] = 0;
  while (twos >= 3)
  {
    digit[8] = digit[8] + 1;
    twos -= 3;
  }
  while (threes >= 2)
  {
    digit[9] = digit[9] + 1;
    threes -= 2;
  }
  while ((twos > 0) && (threes > 0))
  {
    digit[6] = digit[6] + 1;
    twos--;
    threes--;
  }
  while (twos >= 2)
  {
    digit[4] = digit[4] + 1;
    twos -= 2;
  }
  digit[2] = twos;
  digit[3] = threes;
  digit[5] = fives;
  digit[7] = sevens;
  for (j=2;j<=9;j++)
  {
    for (i=0;i<digit[j];i++)
      printf("%d",j);
  }
  printf("\n");
}

void factorize(int n)
{
  int twos = 0;
  int threes = 0;
  int fives = 0;
  int sevens = 0;
  if (n <= 1)
  {
    printf("%d\n",n);
    return;
  }
  while (n % 2 == 0)
  {
    twos++;
    n /= 2;
  }
  while (n % 3 == 0)
  {
    threes++;
    n /= 3;
  }
  while (n % 5 == 0)
  {
    fives++;
    n /= 5;
  }
  while (n % 7 == 0)
  {
    sevens++;
    n /= 7;
  }
  if (n == 1)
  { 
    printnumber(n,twos,threes,fives,sevens);
  }
  else
    printf("-1\n");
}


int main()
{
  int j,x,n;
  scanf("%d",&x);
  for (j=0;j<x;j++)
  {
    scanf("%d",&n);
    factorize(n);
  }
  return 0;
}

