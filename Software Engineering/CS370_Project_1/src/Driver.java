import java.util.*;
import java.io.File;
import java.io.FileNotFoundException;


public class Driver {
    public static void main(String args[]) throws MyException, FileNotFoundException {
        int classNum  = 0, methodNum = 0, retValue=0;
        MyException myEx;
        IC myIC1 = new IC();
        OC myOC  = new OC();
        Scanner input = new Scanner(new File(args[0]));
        while (input.hasNextLine()) {
            Scanner lineRead = new Scanner(input.nextLine());
            lineRead.useDelimiter(":| ");

            while (lineRead.hasNext()) {
                classNum = lineRead.nextInt();
                if (classNum == 0) {
                    System.out.println(lineRead.next());
                }//if classNum = 0


                else if (classNum == 1) {
                    lineRead.next();
                    methodNum = lineRead.nextInt();
                    lineRead.next();
                    if (methodNum == 1) {
                        System.out.println("About to create object of class MyException");
                        myEx = new MyException();
                        System.out.println("Created object of class MyException");
                        System.out.println();
                    } else if (methodNum == 2) {
                        System.out.println("About to create object of class MyException passing string argument s");
                        myEx = new MyException(lineRead.next());
                        System.out.println("Created object of class MyException");
                        System.out.println();
                    }//else if
                }//else if numClass = 1


                else if (classNum == 2) {
                    lineRead.next();
                    methodNum = lineRead.nextInt();
                    if (methodNum == 0) {
                        System.out.println("About to create object of class IC");
                        myIC1 = new IC();
                        System.out.println("Created object of class IC");
                        System.out.println();
                    } else if (methodNum == 1) {
                        lineRead.next();
                        try {
                            System.out.println("Calling ICFUNC()");
                            retValue = myIC1.ICfunc(lineRead.nextInt(), lineRead.nextInt(), lineRead.nextInt());
                            System.out.println("Returned from IC with value "+retValue);
                        } catch (MyException e) {
                            System.out.println("Threw MyException");
                        } catch (Exception e) {
                            System.out.println("Threw Exception");
                        }//catch
                        System.out.println();
                    } else if (methodNum == 2) {
                        lineRead.next();
                        System.out.println("Calling COMPAREFUNC()");
                        int num=myIC1.CompareFunc(lineRead.nextInt());
                        System.out.println("Returned from COMPAREFUNC() with value "+num);
                        System.out.println();
                    }//else if
                }//else if classNum = 2


                else if (classNum == 3) {
                    lineRead.next();
                    methodNum = lineRead.nextInt();
                    if (methodNum == 0) {
                        System.out.println("About to create object of class OC");
                        myOC = new OC();
                        System.out.println("Created object of class OC");
                        System.out.println();
                    }else if (methodNum == 1) {
                        try {
                            lineRead.next();
                            System.out.println("Calling OCFUNC()");
                            retValue = myOC.OCfunc(lineRead.nextInt(), lineRead.nextInt());
                            System.out.println("Returning from OCFUNC() with value " + retValue);
                            System.out.println();
                        }catch (Exception e) {
                            System.out.println("Threw Exception");
                        }//catch
                    } else if (methodNum == 2) {
                        lineRead.next();
                        System.out.println("Calling OCINIT()");
                        myOC.OCinit();
                        System.out.println("Returning from OCINIT()");
                        System.out.println();
                    }//else if methodNum
                }//else if classNum = 3
                break;
            }//while temp
        }//while input
    }//main
}//Driver

//Angelo Zamudio CS370 SPRING 16’
