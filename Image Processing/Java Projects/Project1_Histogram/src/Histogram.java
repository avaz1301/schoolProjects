import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Histogram {

    public static void main(String[] args) throws FileNotFoundException {
        if(args.length<2){
            System.out.println("Please Provide an input and output file");
            return;
        }
        Scanner input = new Scanner(new File(args[0]));
        PrintWriter out_write = new PrintWriter(args[1]);

        HistArray h1 = new HistArray(input);
        h1.computeHistogram(out_write);

        input.close();
        out_write.close();
    }
}

class HistArray {
    private int numRows, numCols, minVal, maxVal;
    private int[] histogram;

    public HistArray(Scanner input) {
        numRows = input.nextInt();
        numCols = input.nextInt();
        minVal = input.nextInt();
        maxVal = input.nextInt();
        histogram = new int[maxVal + 1];
        while (input.hasNext()) {
            int temp = input.nextInt();
            histogram[temp] += 1;
        }
    }

    public void computeHistogram(PrintWriter writer) {
        for (int i = 0; i < histogram.length; i++) {
            System.out.print("(" + i + ") : " + histogram[i]);
            writer.print("(" + i + ") : " + histogram[i]);
            for (int j = 0; j < histogram[i]; j++) {
                if (j <= 80) {
                    System.out.print("+");
                    writer.print("+");
                }
            }
            System.out.println();
            writer.println();
        }
    }
}
//Angelo Zamudio CS381 Fall 16'
