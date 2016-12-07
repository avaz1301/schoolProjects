/**
 * Reader.java
 *

 */


public class Reader implements Runnable
{
	
	private ReadWriteLock db;
	private int readerNum;
	
	public Reader(int readerNum, ReadWriteLock db) {
		this.readerNum = readerNum;
		this.db = db;
	}
	
	public void run() {
		while (true) {
			SleepUtilities.nap();
			
			System.out.println("reader " + readerNum + " wants to read.");
			db.acquireReadLock(readerNum);
			
			// you have access to read from the database
			// let's read for awhile .....
			SleepUtilities.nap();
			
			db.releaseReadLock(readerNum);
		}
	}
}
