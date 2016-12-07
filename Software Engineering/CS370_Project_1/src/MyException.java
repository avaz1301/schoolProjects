
class MyException extends Exception
{
    public MyException ()
    {
        super ();
        System.out.println("In constructor of class MyException");
    }//default constructor

    public MyException (String s)
    {
        super (s);
        System.out.println("In constructor of class MyException, string parameter '"+s+"' passed");
    }//constructor
}//MyException

//Angelo Zamudio CS370 SPRING 16’
