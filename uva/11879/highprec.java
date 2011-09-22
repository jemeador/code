/*
 * Author: Jeremy Meador
 * Problem: 11821 High Precision Number
 *
 */

import java.util.Scanner;
import java.util.ArrayList;

class Main
{
  
  static private class Precision
  {
    public String num;
    public int sign;
    public int decpt;
    
    public Precision(String val)
    {
      num = val;
      this.removeSign();
      this.removeDecimal();
    }

    public void removeDecimal()
    {
      int index = num.indexOf('.');
      if (index == -1)
        decpt = num.length();
      else
        decpt = index;
      num = num.replace(".","");

      //System.out.println(this.num + " " + decpt);
      //System.out.println(that.num + " " + that.decpt);
    }

    public void removeSign()
    {
      if (num.charAt(0) == '-')
        sign = -1;
      else
        sign = 1;
      num = num.replace("-","");
    }
    
    public void align(Precision that)
    {

      //System.out.println(this.num + " " + decpt);
      Precision g, l;
      StringBuffer zeroString;
      int zeros = decpt-that.decpt;
  
      if (zeros < 0)
      {
        g = that;
        l = this;
        zeros *= -1;
      }
      else
      {
        g = this;
        l = that;
      }
      if (zeros != 0)
      {
        zeroString = new StringBuffer(zeros);
        for (int j=0;j<zeros;j++)
        {
          zeroString.append('0');
        }
        l.decpt += zeros;
        l.num = zeroString + l.num;
      }

      //System.out.println(this.num + " " + decpt);
      zeros = this.num.length()-that.num.length();
      if (zeros < 0)
      {
        g = that;
        l = this;
        zeros *= -1;
      }
      else
      {
        g = this;
        l = that;
      }
      if (zeros != 0)
      {
        zeroString = new StringBuffer(zeros);
        for (int j=0;j<zeros;j++)
        {
          zeroString.append('0');
        }
        l.num = l.num + zeroString;
      }
 
      //System.out.println("After format" + this.num + " " + this.decpt);
      //System.out.println(that.num + " " + that.decpt);
      //System.out.println(this.num + " " + decpt);
    }

    public void add(Precision that)
    {
      
      //System.out.println(this.num + " " + this.decpt);
      //System.out.println(that.num + " " + that.decpt);
      StringBuffer sum = new StringBuffer(this.num.length()+1);
      if (this.sign == that.sign)
      {
        int firstDigit = add(that,sum,0);
        if (firstDigit == 1)
        {
          sum.append(1);  
          this.decpt+=1;
        }
        sum.reverse();
      }
      else
      {
        String thatNum = that.num;
        if (this.num.compareTo(that.num)<0)
        {
          thatNum = this.num;
          this.num = that.num;
          this.sign = that.sign;
        }
        this.sub(thatNum, sum, 0);
        sum.reverse();
      }
      this.num = sum.toString();
      //System.out.println("After addition:");
      //System.out.println(this.num + " " + this.decpt);
      //System.out.println(that.num + " " + that.decpt);
    }

    private int add(Precision that, StringBuffer sum, int j)
    {
      if (j==this.num.length())
        return 0;
      int next = this.num.charAt(j)+that.num.charAt(j)-'0'-'0' + add(that,sum,j+1);
      int carry = 0;
      if (next > 9)
      {
        carry = 1;
        next = next - 10;
      }
      sum.append(next);
      return carry;
    }

    private int sub(String thatString, StringBuffer sum, int j)
    {
      if (j==this.num.length())
        return 0;
      int next = this.num.charAt(j)-thatString.charAt(j) - sub(thatString,sum,j+1);
      int borrow = 0;
      if (next < 0)
      {
        borrow = 1;
        next = next + 10;
      }
      sum.append(next);
      return borrow;
    }

    public void clean()
    {
      int j = 0, i = num.length()-1;
      while (num.charAt(j) == '0' && decpt > 1)
      {
        j++;
        decpt--;
      }
      while (i>=decpt && num.charAt(i) == '0')
      {
        i--;
      }
      if (i<=j)
      {
        num = "0";
        decpt = 1;
        sign = 1;
      }
      else
        num = num.substring(j,i+1);
    }

    public String toString()
    {
      clean();
      StringBuffer s = new StringBuffer(num);
      if (decpt < s.length())
        s.insert(decpt,'.');
      if (sign == -1)
        s.insert(0,'-');  
      return s.toString();
    }
  }

  public static void main(String[] args)
  {
    //try{
    Scanner in = new Scanner(System.in);
    int count = in.nextInt();
    Precision p[] = new Precision[2];
    while (count > 0)
    {
      p[0] = new Precision("0");
      p[1] = new Precision("0");  
      do 
      {
        //in.nextLine();
        p[1].align(p[0]);
        p[0].add(p[1]);
        p[1] = new Precision(in.next());
      } while (!p[1].num.equals("0"));
      System.out.println(p[0]);
      count--;
    }
    //}catch(Exception e){}
  }
}




