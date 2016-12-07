import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.lang.Math;
import java.util.Scanner;

public class EuclidDistanceTransform {
    public static void main(String[] args) throws FileNotFoundException {
        if (args.length < 1) {
            System.out.println("Please provide proper input and output files...");
            return;
        }
        Scanner input = new Scanner(new File(args[0]));
        PrintWriter outFile1 = new PrintWriter(args[2]);
        PrintWriter outFile2 = new PrintWriter(args[1]);

        EuclideanTransform Euclid1 = new EuclideanTransform(input);
        Euclid1.loadImage(input);
        Euclid1.firstPassEuclideanDistance(outFile1);
        Euclid1.secondPassEuclideanDistance(outFile1, outFile2);

        input.close();
        outFile1.close();
        outFile2.close();
    }
};

class EuclideanTransform {
    private int numRows = 0, numCols = 0, minVal = 0, maxVal = 0;
    private double newMin = 100, newMax = 0;
    private double sqRoot = Math.sqrt(2);
    private double[][] zeroFramedAry;
    private double[] neighborAry;

    EuclideanTransform(Scanner input) {
        numRows = input.nextInt();
        numCols = input.nextInt();
        minVal = input.nextInt();
        maxVal = input.nextInt();
        zeroFramedAry = new double[numRows + 2][numCols + 2];
        neighborAry = new double[5];
    }

    void loadImage(Scanner input) {
        int pixel;
        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                pixel = input.nextInt();
                zeroFramedAry[i][j] = pixel;
            }//for j
        }//for i
        zeroFramed();
    }//loadImage

    private void zeroFramed() {
        for (int j = 0; j <= numRows + 1; ++j) {
            zeroFramedAry[j][0] = 0;
            zeroFramedAry[j][numCols + 1] = 0;
        }
        //fills first and last row with mirrored value
        for (int k = 0; k <= numCols + 1; ++k) {
            zeroFramedAry[0][k] = 0;
            zeroFramedAry[numRows + 1][k] = 0;
        }
    }//zeroFramed

    private void loadNeighbors(int pass, int row, int column) {
        //adds values to neighborAry
        if (pass == 1) {
            neighborAry[0] = zeroFramedAry[row][column];//p(i,j)
            neighborAry[1] = zeroFramedAry[row - 1][column - 1] + sqRoot;
            neighborAry[2] = zeroFramedAry[row - 1][column] + 1;
            neighborAry[3] = zeroFramedAry[row - 1][column + 1] + sqRoot;
            neighborAry[4] = zeroFramedAry[row][column - 1] + 1;
        } else if (pass == 2) {
            neighborAry[0] = zeroFramedAry[row][column];//p(i,j)
            neighborAry[1] = zeroFramedAry[row][column + 1] + 1;
            neighborAry[2] = zeroFramedAry[row + 1][column - 1] + sqRoot;
            neighborAry[3] = zeroFramedAry[row + 1][column] + 1;
            neighborAry[4] = zeroFramedAry[row + 1][column + 1] + sqRoot;
        }
    }//loadNeighbors

    void firstPassEuclideanDistance(PrintWriter out) {
        double min;
        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                if (zeroFramedAry[i][j] > 0) {
                    loadNeighbors(1, i, j);
                    min = neighborAry[1];
                    for (int k = 2; k < neighborAry.length; k++) {
                        if (neighborAry[k] < min) {
                            min = neighborAry[k];
                        }
                    }
                    zeroFramedAry[i][j] = min;
                    newMin = (zeroFramedAry[i][j] < newMin) ? (zeroFramedAry[i][j]) : newMin;
                    newMax = (zeroFramedAry[i][j] > newMax) ? (zeroFramedAry[i][j]) : newMax;
                }//if
            }//for j
        }//for i
        prettyPrintDistance(1, out);
    }//firstPass

    void secondPassEuclideanDistance(PrintWriter out, PrintWriter out1) {
        double min;
        newMin = 100;
        newMax = 0;
        for (int i = numRows + 1; i > 0; --i) {
            for (int j = numCols + 1; j > 0; --j) {
                if (zeroFramedAry[i][j] > 0) {
                    loadNeighbors(2, i, j);
                    min = neighborAry[1];
                    for (int k = 2; k < neighborAry.length; k++) {
                        if (neighborAry[k] < min) {
                            min = neighborAry[k];
                        }
                    }
                    if (min < zeroFramedAry[i][j]) {
                        zeroFramedAry[i][j] = min;
                        newMin = (zeroFramedAry[i][j] < newMin) ? (zeroFramedAry[i][j]) : newMin;
                        newMax = (zeroFramedAry[i][j] > newMax) ? (zeroFramedAry[i][j]) : newMax;
                    }//if
                }//if
            }//for j
        }//for i
        prettyPrintDistance(2, out);

        int dist_pixel;
        out1.write(numRows + " " + numCols + " " + (int) (newMin + .5) + " " + (int) (newMax + .5) + "\n");
        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                if (zeroFramedAry[i][j] > 0) {
                    dist_pixel = (int) (zeroFramedAry[i][j] + .5);
                    out1.write(dist_pixel + " ");
                } else {
                    out1.write(0 + " ");
                }
            }
            out1.write("\n");
        }
        out.write("\n\n");
    }//SecondEuclideanPass

    private void prettyPrintDistance(int pass, PrintWriter out) {
        out.write("Result of Pass " + pass + ": \n");
        out.write("NumRows:" + numRows + " NumCols:" + numCols + " NewMin:" + (int) (newMin + .5) + " NewMax:" + (int) (newMax + .5) + "\n");
        int pixel;
        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                if (zeroFramedAry[i][j] > 0) {
                    pixel = (int) (zeroFramedAry[i][j] + .5);
                    out.write(pixel + " ");
                } else {
                    out.write("  ");
                }
            }
            out.write("\n");
        }
        out.write("\n\n");
    }//prettyPrint
}
//Angelo Zamudio CS381 Fall 16'
