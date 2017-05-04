package Homework3;


public class Worker implements Runnable {
	
	private Barrier partA;
	
	public Worker(Barrier partA){
		this.partA = partA;
	}
	public void run(){
		System.out.println("A");
		//SleepUtilities.nap();
		
		partA.waitForOthers();
	
		System.out.println("B");
	}
	
}