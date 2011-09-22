/*
 * Author: Jeremy Meador
 * Problem: Movies
 *
 */


#include <stdlib.h>
#include <stdio.h>

#define DEBUG 0
#define printd if (DEBUG) printf

void run()
{
  int movies, minutes=0, j, sum=0;
  scanf("%d",&movies);
  for (j=0;j<movies;j++)
  {
    int movtime;
    scanf("%d",&movtime);
    sum+= movtime;
    minutes += sum + movtime;
  }
  printf("Boudreau is going to spend %d minutes watching movies.\n", minutes);
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


