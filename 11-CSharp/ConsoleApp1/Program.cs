using System;

class Program { 
    static void Main() {
        int nRow = 4;
        int nCol = 4;
        int[,] array = GenSpiral(nRow, nCol);
        PrintArray(array);
    }
    
    static int[,] GenSpiral(int nRow, int nCol) {
        int[,] array = new int[nRow, nCol];
        int value = 1;
        int minRow = 0;
        int maxRow = nRow - 1;
        int minCol = 0;
        int maxCol = nCol - 1;
        while (value <= nRow * nCol) {
            for (int col = minCol; col <= maxCol && value <= nRow * nCol; col++) {
                array[minRow, col] = value++;
            }
            minRow++;
            for (int row = minRow; row <= maxRow && value <= nRow * nCol; row++) {
                array[row, maxCol] = value++;
            }
            maxCol--;
            for (int col = maxCol; col >= minCol && value <= nRow * nCol; col--) {
                array[maxRow, col] = value++;
            }
            maxRow--;
            for (int row = maxRow; row >= minRow && value <= nRow * nCol; row--) {
                array[row, minCol] = value++;
            }
            minCol++;
        }
        return array;
    }

    static void PrintArray(int[,] array) {
        int nRow = array.GetLength(0);
        int nCol = array.GetLength(1);
        for (int i = 0; i < nRow; i++) {
            for (int j = 0; j < nCol; j++) {
                Console.Write(array[i, j] + "\t");
            }
            Console.WriteLine();
        }
    }
}