/**
 * An interface for reader-writer locks.
 *
 
 */

public interface ReadWriteLock
{
	public abstract void acquireReadLock(int readerNum);
	public abstract void acquireWriteLock(int writerNum);
	public abstract void releaseReadLock(int readerNum);
	public abstract void releaseWriteLock(int writerNum);
}
