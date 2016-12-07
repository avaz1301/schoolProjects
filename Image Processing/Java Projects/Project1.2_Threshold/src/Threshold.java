import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Threshold {

    public static void main(String[] args) throws FileNotFoundException {
        if (args.length < 1) {
            System.out.println("Please Provide an input and output file");
            return;
        }
        Scanner input = new Scanner(new File(args[0]));
        Scanner user_in = new Scanner(System.in);
        System.out.print("Please enter a threshold value: ");
        String thr = user_in.nextLine();
        PrintWriter out_write = new PrintWriter("thr_" + thr + ".txt");
        user_in.close();

        ThresholdArray h1 = new ThresholdArray(input, Integer.parseInt(thr));
        h1.computeThreshold(out_write);

        input.close();
        out_write.close();
    }//main
}

class ThresholdArray {
    private int numRows, numCols, minVal, maxVal, thrVal;
    private int[][] thr_Ary;

    public ThresholdArray(Scanner input, int thr) {
        thrVal = thr;
        numRows = input.nextInt();
        numCols = input.nextInt();
        minVal = input.nextInt();
        maxVal = input.nextInt();
        thr_Ary = new int[numRows][numCols];
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                thr_Ary[i][j] = input.nextInt();
            }//for j
        }//for i
    }

    public void computeThreshold(PrintWriter writer) {
        writer.println(numRows + " " + numCols + " " + minVal + " " + maxVal);
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (thr_Ary[i][j] < thrVal) {
                    writer.print(0 + " ");
                } else {
                    writer.print(1 + " ");
                }//else
            }//for j
            writer.println();
        }//for i
    }//computeThreshold
}
//Angelo Zamudio CS381 Fall 16'