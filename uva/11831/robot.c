/*
 * Author: Jeremy Meador
 * Problem: 11831 Sticker Collector Robot 
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define DEBUG 0
#define printd if (DEBUG) printf

int * getpos(int r, int c, char ** arena)
{
  int i, j, *pos;
  pos = malloc(sizeof(int)*3);
  for (j=0;j<r;j++)
    for (i=0;i<c;i++)
    {
      if (arena[j][i] == 'N')
      {
        arena[j][i] = '.';
        pos[0] = j;
        pos[1] = i;
        pos[2] = 0; /*North*/
        return pos;
      }
      if (arena[j][i] == 'S')
      {
        arena[j][i] = '.';
        pos[0] = j;
        pos[1] = i;
        pos[2] = 2; /*South*/
        return pos;
      }
      if (arena[j][i] == 'L')
      {
        arena[j][i] = '.';
        pos[0] = j;
        pos[1] = i;
        pos[2] = 1; /*East*/
        return pos;
      }
      if (arena[j][i] == 'O')
      {
        arena[j][i] = '.';
        pos[0] = j;
        pos[1] = i;
        pos[2] = 3; /*West*/
        return pos;
      }
    }
  return NULL;  
}

int move(char c, int * pos, char ** arena)
{
  int xdir=0,ydir=0;
  if (pos[2] == 0)
    ydir = -1;  
  if (pos[2] == 1)
    xdir = 1;  
  if (pos[2] == 2)
    ydir = 1;  
  if (pos[2] == 3)
    xdir = -1;  
  if (c == 'F')
  {
    char sq = arena[pos[0]+ydir][pos[1]+xdir];
    if (sq!='#')
    {
      arena[pos[0]+ydir][pos[1]+xdir] = '.';
      pos[0]+=ydir;
      pos[1]+=xdir;
      return (sq=='*');
    }
  }
  else if (c == 'D')
  {
    pos[2] = (5+pos[2])%4;
  }
  else if (c == 'E')
  {
    pos[2] = (3+pos[2])%4;
  }
  return 0;
}

void run(int r, int c, int cc)
{
  char ** arena = malloc(sizeof(char *)*(r+2));
  char cmds[cc];
  int j, i, *pos, stickers;
  for (j=1;j<r+1;j++)
  {
    arena[j] = malloc(sizeof(char)*(c+3));
    arena[j][0] = '#';
    scanf("%s",arena[j]+1);
    arena[j][c+1] = '#';
  }
  arena[0] = malloc(sizeof(char)*(c+2)); 
  arena[r+1] = malloc(sizeof(char)*(c+2));
  for (j=0;j<c+2;j++)
  {
    arena[0][j] = '#'; 
    arena[r+1][j] = '#';
  }
  for (j=0;j<r+2;j++)
  {
    for (i=0;i<c+2;i++)
      printd("%c",arena[j][i]);
    printd("\n");
  }
  scanf(" %s", cmds);
  pos = getpos(r+2,c+2,arena);
  if (!pos)
  {
    printd("No robot?! :(");
    return;
  }
  printd("%d %d %d\n", pos[0], pos[1], pos[2]);  
  stickers = 0;
  for (j=0;j<cc;j++)
  {
    stickers += move(cmds[j], pos, arena);
    printd("%d %d %d\n", pos[0], pos[1], pos[2]);  
  }
  printf("%d\n", stickers);
}

int main()
{
  int r, c, commands;
  scanf("%d %d %d", &r, &c, &commands);
  while ((r!=0)&&(c!=0)&&(commands!=0))
  {
    run(r,c,commands);
    scanf("%d %d %d", &r, &c, &commands);
  }
  return 0;
}


