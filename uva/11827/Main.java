/*
 * Author: Jeremy Meador
 * Problem: 11827 Maximum GCD
 */


import java.util.Scanner;
import java.util.ArrayList;


public class Main
{
  public static int gcd(int a, int b, int max)
  {
    if (a==0||b==0)
      return 0;
    if (a < b)
    {
      int t = a;
      a = b;
      b = t;
    }
    if (b<=max)
      return 0;
    int c = a%b;
    if (c == 0)
    {
      return b;
    }
    return gcd(b,c,max);
  }
  
  public static void main(String[] args)
  {
    Scanner in = new Scanner(System.in);
    int count = in.nextInt();
    in.nextLine();
    while ((count != 0)&&(in.hasNextLine()))
    {
      ArrayList<Integer> nums = new ArrayList<Integer>();
      int max = 0;
      Scanner line = new Scanner(in.nextLine());
      while (line.hasNextInt())
      {
        nums.add(line.nextInt());
      }
      for (int j=0;j<nums.size();j++)
        for (int i=j+1;i<nums.size();i++)
        {
          int g;
          if ((g = gcd(nums.get(j),nums.get(i), max)) != 0)
          {
            max = g;
          }
        }
      System.out.println(max);
      count--;
    }
  }
}





