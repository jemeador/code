import java.util.Scanner;
import java.util.ArrayList;

public class Main
{
  public static void main(String[] args)
  {
    Scanner in = new Scanner(System.in);
    int size = in.nextInt(); 
    ArrayList<ArrayList<Integer>> stack = new ArrayList<ArrayList<Integer>>();
    for (int j=0;j<size;j++)
    {
      ArrayList<Integer> al = new ArrayList<Integer>();
      al.add(j);
      stack.add(al);
    }
    in.nextLine();
    String line = in.nextLine(); 
    Scanner lineIn = new Scanner(line);
    String c1 = lineIn.next();
    while (!c1.equals("quit"))
    {
      int n1 = lineIn.nextInt();
      String c2 = lineIn.next();
      int n2 = lineIn.nextInt();
      ArrayList<Integer> s1 = null, s2 = null, temp = null;
      for (int j=0;j<size;j++)
      {
        temp = stack.get(j);
        if (s1 == null && temp.contains(n1))
          s1 = temp;
        if (s2 == null && temp.contains(n2))
          s2 = temp;
      }
      if (s1 != s2)
      {
        if (c1.equals("move")) 
        {
          int i = s1.indexOf(n1)+1;
          while(i<s1.size())
          {
            int removedBlock = s1.remove(i);
            stack.get(removedBlock).add(removedBlock);
          }
        }
        if (c2.equals("onto")) 
        {
          int i = s2.indexOf(n2)+1;
          while(i<s2.size())
          {
            int removedBlock = s2.remove(i);
            stack.get(removedBlock).add(removedBlock);
          }
        }
        int i = s1.indexOf(n1);
        while(i<s1.size())
        {
          s2.add(s1.remove(i));
        }
      }
      line = in.nextLine();
      lineIn = new Scanner(line);
      c1 = lineIn.next();
    }
    for (int j=0;j<size;j++)
    {
      System.out.print(j + ":");
      for (int i=0;i<stack.get(j).size();i++)
        System.out.print(" " + stack.get(j).get(i));
      System.out.println();
    }
  }
}


