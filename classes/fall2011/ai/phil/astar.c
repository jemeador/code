/*
 * Author: Phillip LeBlanc
 * Problem: 3c Homework 1
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEBUG 1
#define printd if (DEBUG) printf

#define DIRTY 10
#define CLEAN 11


struct node {
  char world[9];
  char agent_pos;
  struct node *parent;
};

typedef struct {
  struct node *n;
  int score;
} frontier;

enum actions { suck=0, down, left, right, up, noop=5 };
int applyAction(enum actions d, struct node *n);
int cost(enum actions d, struct node *n, int old_score);
int goalCheck(struct node *n);
void expand(struct node *n);
int dummyCheck();
int h(struct node *n);

frontier f[100000];

// The mailbox array is used to circumvent a lot of code
// that would otherwise be necessary to check to see if the
// agent can move left or right and not go past the boundary.
char mailbox15[9] = { 1, 2, 3,
                      6, 7, 8,
                      11, 12, 13 };
char mailbox[15] = { 0, 1, 1, 1, 0,
                     0, 1, 1, 1, 0,
                     0, 1, 1, 1, 0 };

char initial_world[9] = { DIRTY, DIRTY, DIRTY,
                  CLEAN, CLEAN, CLEAN,
                  CLEAN, CLEAN, CLEAN};


int numDirtySquares(struct node *n) {
  if (n == NULL)
    return 0;
  int dirty = 0;
  for (int i = 0; i < 9; i++)
    if (n->world[i] == DIRTY)
      dirty++;
  return dirty;
}

struct node *astar(struct node *n) {
  struct node *goal;
  expand(n);

  while (goalCheck(goal) != 1) {
    if (dummyCheck() == 0)
    {
      printd("Exceeded frontier limit\n");
      exit(1);
    }
    int min = 100000;
    struct node *best;
    for (int i = 0; i < 100000; i++) {
      if (f[i].score < min && f[i].score > -1) {
        best = f[i].n;
        min = f[i].score;
      }
    }
    expand(best);
  }
  return goal;
}

int dummyCheck() {
  for (int i = 0; i < 100000; i++) {
    if (f[i].score == -1)
      return 1;
  }
  return 0;
}

int goalCheck(struct node *n) {
  for (int i = 0; i < 100000; i++) 
    if (f[i].score == 0) {
      n = f[i].n;
      return 1;
    }
  return 0;
}

void addToFrontier(struct node *n, int score) {
  for (int i = 0; i < 100000; i++) {
    if (f[i].score == -1) {
      f[i].n = n;
      f[i].score = score;
      return;
    }
  }
}

int removeFromFrontier(struct node *n) {
  int old_score;
  for (int i = 0; i < 100000; i++) {
    if (f[i].n == n) {
      old_score = f[i].score;
      f[i].score = -1;
      return old_score;
    }
  }
}

void expand(struct node *n) {
  int old_score = removeFromFrontier(n);
  struct node *newNode = malloc(sizeof(struct node));
  memcpy(newNode, n, sizeof(struct node));
  for (int i = 0; i < 6; i++) {
    if (!applyAction(i, newNode))
      continue;
    newNode->parent = n;
    addToFrontier(newNode, cost(i, newNode, old_score) + h(newNode));
    newNode = malloc(sizeof(struct node));
    memcpy(newNode, n, sizeof(struct node));
  }

}

int cost(enum actions d, struct node *n, int old_score) {
  int cost = 1;
  if (d == noop)
    cost = 0;

  if (n->parent != NULL)
    return cost + 2*numDirtySquares(n) + old_score;
  else
    return cost + 2*numDirtySquares(n);
}

int h(struct node *n) {
  return 2*numDirtySquares(n) - 1;
}

// The node passed in is converted to have the new
// state, or is unchanged if the action is not valid
int applyAction(enum actions d, struct node *n) {
  switch (d) {
    case up:
      if (n->agent_pos < 3)
        return 0;
      n->agent_pos -= 3;
      return 1;
    case down:
      if (n->agent_pos > 5)
        return 0;
      n->agent_pos += 3;
      return 1;
    case left:
      if (mailbox[mailbox15[n->agent_pos - 1]]) {
        n->agent_pos--;
        return 1;
      }
      else
        return 0;
    case right:
      if (mailbox[mailbox15[n->agent_pos + 1]]) {
        n->agent_pos++;
        return 1;
      }
      else
        return 0;
    case noop:
      return 1;
    case suck:
      n->world[n->agent_pos] = CLEAN;
      return 1;
  }
  return 0;
}
void print_path(struct node * n)
{
  int i,j;
  if (n == NULL)
    return;
  print_path(n->parent);
  /*if (n->type != 'N')
  {*/
    for (j=0;j<3;j++)
    {
      for (i=0;i<3;i++)
      {
        if (n->agent_pos == j*3+i)
          printf("O");
        else 
          printf("%c",n->world[j*3+i]);
      }
      printf("\n");
    }
  return;
}
int main() {
  struct node *n;
  struct node *goal;
  for (int i = 0; i < 100000; i++)
    f[i].score = -1;
  n = malloc(sizeof(struct node));
  n->parent = NULL;
  memcpy(n->world, initial_world, sizeof(char)*9);
  n->agent_pos = 4;
  goal = astar(n);
  print_path(goal);
}

