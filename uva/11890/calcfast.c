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

int negs;

int parse_exp(char * e, int start, int end, int pos)
{
  int j, opens=0, closes=0;
  printd("mode: %d\n", pos);
  for (j=start;j<end;j++)
  {
    if (e[j] == '-')
    {
      if (e[j+1] == '(')
        j = parse_exp(e,j+2,end,pos*-1);
      else if (e[j+1] == 'x' && (pos == 1))
      {
        printd("-neg\n");
        negs++;
        j++;
      }
    }
    else if (e[j] == '(')
    {
      printd("open\n");
      opens++;
    }
    else if (e[j] == ')')
    {
      printd("close");
      closes++;
      if (closes > opens)
      {
        return j+1;
      }
    }
    else if (e[j] == 'x' && (pos == -1))
    {
      printd("+neg\n");
      negs++;
    }
  }
  printd("ended properly\n");
}

int compare(const void * a, const void * b)
{
  return *(int *)b - *(int*)a;
}

void run()
{
  char e[100000];
  int j,i,n, * values;
  int total = 0;
  scanf("%s %d",e,&n);
  values = malloc(sizeof(int)*n);
  for (j=0;j<n;j++)
  {
    scanf("%d\n", &values[j]);
  }
  negs = 0;
  parse_exp(e,0, strlen(e), 1);
  printd("%d\n",negs);
  qsort(values,n,sizeof(int),compare);
  for (i=0;i<(n-negs);i++)
  {
    printd("+%d",values[i]);
    total+= values[i];
  }
  for (i=(n-negs);i<n;i++)
  {
    printd("-%d",values[i]);
    total-= values[i];
  }
  printd("\n");
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


