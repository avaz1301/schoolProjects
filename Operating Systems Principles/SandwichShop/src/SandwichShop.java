

public class SandwichShop {
    //customer_in_shop makes sure there is only one customer in shop
    public static Semaphore customer_in_shop=new Semaphore(1);
    //notify_employee controls the flow of the employee.
    public static Semaphore notify_employee = new Semaphore(0);
    //customer_pay controls when the customer is allowed to leave the shop.
    public static Semaphore customer_pay = new Semaphore(0);

    public static void main(String[] args) {
        if (args.length != 1) {
            printUsage();
        }

        int num = 0;
        try {
            num = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            printUsage();
        }

        System.out.println("Customer:\t\t\t\t\t\t\t\t\t\t\t| Employee:");
        System.out.print("Traveling\tArrived\t\tOrdering\tBrowsing\tAt Register\tLeaving");
        System.out.println("\t\t| Waiting\tSandwich Making\t\tAt Register\tPayment Accepted");
        System.out .println("---------------------------------------------------"
                + "---------------------------------------------+--------"
                + "-------------------------------------------------------------------");

        Thread emp = new EmployeeThread();
        emp.start();


        Thread[] custs = new Thread[num];
        for (int i = 0; i < num; i++) {
            custs[i] = new CustomerThread(i);
            custs[i].start();
        }
        for (int i = 0; i < num; i++) {
            try {
                custs[i].join();
            } catch (InterruptedException e) {
            }
        }

        System.exit(0);
    }

    private static void printUsage() {
        System.out.println("Usage: java SandwichShop <num>");
        System.out.println("  <num>: Number of customers.");
        System.exit(-1);
    }

    public static void randomSleep(int max) {
        try {
            Thread.sleep((int) (Math.random() * max));
        } catch (InterruptedException e) {

        }
    }
}//SandwichShop

class CustomerThread extends Thread {
    private int id;

    public CustomerThread(int id)  {
        this.id = id;
    }

    public void run() {
        travelToShop();
        //The shop must be "empty" for a customer to enter.
        //If shop is occupied customer must wait.
        SandwichShop.customer_in_shop.acquire();
        arriveAtShop();

        placeOrder();
        //Once the customer places order, employee is notified
        //to make sandwich.
        SandwichShop.notify_employee.release();

        browseShop();

        atRegister();
        //once customer arrives at register, employee is notified
        //to begin transaction.
        SandwichShop.notify_employee.release();
        //Customer must wait for employee to accept payment before
        //leaving the shop.
        SandwichShop.customer_pay.acquire();
        leaveShop();
        //Once customer leaves, they give up control of the shop
        //and notify waiting customer objects.
        SandwichShop.customer_in_shop.release();

    }

    private void travelToShop() {
        System.out.println("Customer " + id + "\t\t\t\t\t\t\t\t\t\t\t|");
        SandwichShop.randomSleep(1000);
    }

    private void arriveAtShop() {
        System.out.println("\t\tCustomer " + id + "\t\t\t\t\t\t\t\t\t|");
    }

    private void placeOrder() {
        System.out.println("\t\t\t\tCustomer " + id + "\t\t\t\t\t\t\t|");
    }

    private void browseShop() {
        System.out.println("\t\t\t\t\t\tCustomer " + id + "\t\t\t\t\t|");
        SandwichShop.randomSleep(1000);
    }

    private void atRegister() {
        System.out.println("\t\t\t\t\t\t\t\tCustomer " + id + "\t\t\t|");
    }

    private void leaveShop() {
        System.out.println("\t\t\t\t\t\t\t\t\t\tCustomer " + id + "\t|");
    }
}//CustomerThread

class EmployeeThread extends Thread {

    public void run() {
        while (true) {
            waitForCustomer();
            //Employee must wait to be notified by the customer
            //that order has been placed.
            SandwichShop.notify_employee.acquire();
            makeSandwich();

            atCashRegister();
            //employee must wait until customer is at the
            //register to continue with the transaction.
            SandwichShop.notify_employee.acquire();

            paymentAccepted();
            //once employee accepts payment customer is
            //notified and allowed to leave the shop.
            SandwichShop.customer_pay.release();

        }//while
    }//run

    private void waitForCustomer() {
        System.out.println("\t\t\t\t\t\t\t\t\t\t\t\t| Employee");
    }

    private void makeSandwich() {
        System.out.println("\t\t\t\t\t\t\t\t\t\t\t\t| \t\tEmployee");
        SandwichShop.randomSleep(1000);
    }

    private void atCashRegister() {
        System.out.println("\t\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\t\tEmployee");
    }

    private void paymentAccepted() {
        System.out.println("\t\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\t\t\t\tEmployee");
    }
}//EmployeeThread

class Semaphore{
    private int value;

    public Semaphore(int value) {
        this.value = value;
    }

    public synchronized void acquire() {
        while (value <= 0) {
            try {
                wait();
            }
            catch (InterruptedException e) { }
        }
        value--;
    }

    public synchronized void release() {
        ++value;
        notify();
    }
}//Semaphore


//ANGELO ZAMUDIO SPRING 16' CS 340
