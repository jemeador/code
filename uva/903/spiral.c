#include <stdlib.h>
#include <stdio.h>
typedef struct{
   int x;
   int y;
}point;

int getshell(int a) {
  int j;
  for (j=0;j<32768;j++) /*possible optimization: start at the ceiling of the sqrt of a instead of 0*/
  {
    if (a<=(2*j+1)*(2*j+1))
      return j; 
  }
  printf("logic error getshell(%d)", a);
}

void getcoords(int a, point * p) {
  int shell = getshell(a);
  int x = shell;
  int y = shell-1;
  int start = (2*(shell-1)+1)*(2*(shell-1)+1)+1;
  if (a == 1)
  {
    p->x = 0;
    p->y = 0;
    return;
  }
  while ((start < a)&&(y>-shell))
  {
    y--;
    start++;
  }
  while ((start < a)&&(x>-shell))
  {
    x--;
    start++;
  }
  while ((start < a)&&(y<shell))
  {
    y++;
    start++;
  }
  while ((start < a)&&(x<=shell))
  {
    x++;
    start++;
  }
  if (start < a)
    printf("logic error getcoords");
  p->x = x;
  p->y = y;
}

int getval(point * p)
{
  int shell;
  int start;
  int x, y, absxg, absyg;
  int xgoal = p->x;
  int ygoal = p->y;
  if ((xgoal == 0)&&(ygoal == 0))
    return 1;
  if (xgoal < 0)
    absxg = -xgoal;
  else
    absxg = xgoal;
  if (ygoal < 0)
    absyg = -ygoal;
  else
    absyg = ygoal;
  shell = absxg;
  if (absyg > shell)
    shell = absyg;
  start = (2*(shell-1)+1)*(2*(shell-1)+1)+1;
  x = shell;
  y = shell-1;
  while ((y>-shell)&&(!((y==ygoal)&&(x==xgoal))))
  {
    y--;
    start++;
  }
  while ((x>-shell)&&(!((y==ygoal)&&(x==xgoal))))
  {
    x--;
    start++;
  }
  while ((y<shell)&&(!((y==ygoal)&&(x==xgoal))))
  {
    y++;
    start++;
  }
  while ((x<=shell)&&(!((y==ygoal)&&(x==xgoal))))
  {
    x++;
    start++;
  }
  if (x > shell)
  {
    printf("logic error getval(%d,%d) of shell %d", xgoal, ygoal, shell);
  }
  return start;
}

int main() {
  int n;
  while (scanf("%d", &n) > 0)
  {
    point p = {0,0};
    getcoords(n,&p);
    point topleft = {p.x-1,p.y+1};
    point left = {p.x-1,p.y};
    point botleft = {p.x-1,p.y-1};
    point top = {p.x,p.y+1};
    point bot = {p.x,p.y-1};
    point topright = {p.x+1,p.y+1};
    point right = {p.x+1,p.y};
    point botright = {p.x+1,p.y-1};
    printf("%d;%d;%d;\n",getval(&topleft),getval(&top),getval(&topright));
    printf("%d;%d;%d;\n",getval(&left),getval(&p),getval(&right));
    printf("%d;%d;%d;\n",getval(&botleft),getval(&bot),getval(&botright));
  }
	return 0;
}
