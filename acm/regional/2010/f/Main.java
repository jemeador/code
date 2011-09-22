/*
 * Author: Jeremy Meador
 * Problem: If You Can't Stand the Heat
 */


import java.util.Scanner;
import java.util.ArrayList;

public class Main
{
  public static class Token
  {
    public Token next;
    public String val;

    public Token(String s)
    {
      val = string;
      next = null;
    }
  }
  
  public static class Exp extends Value
  {
    public Value left;
    public Value right; 
    
    Exp(String s)
    {
      switch (s)
      {
        case "(": 
      }
    }
    
    public Token accepts(Token t)
    {
      Token last = left.accepts(Token t);
      if (right)
        return right.accepts(Token last.next);
      return left;  
    }
  }

  public static class Value
  {
    public String val;

    public Value()
    {
      val = null;
    }
  
    public Value(String s)
    {
      val = s;
    }

    public Token accepts(Token t)
    {
      if (v && t.val.equals(v))
        return t;
      return null;
    }
  }

  public static class Or extends Value
  {

    public Or()
    {
      
    }

    public boolean accepts(Token s)
    {
      return (s.equals(val)||s.equals(val));
    }
  }
  
  public static void main(String[] args)
  {
    Scanner in = new Scanner(System.in);
    int count = in.nextInt();
    in.nextLine();
    while (count != 0)
    {
      String name = in.nextLine();
      String recipe = in.nextLine();
      Scanner r = = new Scanner(recipe);
      Exp e = null;
      e = new Exp(r.next());
      int attempts = in.nextInt();
      System.out.println("Boudreau and Thibodeaux attempt to make " + name + ".");
      for (int j = 0;j<attempts;j++)
      {
        Scanner a = new Scanner(in.nextLine());
        Token t = null, n = null;
        t = n = new Token(a.next);
        while (a.hasNext())
        {
          n.next = new Token(a.next());
          n = n.next;
        }
        if (e.accepts(t))
          System.out.println("--> Attempt number " + (j+1) + " resulted in success.");
        else
          System.out.println("--> Attempt number " + (j+1) + " resulted in failure.");
      }
      count--;
    }
  }
}





