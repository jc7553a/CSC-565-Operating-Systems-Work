package Homework3;

import java.util.concurrent.Semaphore;

import java.util.*;

public class BarrierImpl implements Barrier {
	
	public static int value;
	public int threadNumber;
	
	/* Creating 2 Semaphores for Counting and Blocking */
	public Semaphore mySemaphore;
	public Semaphore countSemaphore;
	
	public BarrierImpl(int threadPassed){
		
		/* Setting Thread Number and initializing Semaphores*/
		this.threadNumber = threadPassed;
		this.mySemaphore = new Semaphore(0);
		this.countSemaphore = new Semaphore(threadNumber);
	}
	
	public void waitForOthers(){
		/* Decrementing Counting Semaphore*/
		try{
		countSemaphore.acquire();
		} catch (InterruptedException e) {}
		
		/* Getting Value of Counting Semaphore*/
		value = countSemaphore.availablePermits();
		
		/* If Counting Semaphore has reached 0 then 5 Threads have been blocked*/
		if(value > 0)
		{
			try{
				mySemaphore.acquire();
			} catch (InterruptedException e) {}
		
		}
		else
		{
				/* Releasing 1 Semaphore at a Time Until Count Semaphore is back to original Value*/
				while (value < 5)
				{
					value = countSemaphore.availablePermits();
					countSemaphore.release(1);
					mySemaphore.release(1);
				}
			}
			
	}
	public void freeAll()
	{
		/* Releasing All Blocked Semaphores Immediatlyy */
		mySemaphore.release(threadNumber);
	}

	
	
}



