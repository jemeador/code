/*
 * Author: Jeremy Meador
 * Program: 12000 "K-transformed" Permutations
 * Date: 9-8-11
 * Description: Solved using fast matrix exponentiation
 */


#include <stdlib.h>
#include <stdio.h>

#define DEBUG 0
#define printd if (DEBUG) printf
#define C 73405

typedef struct
{
  int size;
  int **e;
} Matrix;

/*
 * isStep:
 *   Checks whether or not state b can be reached from state a after adding a 
 *  number.
 *   Using this function we can build a matrix of states and the states that 
 *  follow them.
 * returns: 1 if a->b, 0 if not
 *
 * Ex: k = 2
 * We can get from state 1010 to state 0110 (e.g. 2010000 to 20130000, where 1
 *                                              | ^^^^      | ^^^^
 * means a space is occupied or inaccessible).
 *  States such as 0101 (where the first bit is a 0) can only transition to the
 * state that is the shift of itself (1010).
 *  I reverse the states visually (010110 becomes 011010) so that I can use 
 * bitwise arithmetic.
 */
int isStep(char a, char b)
{
  int x;
  if (a % 2 == 0)
  {
    /*The first slot needs to be occupied since we will be shifting away from 
     * it, return b == shifted state of a*/
    return !((a>>1)^b);
  }
  /*Set state z to the shifted state of a XOR b*/
  char z = (a>>1)^b;
  /*A valid transition should be the difference of a single slot, check to see 
   * if z is a power of two (01 and 10 and 0100000 are powers of 2)*/
  return !((z<=0)||(z&(z-1)));
}

/*
 * makeVector:
 *   Builds a vector v of possible states given a k( 1<= k <= 3) and returns a 
 *  length z
 * return: v (vector of possible states), z (length of vector)
 *
 * Valid states follow this one rule
 *     They must have k occupied or inaccesible spots, and k+1 open spots for 
 *    the current number. The last slot in a state is always a zero however, 
 *    since it has just shifted into view.
 *   
 * We will only need to keep track of 2*n bits per state, which will never 
 *  exceed a byte for k <= 3.
 *
 * k=1 states: 10, 01
 * k=2 states: 1100, 1010, 1001 ... 0101, 0011
 * k=3 states: 111000, 110100, 110010 ... 001011, 000111
 */
void makeVector(int k, char * v, int * z)
{
  char a;
  int j, x;
  *z=0;
  /* Loop over all combinations of 1s and 0s*/
  for(a = (1<<k)-1; a < 1<<(2*k);a++)
  {
    x=0;
    /*Count the number of 1s in state a*/ 
    for (j=1;j < 1<<(2*k);j=j<<1)
      x+=((j&a)==j);
    if (k==x)
    {
      /*Add a to the vector and iterate the count*/
      v[(*z)++] = a;
    }
  }
}

/* Does what it says, multiplies two matrices together.
 * Don't look too much into it.
 */
Matrix * mult_mat(Matrix * M1, Matrix * M2)
{
  int i,j,k,sum;
  int s = M1->size;
  Matrix * M3 = (Matrix *)malloc(sizeof(Matrix));
  M3->size = M1->size;
  M3->e = (int **)malloc(sizeof(int *)*s);
  for (i=0;i<s;i++)
  {
    M3->e[i] = (int *)malloc(sizeof(int)*s);
    for (j=0;j<s;j++)
    {
      int sum = 0;
      for (k=0;k<s;k++)
      {
        /*Turns out there's numbers under our constant that are over maxint when
         * squared!*/
        long long int exp1 = (M1->e)[i][k]%C;
        long long int exp2 = (M2->e)[k][j]%C;
        long long int product = (exp1 * exp2)%C;
        sum = (sum + product)%C;
      }
      (M3->e)[i][j] = sum;
    }
  }
  return M3;
}

/* Magic (See "Exponentiation by squaring" on Wikipedia)
 * 
 * The key to this problem: if we multiply our state matrix by itself
 * we get the number of different ways there are to get from any one state 
 * to another. We can just exponentiation the crap out of it until we get what
 * we want.
 */
Matrix * fastExp(Matrix * M, int p)
{
  if (M == NULL)
    printd("Null Matrix! %d", p);
  Matrix * M2, * M3;
  printd("%d\n", p);
  if (p==1)
  {
    return M; 
  }
  if (p % 2 == 1)
  {
    Matrix * Mtemp = fastExp(M,(p-1)/2);
    M2 = mult_mat(Mtemp,Mtemp);
    M3 = mult_mat(M,M2);
  }
  else
  { 
    M = fastExp(M,p/2);
    M3 = mult_mat(M,M);
  }
  return M3; 
}

void run()
{
  Matrix M, *newM;
  int n, k, z, i, j;
  char v[50];
  scanf("%d %d", &n, &k);
  if ((k>0)&&(n>0))
  {
    makeVector(k,v,&z);
    M.size = z;
    M.e = (int **)malloc(sizeof(int*)*z);
    for (i=0;i<z;i++)
    {
      M.e[i] = (int *)malloc(sizeof(int)*z);
      for(j=0;j<z;j++)
      {
        M.e[i][j] = isStep(v[i],v[j]);
      }
    }
    newM = fastExp(&M,n);
    /* The first state in the vector is the start state. It's also the end 
     * state! The magic number is at e[0][0]*/
    printf("%d\n",newM->e[0][0]);
  }
  else
  {
    printf("1\n");
  }
}

int main()
{
  int count, j;
  scanf("%d", &count);
  for (j=0;j<count;j++)
  {
    printf("Case %d: ", j+1);
    run();
  }
  return 0;
}

