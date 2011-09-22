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
/*2020123/0   12*/
void run(char * n)
{
  int length = strlen(n);
  printd("%s\n",n);
  while (length > 3)
  {
    int d = n[length-1] - '0';
    int x = 100*n[length-4] - '0' + 10*(n[length-3] - '0') + n[length-2] - '0';
    char newnum[4];
    x -= d*5;
    n[length-4] = '\0';
    printd("%d\n",x);
    sprintf(newnum,"%d",x);
    strcat(n,newnum);
    length--;    
  } 
}

int main()
{
  char num[101];
  scanf("%s",num);
  for (;strcmp(num,"0")!=0;scanf("%s",num))
  {
    run(num);
  }
}


/*    private int sub(String thatString, StringBuffer sum, int j)
    {
      if (j==this.num.length())
        return 0;
      int next = this.num.charAt(j)-thatString.charAt(j) - sub(thatString,sum,j+1);
      int borrow = 0;
      if (next < 0)
      {
        borrow = 1;
        next = next + 10;
      }
      sum.append(next);
      return borrow;
    }
*/

void sub(char * s, int n)
{
  int l = strlen(s);
  while (n != 0)
  {
    int x = s[l-1];
    int c = 0;
    while (x-n < 0)
    { 
      n -= 10;
      c++;
    }  
    s[l-1] -= n;
    l--;
    n = c;
  }
}




