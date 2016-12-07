class OC
{
    private int n;
    private IC  myIC;

	public OC() {
		System.out.println("In Constructor for OC");
	}
   
    public int OCfunc (int x, int y)
    {
        int retval = 0;
        int compare = 0;
		System.out.println("In OCFUNC() with x = "+x+", y = "+y+", retval = "+retval+
				", and compare = "+compare);
        System.out.println ("Before WHILE, n="+n+" about to test (n != 3)");
        while (n != 3)
        {
			System.out.println("In WHILE, n="+n+", (n != 3) is true ");
			try
            {
                System.out.println ("Entering TRY block");
				System.out.println("Calling ICFUNC() from OCFUNC()");
				retval = myIC.ICfunc (n, x, y);///called from IC
				System.out.println("Returning from ICFUNC() to OCFUNC() retval = "+retval);
				System.out.println("");
				System.out.println("Calling COMPAREFUNC() from OCFUNC()");
				compare = myIC.CompareFunc (retval);//called from IC
				System.out.println("Returning from COMPAREFUNC() to OCFUNC() compare = "+compare);
				System.out.println();
				System.out.println ("Exiting TRY block");
            }//try
            catch (Exception ex)
            {
				System.out.println ("IN CATCH block, exception caught: " + ex);
                retval = 0;
            }//catch

            n = n + 1;
			System.out.println("End of WHILE, i equals "+n+", retesting (n != 3)");
		}//while
		System.out.println("End of OCFUNC(), returning to caller with n = "+n+", retval = "+retval+" and compare = "+compare);
		return retval;
    }//OCfunc

    public void OCinit ()
    {
		System.out.println("In OCINIT()");
		n = 0;
		System.out.println("About to create object of class IC");
		myIC = new IC ();
		System.out.println("Created object of class IC");
		System.out.println("End of OCINIT(), returning to caller");
	}//OCinit()
}//OC
