package Homework2;

import java.util.*;

public class Driver {
	public static int SIZE_ROW = 50;
	public static int SIZE_COLUMN = 10;
	public static void main (String[] args)
	{
		Scanner keyboard = new Scanner(System.in);
		int val = 1;
		int matrixToPass[][] = new int [SIZE_ROW][SIZE_COLUMN];
		for (int i = 0; i < SIZE_ROW;  ++i)
		{
			for (int j = 0; j < SIZE_COLUMN; ++j)
			{
				matrixToPass[i][j] = val;
				++val;
			}
		}
		
		
		if (args.length >0)
		{
			if (Integer.parseInt(args[0]) < 0)
			{
				System.err.println(args[0] + " must be >= 0.");;
			}
		}
			else
			{
				System.out.println("What number do you want a list of all the primes previous to it?");
				int myNum = keyboard.nextInt();
				System.out.println("You Entered: " + myNum);
				
				int stopRow = myNum/10;
				int stopColumn = myNum%10;
				boolean flag = false;
				
				primes myObject = new primes();
				myObject.setMatrix(matrixToPass);
				myObject.setColumn(SIZE_COLUMN);
				myObject.setRow(SIZE_ROW);
				int tempMatrix [][];
				
				Thread thrd =  new Thread(new findPrimes(myObject));
				thrd.start();
				try{
					thrd.join();
					tempMatrix = myObject.getMatrix();
					System.out.println("Prime Numbers:");
					for (int t = 0; t < SIZE_ROW; ++t)
					{
						for ( int q = 0; q < SIZE_COLUMN; ++q)
						{
							if (t == stopRow && q == stopColumn)
							{
								flag = true;
							}
							if (tempMatrix[t][q] != 1 && flag == false)
							{
								System.out.printf("%d ", tempMatrix[t][q]);
							}
						}
					}
					} catch (InterruptedException ie) { }
				}
				
			}
		
		}// end main

