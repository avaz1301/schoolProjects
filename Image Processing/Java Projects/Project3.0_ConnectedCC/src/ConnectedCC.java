import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.lang.Math;
import java.util.Scanner;

public class ConnectedCC {
    public static void main(String[] args) throws FileNotFoundException {
        if (args.length < 1) {
            System.out.println("Please Provide an output files.");
            return;
        }
        Scanner input = new Scanner(new File(args[0]));
        PrintWriter outFile1 = new PrintWriter(args[1]);
        PrintWriter outFile2 = new PrintWriter(args[2]);
        PrintWriter outFile3 = new PrintWriter(args[3]);

        Connected_CC Connect1 = new Connected_CC(input);
        Connect1.loadImage(input);

        Connect1.Connect_CC_Pass1(outFile1);
        Connect1.Connect_CC_Pass2(outFile1);
        Connect1.Connect_CC_Pass3(outFile1, outFile3);
        Connect1.toBinary(outFile2);

        input.close();
        outFile1.close();
        outFile2.close();
        outFile3.close();
    }
};

class Property {
    int label, numPixels;
    int minRow, minCol, maxRow, maxCol;
};

class Connected_CC {
    private int numRows = 0, numCols = 0, minVal = 0, maxVal = 0;
    private int newMin = 100, newMax = 0, newLabel = 0;
    private int[][] zeroFramedAry;
    private int[] EQAry;
    private int[] neighborAry;
    private Property[] cc_PropertyList;
    private int propSize = 0;

