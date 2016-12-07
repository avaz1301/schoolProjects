import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.lang.Math;
import java.util.Scanner;

public class HoughTransform {
    public static void main(String[] args) throws FileNotFoundException {
        if (args.length < 1) {
            System.out.println("Please provide proper input and output files...");
            return;
        }
        Scanner input = new Scanner(new File(args[0]));
        PrintWriter outFile1 = new PrintWriter(args[1]);
        PrintWriter outFile2 = new PrintWriter(args[2]);

        ImageProcessing img = new ImageProcessing(input);
        HoughImageTransform ht = new HoughImageTransform(img, outFile1, outFile2);

        input.close();
        outFile1.close();
        outFile2.close();
    }//main
}//HT

class ImageProcessing {
    int numRows, numCols;
    private int minVal;
    private int maxVal;
    int[][] imgAry;

    ImageProcessing(Scanner input) {
        numRows = input.nextInt();
        numCols = input.nextInt();
        minVal = input.nextInt();
        maxVal = input.nextInt();
        imgAry = new int[numRows][numCols];
        loadImage(input);
    }

    private void loadImage(Scanner input) {
        int pixel;
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                pixel = input.nextInt();
                imgAry[i][j] = pixel;
            }//for j
        }//for i
    }//loadImage

    private void prettyPrint(PrintWriter out) {
        out.write(numRows + " " + numCols + " " + minVal + " " + maxVal + "\n");
        int pixel;
        for (int i = 1; i < numRows; ++i) {
            for (int j = 1; j < numCols; ++j) {
                pixel = imgAry[i][j];
                if (pixel > 0) {
                    out.write(pixel + " ");
                } else {
                    out.write("  ");
                }
            }
            out.write("\n");
        }//for
    }//PP
}

class xyCoord {
    int x, y;
}

class HoughImageTransform {
    private xyCoord point;
    private int angleInDegree;
    private double angleInRadians, pi;
    private int numRows, numCols, minVal, maxVal;
    private int[][] houghAry;

    HoughImageTransform(ImageProcessing img, PrintWriter out, PrintWriter out1) {
        numRows = 180;
        numCols = 2 * (int) (Math.sqrt((img.numCols * img.numCols) + (img.numRows * img.numRows)));
        minVal = 100;
        maxVal = 0;
        pi = 3.14159;
        point = new xyCoord();/////////////////
        houghAry = new int[numRows][numCols];
        for (int i = 0; i < img.numRows; ++i) {
            for (int j = 0; j < img.numCols; ++j) {
                if (img.imgAry[i][j] > 0) {
                    point.x = i;
                    point.y = j;
                    angleInDegree = 0;
                    while (angleInDegree <= 179) {
                        angleInRadians = (angleInDegree / 180.0) * pi;
                        int dist = (int) computeDistance(point, angleInRadians);
                        int offdist = (numCols / 2) + dist;
                        houghAry[angleInDegree][offdist]++;
                        maxVal = (houghAry[angleInDegree][offdist] > maxVal) ? houghAry[angleInDegree][offdist] : maxVal;
                        minVal = (houghAry[angleInDegree][offdist] < minVal) ? houghAry[angleInDegree][offdist] : minVal;
                        angleInDegree++;
                    }//while
                }//if
            }
        }//for
        determineHeader(out);
        prettyPrint(out1);
    }//HIT

    private double computeDistance(xyCoord pt, double angle) {
        double t = angle - Math.atan(pt.y / pt.x) - (pi / 2.0);
        return Math.sqrt((pt.x * pt.x) + (pt.y * pt.y)) * Math.cos(t);
    }

    private void determineHeader(PrintWriter out) {
        out.write(numRows + " " + numCols + " " + minVal + " " + maxVal + "\n");
        int pixel;
        for (int i = 1; i < numRows; ++i) {
            for (int j = 1; j < numCols; ++j) {
                out.write(houghAry[i][j] + " ");
            }
            out.write("\n");
        }//for
    }//determineHeader

    private void prettyPrint(PrintWriter out) {
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                if (houghAry[i][j] > 0) {
                    out.write(houghAry[i][j] + " ");
                } else {
                    out.write("  ");
                }
            }
            out.write("\n");
        }//for
    }//prettyPrint
}//HIT

//Angelo Zamudio CS381 Fall 16'



