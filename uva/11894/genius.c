/*
 * Author: Jeremy Meador
 * Problem: 
 *
 */


#include <stdlib.h>
#include <stdio.h>

#define DEBUG 0
#define printd if (DEBUG) printf

typedef struct
{
  int x;
  int y;
}coord;

typedef struct 
{
  coord * c[100000];
}plug;

int compare(const void * a, const void * b)
{
  int r;
  coord * c1 = (*(coord**)a);
  coord * c2 = (*(coord**)b);
  /*if (c1 == NULL)
    return -1;
  if (c2 == NULL)
    return 1;*/
  r = c1->x - c2->x;
  if (r == 0)
    r = c1->y - c2->y;
  return r;  
}

void rotate(plug * p, int count)
{
  int j = 0;
  while((p->c[j] != NULL) && j < count)
  {
    int x = p->c[j]->x;
    int y = p->c[j]->y;  
    p->c[j]->x = y;
    p->c[j]->y = -x;
    j++;
  }
  qsort(p->c, count, sizeof(coord*),compare);
}

int fits(plug * m, plug * f, int count)
{
  int offx = m->c[0]->x - f->c[0]->x;
  int offy = m->c[0]->y - f->c[0]->y;
  int j = 0;
  while ((m->c[j] != NULL) && j < count)
  {
    printd("%d == %d + %d\n", m->c[j]->x, f->c[j]->x, offx);
    printd("%d == %d + %d\n", m->c[j]->y, f->c[j]->y, offy);
    if ((m->c[j]->x != (f->c[j]->x + offx)) || (m->c[j]->y != (f->c[j]->y + offy)))
      return 0;
    j++;  
  }
  return 1;
}

void run()
{
  int count, x,y,j,k,i;
  plug plugs[2];
  scanf("%d\n", &count);
  for (i=0;i<2;i++)
  {
    for (j=0;j<count;j++)
    {
      scanf("%d %d\n", &x, &y);
      plugs[i].c[j] = malloc(sizeof(coord));
      plugs[i].c[j]->x = x;
      plugs[i].c[j]->y = y;
    }

    for (j=0;j<count;j++)
      printd("%d %d\n",plugs[i].c[j]->x, plugs[i].c[j]->y);
      /*printd("%d %d\n",plugs[i].c[j]->x - plugs[i].c[0]->x, plugs[i].c[j]->y - plugs[i].c[0]->y);*/
  }
  qsort(plugs[0].c, count, sizeof(coord*),compare);
  qsort(plugs[1].c, count, sizeof(coord*),compare);
  k = fits(&plugs[0],&plugs[1], count);
  for (i=0;(i<3 && k==0);i++)
  {
    rotate(&plugs[1], count); 
    printd("-=-=-=-=-\n");
    for (j=0;j<count;j++)
      printd("%d %d\n",plugs[1].c[j]->x, plugs[1].c[j]->y);
      /*printd("%d %d\n",plugs[1].c[j]->x - plugs[1].c[0]->x, plugs[1].c[j]->y - plugs[1].c[0]->y);*/
    k = fits(&plugs[0],&plugs[1], count);
  }
  if (k)
  {
    printf("MATCHED\n");  
  }
  else
    printf("NOT MATCHED\n");
}

int main()
{
  int count, j;
  scanf("%d\n", &count);
  for (j=0;j<count;j++)
  {
    printd("%d\n",j);
    run();
  }
}


