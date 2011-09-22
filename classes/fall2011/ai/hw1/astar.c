/*
 * Author: Jeremy Meador
 * Assignment: Homework 1 A* algorithm 
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEBUG 0
#define printd if (DEBUG) printf
#define MAX_PATH 1000000

typedef struct
{
  char sq[26];
  /*0  1  2  3  4
   *5  6  7  8  9
   *10 11 12 13 14
   *15 16 17 18 19
   *20 21 22 23 24 \0*/
}map;

struct __node__
{
  map M;
  int pos;
  int action_cost;
  int time;
  char type;
  struct __node__ * parent;
  int f, g, h;
};

typedef struct __node__ node;

typedef struct
{
  node * n[MAX_PATH];
  int size;
}node_list;

void add_node(node * n, node_list * nl)
{
  nl->n[nl->size++] = n;
}

void remove_node(node * n, node_list * nl)
{
  int j;
  for (j=0;j < nl->size;j++)
  {
    if (nl->n[j] == n)
    {
      nl->n[j] = NULL;
      return;
    }
  }
  printf("Error: Node does not exist");
  exit(1);
}

node * best(node_list * nl)
{
  node * n = NULL;
  int b = 1 << 30;
  int j, c;
  for (j=1;j < nl->size;j++)
  {
    if (nl->n[j] != NULL)
    {
      c = nl->n[j]->f;
      if (c < b)
      {
        b = c;
        n = nl->n[j];
      }
    }
  }
  if (n == NULL)
  {
    printf("Invalid frontier configuration, all null of size %d", nl->size);
    exit(1);
  }
  return n;
}

int number_of_dirty(map * M)
{
  int j, d=0;
  for (j=0;j<25;j++)
  {
    if (M->sq[j] == 'D')
      d++;
  }
  return d;
}

int calcg(node * n)
{
  int x = 2*number_of_dirty(&(n->M)) + n->action_cost;
  /*printd("Calcg: %d\n", x);*/
  return x;
}

int calch(node * n)
{
  int d = number_of_dirty(&(n->M));
  if (d == 0)
    return 0;
  return 4*number_of_dirty(&(n->M)) - 1;
}

int calcf(node * n)
{
  return calch(n) + calcg(n);
}

void print_path(node * n)
{
  int i,j;
  if (n->type != 'B')
  {
    print_path(n->parent);
    if (n->type == 'U')
      printf("Move Up | Score: -%d\n", n->g);
    else if (n->type == 'D')
      printf("Move Down| Score: -%d\n", n->g);
    else if (n->type == 'L')
      printf("Move Left | Score: -%d\n", n->g);
    else if (n->type == 'R')
      printf("Move Right | Score: -%d\n", n->g);
    else if (n->type == 'S')
      printf("Suck | Score: -%d\n", n->g);  
  }
  if (n->type != 'N')
  {
    for (j=0;j<5;j++)
    {
      for (i=0;i<5;i++)
      {
        if (n->pos == j*5+i)
          printf("O");
        else 
          printf("%c",n->M.sq[j*5+i]);
      }
      printf("\n");
    }
  }
  return;
}

int main()
{
  node start;
  map original_map = 
          {'x', 'x', 'x', 'x', 'x',
           'x', 'D', 'D', 'D', 'x',
           'x', 'C', 'C', 'C', 'x',
           'x', 'C', 'C', 'C', 'x',
           'x', 'x', 'x', 'x', 'x', '\0'};
  start.M = original_map;
  start.action_cost = 0;
  start.g = 0;
  start.pos = 12;
  start.time = 0;
  start.type = 'B'; /*begin*/
  node_list frontier;
  frontier.size = 0;
  node * current = &start;
  add_node(&start,&frontier);
  while (current->time < 100)
  {
    node * n = current;
    remove_node(n, &frontier);
    if (n->M.sq[n->pos-5] != 'x')
    {
      node * m = malloc(sizeof(node));
      m->type = 'U';
      m->pos = n->pos - 5;
      strcpy(m->M.sq,n->M.sq);
      m->action_cost = 1;
      m->time = n->time+1;
      m->parent = n;
      m->g = calcg(m) + n->g;
      m->h = calch(m);
      m->f = m->g + m->h;
      printd("Up: g:%d, h:%d, f:%d\n", m->g, m->h, m->f);
      add_node(m, &frontier);
    }
    if (n->M.sq[n->pos+5] != 'x')
    {
      node * m = malloc(sizeof(node));
      m->type = 'D';
      m->pos = n->pos + 5;
      strcpy(m->M.sq,n->M.sq);
      m->action_cost = 1;
      m->time = n->time+1;
      m->parent = n;
      m->g = calcg(m) + n->g;
      m->h = calch(m);
      m->f = m->g + m->h;
      printd("Down: g:%d, h:%d, f:%d\n", m->g, m->h, m->f);
      add_node(m, &frontier);
    }
    if (n->M.sq[n->pos-1] != 'x')
    {
      node * m = malloc(sizeof(node));
      m->type = 'L';
      m->pos = n->pos - 1;
      strcpy(m->M.sq,n->M.sq);
      m->action_cost = 1;
      m->time = n->time+1;
      m->parent = n;
      m->g = calcg(m) + n->g;
      m->h = calch(m);
      m->f = m->g + m->h;
      printd("Left: g:%d, h:%d, f:%d\n", m->g, m->h, m->f);
      add_node(m, &frontier);
    }
    if (n->M.sq[n->pos+1] != 'x')
    {
      node * m = malloc(sizeof(node));
      m->type = 'R';
      m->pos = n->pos + 1;
      strcpy(m->M.sq,n->M.sq);
      m->action_cost = 1;
      m->time = n->time+1;
      m->parent = n;
      m->g = calcg(m) + n->g;
      m->h = calch(m);
      m->f = m->g + m->h;
      printd("Right: g:%d, h:%d, f:%d\n", m->g, m->h, m->f);
      add_node(m, &frontier);
    }
    if (n->M.sq[n->pos] == 'D')
    {
      node * m = malloc(sizeof(node));
      m->type = 'S';
      m->pos = n->pos;
      strcpy(m->M.sq,n->M.sq);
      m->M.sq[m->pos] = 'C';
      m->action_cost = 1;
      m->time = n->time+1;
      m->parent = n;
      m->g = calcg(m) + n->g;
      m->h = calch(m);
      m->f = m->g + m->h;
      printd("Suck: g:%d, h:%d, f:%d\n", m->g, m->h, m->f);
      add_node(m, &frontier);
    }
    if (1) /* noop */
    {
      node * m = malloc(sizeof(node));
      m->type = 'N';
      m->pos = n->pos;
      strcpy(m->M.sq,n->M.sq);
      m->action_cost  = 0;
      m->time = n->time+1;
      m->parent = n;
      m->g = calcg(m) + n->g;
      m->h = calch(m);
      m->f = m->g + m->h;
      add_node(m, &frontier);
    }
    current = best(&frontier);
    printd("Exploring a '%c'\n", current->type);
  }
  print_path(current);
  return 0;
}


