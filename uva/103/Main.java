//import java.util.Scanner;
//import java.util.ArrayList;
import java.util.*;
public class Main
{
  static public class Box implements Comparable<Box>
  {
    public ArrayList<Integer> d;
    public int id;
    public Box(int i)
    {
      id = i;
      d = new ArrayList<Integer>();
    }

    public int sum()
    {
      int s = 0;
      for (int i=0;i<d.size();i++)
      {
        s+= d.get(i);
      }
      return s;
    }

    public boolean fitsIn(Box that)
    {
      boolean fits = true;
      for (int j=0;j<d.size();j++)
      {
        if (this.d.get(j) >= that.d.get(j))
        {  
          fits = false;
          break;
        }
      }
      return fits;
    }

    public int compareTo(Box o)
    {
      return this.sum() - o.sum();
    }
  }

  public String chain(ArrayList<Box> a, int start)
  {
    String best = "";
    for (int k=start;k<a.size();k++)
    {
      Box b = a.get(k);
      for (int i=k+1;i<a.size();i++)
      {
        String c;
        boolean fits = true;
        for (int j=0;j<b.d.size();j++)
        {
          if (b.d.get(j) <= a.get(i).d.get(j))
          {
            fits = false;
            break;
          }
        }
        if (fits)
          c = chain(a,start+1);
        if (c.length() > best.length()
          
      }
    }
      
  }
  
  public static void main(String[] args)
  {
    Scanner in = new Scanner(System.in);
    while (in.hasNextInt())
    {
      int k = in.nextInt();
      int n = in.nextInt();
      ArrayList<Box> b = new ArrayList<Box>();
      for (int j=0;j<k;j++)
      {
        b.add(new Box(j+1));
        for (int i=0;i<n;i++)
        {
          b.get(j).d.add(in.nextInt());
        }
        Collections.sort(b.get(j).d);
      }
      Collections.sort(b);
      for (Box box:b)
      {
        for (int i:box.d)
        {
          System.out.println(i + " ");//b.get(j).d.add(in.nextInt());
        }
        System.out.println();
      }
    }

  }
}




