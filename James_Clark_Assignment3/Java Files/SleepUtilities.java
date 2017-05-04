package Homework3;


public class SleepUtilities {
	
	public static void nap()
	{
		nap(NAP_TIME);
	}
	
	public static void nap(int duration){
		int sleeptime = (int)(duration*Math.random());
		try{Thread.sleep(sleeptime*1000);;
		}catch(InterruptedException e){}
		}
	
	private static final int NAP_TIME = 7;
	}


