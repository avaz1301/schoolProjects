/**
 * Created by Angelo Zamudio.
 */
public class Semaphore{

    private int value;//Initial Semaphore value

    /**
     * Creates instance oF Semaphore object with number of "locks"
     * set to passed integer parameter.
     * @param value Number of "locks" to be acquired.
     */
    public Semaphore(int value) {
        this.value = value;
    }//Semaphore

    /**
     * This method controls the number of threads that can pass
     * through, decrementing Semaphore value and waiting any thread
     * when the Semaphore value is 0 or less.
     * NOTE:There is possibility that this implementation of the
     * acquire method may cause starvation if appropriate thread
     * is never notified. Through extensive testing this has not
     * been the case as of yet.
     * @param cc
     */
    public synchronized void acquire(coffeeCustomer cc) {
        // The loop guarantees that if the acquiring thread is not first in the queue or
        // if the current Semaphore value is equal to or less than 0 the acquiring thread
        // is waited and waits to be notified.
        while (!cc.isFirst() || value <= 0) {
            try {
                wait();
            } catch (InterruptedException e) { }
        }//while

        // Only the thread at the front of the queue will reach this point.
        // The mutex semaphore is used to fix printout order problem.
        value--;
        // This notifyAll() is placed here in the event where the Semaphore value is
        // less than 5 but not zero and acquiring threads will notify waiting threads
        // until all locks are acquired.
        notifyAll();
    }//acquire

    /**
     * Increments value of the Semaphore.
     */
    public synchronized void release() {
        ++value;
        // In the event that the coffee bar is full to capacity, only the last thread
        // to leave the bar will notify all of the waiting threads in the idQueue.
        if(value==5){
            System.out.println("-----------------------------COFFEE SHOP IS EMPTY-------------------------------|  ");
            notifyAll();
        }//if
    }//release

}//Semaphore
