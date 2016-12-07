import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class AverageFilter {
    public static void main(String[] args) throws FileNotFoundException {
        if (args.length < 1) {
            System.out.println("Please Provide an input.");
            return;
        }
        String output_file = args[0];
        output_file = "AVG3X3Out.txt";

        Scanner input = new Scanner(new File(args[0]));
        PrintWriter out_write = new PrintWriter(output_file);

        Average med1 = new Average(input);
        med1.loadImage(input);
        med1.Average3X3(out_write);

        input.close();
        out_write.close();
    }//main
}

class Average {
    private int numRows, numCols, minVal, maxVal;
    private int newMin, newMax;
    private int[][] mirrorFramedAry;
    private int[][] tempAry;
    private int[] neighborAry;

    public Average(Scanner input) {
        numRows = input.nextInt();
        numCols = input.nextInt();
        minVal = input.nextInt();
        maxVal = input.nextInt();
        newMin = 64;
        mirrorFramedAry = new int[numRows + 2][numCols + 2];
        tempAry = new int[numRows + 2][numCols + 2];
        neighborAry = new int[9];

    }

    public void loadImage(Scanner input) {
        int pixel;
        //process image into mirrorFramedArray starting at (1,1)
        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                pixel = input.nextInt();
                mirrorFramedAry[i][j] = pixel;
            }//for j
        }//for i
        mirrorFramed();
    }//loadImage

    private void mirrorFramed() {
        //fills first and last column with mirrored value
        for (int j = 0; j <= numRows + 1; ++j) {
            mirrorFramedAry[j][0] = mirrorFramedAry[j][1];
            mirrorFramedAry[j][numCols + 1] = mirrorFramedAry[j][numCols];
        }
        //fills first and last row with mirrored value
        for (int k = 0; k <= numCols + 1; ++k) {
            mirrorFramedAry[0][k] = mirrorFramedAry[1][k];
            mirrorFramedAry[numRows + 1][k] = mirrorFramedAry[numRows][k];
        }
        fillTempAry();
    }//mirrorFramed

    private void fillTempAry() {
        //places median of each pixel neighborhood to tempAry[i][j]
        //and prints tempAry
        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                tempAry[i][j] = loadNeighbors(i, j);
            }//for j
        }//for i
    }//fillTempAry

    private int loadNeighbors(int row, int column) {
        int count = 0, candidate = 0;
        //adds values to neighborAry
        for (int i = row - 1; i <= row + 1; ++i) {
            for (int j = column - 1; j <= column + 1; ++j) {
                neighborAry[count++] = mirrorFramedAry[i][j];
            }//for j
        }//for i
        for (int k = 0; k < 9; ++k) {
            candidate += neighborAry[k];
        }
        candidate = candidate / 9;
        //keeps track of newMin,newMax
        if (candidate < newMin) {
            newMin = candidate;
        } else if (candidate > newMax) {
            newMax = candidate;
        }
        return candidate;
    }//loadNeighbors


    void Average3X3(PrintWriter out) {
        out.write(numRows + " " + numCols + " " + newMin + " " + newMax + "\n");

        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                out.write(tempAry[i][j] + " ");
            }//for j
            out.write("\n");
        }//for i

    }//printOutputImage

}
//Angelo Zamudio CS381 Fall 16'