    Connected_CC(Scanner input) {
        numRows = input.nextInt();
        numCols = input.nextInt();
        minVal = input.nextInt();
        maxVal = input.nextInt();
        zeroFramedAry = new int[numRows + 2][numCols + 2];
        neighborAry = new int[4];
        int eqsize = (numRows * numCols) / 4;
        EQAry = new int[eqsize];
        for (int i = 0; i < EQAry.length; i++) {
            EQAry[i] = i;
        }
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
    }

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
    }

    private void loadNeighbors(int row, int column) {
        //adds values to neighborAry
        neighborAry[0] = zeroFramedAry[row - 1][column];
        neighborAry[1] = zeroFramedAry[row][column - 1];
        neighborAry[2] = zeroFramedAry[row][column + 1];
        neighborAry[3] = zeroFramedAry[row + 1][column];
    }//loadNeighbors

    void Connect_CC_Pass1(PrintWriter out) {
        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                if (zeroFramedAry[i][j] == 1) {
                    loadNeighbors(i, j);
                    int a = neighborAry[0];
                    int b = neighborAry[1];
                    if (a == 0 && b == 0) {//case 1
                        newLabel++;
                        zeroFramedAry[i][j] = newLabel;
                    } else if (a > 0 && b > 0) {//case 3.1
                        zeroFramedAry[i][j] = Math.min(a, b);
                    } else if (a == 0) {//case 3.2
                        zeroFramedAry[i][j] = b;

                    } else if (b == 0) {//case 3.3
                        zeroFramedAry[i][j] = a;
                    }

                }//if > 1
            }//for j
        }//for i
        prettyPrint(1, out);
        out.write("EQAry: \n");
        for (int k = 1; k < newLabel; ++k) {
            out.write("[" + k + "]");
        }
        out.write("\n");
        for (int k = 1; k < newLabel; ++k) {
            out.write(" " + EQAry[k] + " ");
        }
        out.write("\n\n");
    }//Connected_CC_Pass1

    void Connect_CC_Pass2(PrintWriter out) {
        for (int i = numRows + 1; i > 0; --i) {
            for (int j = numCols + 1; j > 0; --j) {
                if (zeroFramedAry[i][j] > 0) {
                    loadNeighbors(i, j);
                    int x = zeroFramedAry[i][j];
                    int c = neighborAry[2];
                    int d = neighborAry[3];
                    if (c != 0 && d != 0) {//case 3.1
                        if (c != d) { //3.1A
                            //if nonzero neighbors are different
                            zeroFramedAry[i][j] = Math.min(Math.min(c, d), x);
                            if (zeroFramedAry[i][j] != x) {
                                updateEQAry(x, zeroFramedAry[i][j]);
                            }
                        } else if (x > c) {//3.1B
                            //if X is different from C and D
                            zeroFramedAry[i][j] = c;
                            updateEQAry(x, c);
                        } else /*if (x != c && c != d && d != x)*/ {//3.1C
                            // if X, C and D are different
                            zeroFramedAry[i][j] = Math.min(Math.min(c, d), x);
                            if (zeroFramedAry[i][j] != x) {
                                updateEQAry(x, zeroFramedAry[i][j]);
                            }
                        }
                    } else if (c != 0) {//case 3.2
                        zeroFramedAry[i][j] = c;
                        updateEQAry(x, c);
                    } else if (d != 0) {//case 3.3
                        zeroFramedAry[i][j] = d;
                        updateEQAry(x, d);
                    }

                }//if
            }//for j
        }//for i
        prettyPrint(2, out);
        out.write("EQAry:\n");
        for (int k = 1; k < newLabel; ++k) {
            out.write("[" + k + "]");
        }
        out.write("\n");
        for (int k = 1; k < newLabel; ++k) {
            out.write(" " + EQAry[k] + " ");
        }
        out.write("\n\n");
        manageEQAry();
        out.write("EQAry After Management: \n");
        for (int k = 1; k < newLabel; ++k) {
            out.write("[" + k + "]");
        }
        out.write("\n");
        for (int k = 1; k < newLabel; ++k) {
            out.write(" " + EQAry[k] + " ");
        }
        out.write("\n\n");
    }//Connected_CC_Pass2

    void Connect_CC_Pass3(PrintWriter out, PrintWriter out2) {
        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                if (zeroFramedAry[i][j] != 0) {
                    zeroFramedAry[i][j] = EQAry[zeroFramedAry[i][j]];
                    propUpdate(zeroFramedAry[i][j], i, j);
                }//if
                if (zeroFramedAry[i][j] < newMin) {
                    newMin = zeroFramedAry[i][j];
                }
                if (zeroFramedAry[i][j] > newMax) {
                    newMax = zeroFramedAry[i][j];
                }
            }//for i
        }//for i
        prettyPrint(3, out);
        out.write("EQAry:\n");
        for (int k = 1; k < newLabel; ++k) {
            out.write("[" + k + "]");
        }
        out.write("\n");
        for (int k = 1; k < newLabel; ++k) {
            out.write(" " + EQAry[k] + " ");
        }
        out.write("\n\n");
        for (int i = 1; i < propSize; ++i) {
            if (cc_PropertyList[i].numPixels != 0) {
                out2.write("Label: " + cc_PropertyList[i].label + "\n");
                out2.write("# of Pixels: " + cc_PropertyList[i].numPixels + "\n");
                out2.write("minRow: " + cc_PropertyList[i].minRow + "\nminCol: " + cc_PropertyList[i].minCol + "\nmaxRow: " +
                        cc_PropertyList[i].maxRow + "\nmaxCol: " + cc_PropertyList[i].maxCol + "\n\n");
            }
        }//for i
    }//Connected_CC_Pass3

    private void updateEQAry(int pos, int newVal) {
        if (newVal < EQAry[pos]) {
            EQAry[pos] = newVal;
        }
    }//updateEQAry

    private void manageEQAry() {
        int nlu = 0;
        for (int i = 1; i < newLabel + 1; ++i) {
            if (EQAry[i] == i) {
                nlu++;
                EQAry[i] = nlu;
            } else {
                EQAry[i] = EQAry[EQAry[i]];
            }
            if (EQAry[i] > nlu) {
                nlu++;
                EQAry[i] = nlu;
            }
        }//for
        cc_PropertyList = new Property[nlu + 1];
        for (int i = 0; i < cc_PropertyList.length; i++) {
            cc_PropertyList[i] = new Property();
        }
        propSize = nlu + 1;
        for (int j = 0; j < nlu + 1; ++j) {
            cc_PropertyList[j].label = j;
            cc_PropertyList[j].minRow = (numRows * numCols) / 4;
            cc_PropertyList[j].minCol = (numRows * numCols) / 4;
        }
    }//manageEQAry

    private void propUpdate(int label, int x, int y) {
        cc_PropertyList[label].numPixels += 1;
        if (x < cc_PropertyList[label].minRow) {
            cc_PropertyList[label].minRow = x;
        }
        if (y < cc_PropertyList[label].minCol) {
            cc_PropertyList[label].minCol = y;
        }
        if (x > cc_PropertyList[label].maxRow) {
            cc_PropertyList[label].maxRow = x;
        }
        if (y > cc_PropertyList[label].maxCol) {
            cc_PropertyList[label].maxCol = y;
        }
    }//propUpdate

    private void prettyPrint(int pass, PrintWriter out) {
        out.write("PrettyPrint of Connected_CC_Pass" + pass + ":\n");
        out.write("NumRows:" + numRows + " NumCols:" + numCols + "\n");
        int temp;
        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                temp = zeroFramedAry[i][j];
                if (temp > 0) {
                    out.write(temp + " ");
                } else {
                    out.write("  ");
                }
            }//for j
            out.write("\n");
        }//for i
        out.write("\n\n");
    }//prettyPrint

    void toBinary(PrintWriter out) {
        out.write(numRows + " " + numCols + " " + newMin + " " + newMax + "\n");
        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                if (zeroFramedAry[i][j] > 0) {
                    out.write(1 + " ");
                } else {
                    out.write(0 + " ");
                }
            }//for j
            out.write("\n");
        }//for i
    }//toBinary
}//Connected_CC

//Angelo Zamudio CS381 Fall 16'

