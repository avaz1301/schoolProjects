/**
 * Interface for shared memory.
 *

 */
public interface Buffer <E>
{
	// producers call this method
	public void insert(E item);

	// consumers call this method
	public E remove();
}
