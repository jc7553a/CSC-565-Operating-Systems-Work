package Homework2;

public class primes {
	
	/*Simple Class to Create a Matrix of Values*/
	private int primeMatrix [][];
	private int rowSize;
	private int columnSize;
	
	public void setRow(int rowPassed)
	{
		this.rowSize = rowPassed;
	}
	public void setColumn(int columnPassed)
	{
		this.columnSize = columnPassed;
	}
	public int getRow()
	{
		return rowSize;
	}
	public int getColumn()
	{
		return columnSize;
	}
	public void setMatrix(int myMatrix[][])
	{
		this.primeMatrix = myMatrix;
	}
	public int [][] getMatrix()
	{
		return primeMatrix;
	}

}// end class
