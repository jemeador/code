/*
 * Author: Jeremy Meador
 * Problem: Finite Fingerprints
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEBUG 0
#define printd if (DEBUG) printf

int charToNum(char a)
{
  if ((a >= 'A')&&(a<='Z'))
    return a-'A';
  if ((a >= 'a')&&(a<='z'))
    return a-'a'+26;
  if ((a >= '0')&&(a<='9'))
    return a-'0'+52;
  if (a == '+')
    return 62;
  if (a == '/')
    return 63; 
}

void run(int count, int casenum)
{
  int j,i;
  char ff[count][1000];
  char longf[count][1000];
  char shortf[count][1000];
  char sets[count][count];
  int numInSet[count];
  int numofsets = 1;
  char buf[5];
  int highest = 0;
  for (j=0;j<count;j++)
  {
    int i;
    scanf("%s\n",ff[j]);
    //printd("\n%s = ",ff[j]);
    for (i=0;ff[j][i] != '\0';i++)
    {
      int k;
      for (k=5;k>=0;k--)
      {
        shortf[j][6*i+(5-k)] = (charToNum(ff[j][i])&(1<<k))?'1':'0';
      }
    }
    shortf[j][i*6] = '\0';
    strcpy(longf[j],shortf[j]);
    strcat(longf[j],shortf[j]);
    printd("%s * 2 = %s\n",shortf[j],longf[j]);
  }

  sets[0][0] = '1';
  numInSet[0] = 1;
  highest = 1;
  for (j=1;j<count;j++)
  {
    int newset=1;
    for (i=0;i<numofsets;i++)
    {
      int z = sets[i][0]-'1';
      if (strstr(longf[z],shortf[j]))
      {
        newset = 0;
        sprintf(buf,"%d",j+1);
        strcat(sets[i],buf);
        numInSet[i] += 1;
        if (numInSet[i] > highest)
          highest = numInSet[i];
      }
    }
    if (newset)
    {
      sprintf(buf,"%d",j+1);
      strcpy(sets[numofsets++],buf);
      numInSet[j] = 1;
    }
  }
  printf("Case %d:",casenum);
  for (i=1;i<=highest;i++)
    for (j=0;j<numofsets;j++)
    {
      if (numInSet[j] == i)
        printf(" %s",sets[j]);
    }
  printf("\n");
}

int main()
{
  int count, j, casenum =1;
  scanf("%d", &count);
  for(;count!=0;scanf("%d", &count))
  {
    run(count,casenum);
    casenum++;
  }
}


