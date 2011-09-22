/*
 * Author: Jeremy Meador
 * Problem: 18300 Contract Revision
 *
 */

import java.util.Scanner;
import java.util.ArrayList;

public class Main
{
  public static void main(String[] args)
  {
    Scanner in = new Scanner(System.in);
    String a = in.next();
    String num = in.next();
    while (!(a.equals("0"))&&(!num.equals("0")))
    {
      in.nextLine();
      num = num.replaceAll(a,"");
      for (int j = 0; j<num.length();)
      {
        if (num.charAt(j) == '0')
          num = num.substring(1);
        else
          break;
      }
      if (num.length() == 0)
        num = "0";
      System.out.println(num);  
      a = in.next();
      num = in.next();
    }
  }
}




