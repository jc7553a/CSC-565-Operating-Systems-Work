package Homework2;

public class findPrimes implements Runnable {
	
	private primes primePassed;
	
	public findPrimes(primes passedPrime)
	{
		this.primePassed = passedPrime;
	}

	public void run()
	{
		/*Method that will Check for Primes by Modular Arithmetic*/
		int temp;
		int matrixPassed[][] = primePassed.getMatrix();
		for (int i = 0; i < Driver.SIZE_ROW; ++i)
		{
			for (int j = 0; j <  Driver.SIZE_COLUMN; ++j)
			{
				temp = matrixPassed[i][j];
				if (temp !=2 && temp %2 ==0)
				{
					matrixPassed[i][j] = 1;
				}
				if (temp !=3 && temp %3 ==0)
				{
					matrixPassed[i][j] = 1;
				}
				if (temp !=5 && temp %5 ==0)
				{
					matrixPassed[i][j] = 1;
				}
				if (temp !=7 && temp %7 ==0)
				{
					matrixPassed[i][j] = 1;
				}
			}
		}
		/*Setting Matrix of Instance to new Matrix*/
		primePassed.setMatrix(matrixPassed);
	}// end run
}// end class
