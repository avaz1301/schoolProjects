class IC
{
	private int retval;

	public IC(){System.out.println("In constructor for IC");}

	public int ICfunc (int n, int x, int y) throws MyException
	{	
		System.out.println("In ICFUNC() from caller with n = "+n+", x = "+x+", and y = "+y);
		System.out.println("Before SWITCH about to test n, which equals " +n);
		switch (n)
        {
			case 1:
			{
                System.out.println("In SWITCH. Entering CASE n=1");
				System.out.println("Before IF, testing if x which equals "+x+" == 0 && if y which equals "+y+" == 0 is true");
				if ((x == 0) && (y == 0))
				{
					System.out.println("About to create object of class MyException");
					throw new MyException ("all zero");

				}
				else if (x <= y)
				{
					System.out.println("In ELSE IF, x = "+x+" and y = "+y+", (x == 0) && (y == 0) is false and (x <= y)is true.");
					retval = x;
                    System.out.println("End of ICFUNC() returning to caller with retval="+retval);
					return retval;
				}
				else
				{
					System.out.println("In ELSE, x = "+x+" and y = "+y+", (x == 0) && (y == 0) is false and (x <= y) is also false.");
					retval = y;
                    System.out.println("End of ICFUNC() returning to caller with retval="+retval);
					return retval;
				}
			}//case1

			case 2:
			{
				System.out.println("In SWITCH. Entering CASE n=2");
				int i;
				System.out.println("Before IF, about to test if (x == y).");
				if (x == y)
				{
					System.out.println("In IF, x = "+x+" and y = "+y+", (x == y) is true.");
					System.out.println("About to create object of class MyException");
					throw new MyException ("all equal");
				}//if
				else if (x < y)
				{
					System.out.println("In ELSE IF,x = "+x+" and y = "+y+" , (x == y) is false and (x < y) is true");
					System.out.println("Before FOR, about to test i; which is equal to "+ x +" while i > y which is equal to "+y+".");
					for (i = x; i < y; i++)
					{
						System.out.println("In FOR, ("+i+" < "+y+") is true");
						System.out.println("    Before IF, about to test if (i > i+5) => i = "+i+", x+5 = "+(x+5));
						if (i > x + 5)
						{
							System.out.println("    In IF, ("+i+" > "+(x+5)+"), (i > x+5) is true.");
							retval = x + 5;
                            System.out.println("End of ICFUNC() returning to caller with retval="+retval);
							return retval;
						}
						System.out.println("End of FOR, i = "+(i+1)+" and y = "+y+", testing if ("+i+" < "+y+")");
					}//for
                    System.out.println("After FOR, i = "+i);
                    retval = i;
                    System.out.println("End of ICFUNC() returning to caller with retval = "+retval);
					System.out.println();
					return retval;
				}//else if
				else
				{
					System.out.println("Inside ELSE, x = "+x+" and y = "+y+", (x == y) & (x < y) are both false.");
					retval = n;
                    System.out.println("End of ICFUNC() returning to caller with retval="+retval);
					return retval;
				}//else
			}//case2

			default:
			{
				System.out.println("In SWITCH. Entering DEFAULT case, CASE 1 (n=1) and CASE 2 (n=2) are false, n = "+ n);
                System.out.println("End of ICFUNC() returning to caller with value 0");
				return 0;
			}//default
		} // end switch
    } // end method

	public int CompareFunc (int returnVal)
	{
		System.out.println("In function COMPAREFUNC(), using parameter returnVal which equals "+returnVal);
		System.out.println("Before IF, about to test if retval which equals "+retval+" is equal to "+returnVal);
		if (retval == returnVal){
			System.out.println("In IF, (retval == returnVal) is true");
            System.out.println("End of COMPAREFUNC() retuning to caller with value 1");
            return 1;
		}else{
			System.out.println("In ELSE. (retval != returnVal) is true, (retval == returnVal) is false");
            System.out.println("End of COMPAREFUNC() returning to caller with value 0");
            return 0;
		}//else
    }//CompareFunc

} // end class
