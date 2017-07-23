/* package codechef; // don't place package name! */
 
import java.util.*;
import java.lang.*;
import java.io.*;
 
/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
	public static void main (String[] args) throws java.lang.Exception
	{
		int t,i ;
       char ch ;
       Scanner sc=new Scanner(System.in) ;
       t=sc.nextInt() ;
       while(t!=0)
       {
           t-- ;
           int tot=1,big=1,small=1 ;
           String s=sc.next() ;
           for(i=0;i<s.length();i++)
           {
               ch=s.charAt(i) ;
           
               
               if(ch=='>')
               {
                   small=1 ;
                   big++ ;
                   if(big>tot)
                       tot=big ;
               }
               
               if(ch=='<')
               {
                   big=1 ;
                   small++ ;
                   if(small>tot)
                       tot=small ;
 
               }
           }
           System.out.println(tot);
       }
	}
}
 
