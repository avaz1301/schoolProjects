import java.util.concurrent.ConcurrentLinkedQueue;
/**
 * coffeeBar program simulates the operation of a coffee bar.
 * Customers are served in order of arrival (no line jumping).
 * If a customer ARRIVES and there is an available seat then
 * they may occupy that seat. But if customer ARRIVES and all
 * seats are taken, they must wait until ALL customers in the
 * bar leave in order to enter the bar. These conditions are
 * controlled with the use of a Queue and counting Semaphore.
 *
 *
 * @author  Angelo Zamudio
 * @version 1.0
 * @see java.lang.Thread
 * @see java.util.concurrent.ConcurrentLinkedQueue
 */

public class coffeeBar extends Thread{
    // Counting Semaphore to control number of CoffeeCustomers allowed in the
    // bar at any time shop.
    public static Semaphore occupyShop = new Semaphore(5);
    // ConcurrentLinkedQueue is an unbounded thread-safe queue based on linked nodes.
    // NOTE: actions in a thread prior to placing into a ConcurrentLinkedQueue
    // happen-before actions subsequent to the access or removal of that element
    // from the ConcurrentLinkedQueue in another thread.
    //Queue hold the customer id in the order at which they arrive.
    public static ConcurrentLinkedQueue<Integer> idQueue = new ConcurrentLinkedQueue<>();

    /**
     * Driver method of coffeeBar. It instantiates, starts, runs
     * and then joins the number of coffeeCustomer threads desired
     * by the user, which is specified by the inputted command line
     * argument.
     * @param args String array containing argument to be passed
     *             into program.
     */
    public static void main(String args[]) {
        //For output readability.
        System.out.println("   Arrived\t\t\tDrinking\t\t\tLeaving\t\t| idQueue Status");
        System.out.println("---------------------------------------------------------------------" +
                           "---------------------------");
        // Parses the argument from command line that represents number
        // of customers.
        int numCustomers = Integer.parseInt(args[0]);
        coffeeCustomer[] customers = new coffeeCustomer[numCustomers];

        //Generates the desired number of threads and starts each of them.
        for (int i = 0; i < numCustomers; i++) {
            customers[i] = new coffeeCustomer(i);
            customers[i].start();
        }//for

        // Calls join() on each thread in array which waits for thread
        // to complete execution and die.
        for (int i = 0; i < numCustomers; i++) {
            try {
                customers[i].join();
            } catch (InterruptedException e) {

            }//try/catch
        }//for
    }//main

}//coffeeBar
