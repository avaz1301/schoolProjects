/**
 * Created by Angelo Zamudio.
 */
public class coffeeCustomer extends Thread {
    private int customerId;
    /**
     * Creates instance of coffeeCustomer setting customer idQueue
     * equal to integer parameter idQueue.
     * @param id Customer identification number.
     */
    public coffeeCustomer(int id){
        customerId = id;
    }

    /**
     * Method is called by the start(). Coffee Customer
     * thread will preform all instructions within the
     * run method.
     */
    public void run(){
        arriveAtShop();
        //Customer is passed into acquire for comparison.
        //When acquire is successful, remove from queue.
        coffeeBar.occupyShop.acquire(this);
        // This is done with guarantee that THIS coffeeCustomer is head of queue.
        coffeeBar.idQueue.poll();
        drinkCoffee();
        leaveShop();
        coffeeBar.occupyShop.release();//Once complete, coffeeCustomer will release a lock.
    }//run

    public boolean isFirst(){
        if(customerId==coffeeBar.idQueue.peek()){
            return true;
        }else{
            return false;
        }
    }

    /**
     * Notifies user that coffeeCustomer has arrived to the
     * coffee bar with a console output after the customer
     * thread is put to wakes from random sleep.
     */
    public void arriveAtShop(){
        randomSleep(2000);//Simulates customers "arriving" at varying times.
        //Following if/else is for keeping console output uniform and readable.
        coffeeBar.idQueue.add(customerId); //Customer idQueue added to end of queue.
        if (customerId >9){
            System.out.println("Customer "+ customerId + " arrived.\t\t\t\t\t\t\t\t|  "+ coffeeBar.idQueue);
        }else{
            System.out.println("Customer "+ customerId + " arrived.\t\t\t\t\t\t\t\t|  "+ coffeeBar.idQueue);
        }
    }//arrive

    /**
     * Notifies user that coffeeCustomer is drinking coffee.
     * Sleeps customer thread to simulate drinking coffee.
     */
    public void drinkCoffee(){
        //Following if/else is for keeping console output uniform and readable.
        if (customerId >9){
            System.out.println("\t\t\tCustomer "+ customerId + " is drinking.\t\t\t\t|  "+ coffeeBar.idQueue);
        }else{
            System.out.println("\t\t\tCustomer "+ customerId + " is drinking.\t\t\t\t\t|  "+ coffeeBar.idQueue);
        }
        randomSleep(2000);//Simulates customers enjoying coffee for lengthy variations of time.
    }//drink

    /**
     * Notifies user that a coffeeCustomer is leaving the
     * bar with console output.
     */
    public void leaveShop(){
        //Following if/else is for keeping console output uniform and readable.
        if (customerId >9){
            System.out.println("\t\t\t\t\t\t\tCustomer "+ customerId + " left.\t|  "+ coffeeBar.idQueue);
        }else{
            System.out.println("\t\t\t\t\t\t\tCustomer "+ customerId + " left.\t|  "+ coffeeBar.idQueue);
        }
    }//leave

    /**
     * This method places thread to sleep for a random amount of time,
     * using parameter max as the factor by which to multiply the
     * random number. Resulting sleep time is in milliseconds.
     * @param max Factor by which randomly generated number
     *            is multiplied.
     */
    public static void randomSleep(int max) {
        try {
            Thread.sleep((int) (Math.random() * max));
        } catch (InterruptedException e) {

        }//try_catch
    }//randomSleep
}//coffeeCustomer
