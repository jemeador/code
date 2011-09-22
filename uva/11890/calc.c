/*
 * Author: Jeremy Meador
 * Problem: 
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEBUG 0
#define printd if (DEBUG) printf


int get_next_close(char * e, int start, int end)
{
  int j;
  for (j=start;j<end;j++)
  {
    if (e[j] == ')')
    {
      return j; 
    }
  }
  return 0;
}

int get_prev_open(char * e, int end)
{
  int j;
  for (j=end;j >= 0;j--)
  {
    if (e[j] == '(')
    {
      return j; 
    }
  }
  return 0;
}



void parse_exp(char * e)
{
  int close, j, start=0;
  while (close = get_next_close(e, start, strlen(e)))
  {
    int open = get_prev_open(e, close);
    { 
      for (j=open;j<=close;j++)
      {
        if (open > 0 && e[open-1] == '-')
        {
          if (e[j] == '-')
            e[j] = '+';
          else if (e[j] == '+')
            e[j] = '-';
        }
        if (e[j] == ')' || e[j] == '(')
          e[j] = ' ';
      }
    }
    start = close;
  }
}

int compare(const void * a, const void * b)
{
  return *(int *)b - *(int*)a;
}

void run()
{
  char e[100000];
  int total, j,i,n, negs, * values;
  scanf("%s %d",e,&n);
  values = malloc(sizeof(int)*n);
  for (j=0;j<n;j++)
  {
    scanf("%d\n", &values[j]);
  }
  printd("%s, %d\n",e,n);
  parse_exp(e);
  negs = 0;
  for (i=0;i<strlen(e);i++)
  {
    if (e[i] == '-')
      negs += 1;  
  }
  total = 0;
  qsort(values,n,sizeof(int),compare);
  for (i=0;i<(n-negs);i++)
  {
    total+= values[i];
  }
  for (i=(n-negs);i<n;i++)
  {
    total-= values[i];
  }
  printf("%d\n", total);
}

int main()
{
  int count, j;
  scanf("%d", &count);
  for (j=0;j<count;j++)
  {
    printd("%d\n",count);  
    run();
  }
}


