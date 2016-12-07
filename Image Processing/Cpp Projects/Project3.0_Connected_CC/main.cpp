#include <iostream>
#include<fstream>
using namespace std;

struct Property {
    int label = 0;
    int numbpixels = 0;
    int minRow = 0, minCol = 0, maxRow = 0, maxCol = 0;
};

class ConnectedCC {
private:
    int numRows = 0, numCols = 0, minVal = 0, maxVal = 0;
    int newMin = 100, newMax = 0, newLabel = 0;
    int **zeroFramedAry;
    int *EQAry;
    int *neighborAry;
    Property *prop;
    int propSize = 0;
public:
    ConnectedCC(ifstream &in) {
        in >> numRows >> numCols >> minVal >> maxVal;
        int eqsize = (numRows * numCols) / 4;

        zeroFramedAry = new int *[numRows + 2];
        EQAry = new int[eqsize]();
        neighborAry = new int[3]();

        for (int i = 0; i < numRows + 2; ++i) {
            zeroFramedAry[i] = new int[numCols + 2]();
        }
        for (int j = 0; j < eqsize; ++j) {
            EQAry[j] = j;
        }
    }

    ~ConnectedCC() {
        delete zeroFramedAry;
        delete EQAry;
        delete neighborAry;
        delete prop;
    }

    void loadimage(ifstream &in) {
        if (in) {
            int pixel = 0;
            //process image into mirrorFramedArray starting at (1,1)
            for (int i = 1; i < numRows + 1; ++i) {
                for (int j = 1; j < numCols + 1; ++j) {
                    in >> pixel;
                    zeroFramedAry[i][j] = pixel;
                }//for j
            }//for i
        }
        zeroFramed();
    }//loadImage

    void zeroFramed() {
        //fills first and last column with mirrored value
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

    void loadNeighbors(int row, int column) {
        //adds values to neighborAry
        neighborAry[0] = zeroFramedAry[row - 1][column];
        neighborAry[1] = zeroFramedAry[row][column - 1];
        neighborAry[2] = zeroFramedAry[row][column + 1];
        neighborAry[3] = zeroFramedAry[row + 1][column];
    }//loadNeighbors

    void Connect_CC_Pass1(ofstream &out) {
        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                if (zeroFramedAry[i][j] == 1) {
                    loadNeighbors(i, j);
                    int a = neighborAry[0];
                    int b = neighborAry[1];
                    if (a == 0 && b == 0) {//case 1
                        newLabel++;
                        zeroFramedAry[i][j] = newLabel;
                    }
                    else if (a > 0 && b > 0) {//case 3.1
                        zeroFramedAry[i][j] = min(a, b);
                    }
                    else if (a == 0) {//case 3.2
                        zeroFramedAry[i][j] = b;

                    }
                    else if (b == 0) {//case 3.3
                        zeroFramedAry[i][j] = a;
                    }

                }//if > 1
            }//for j
        }//for i
        prettyPrint(1, out);
        out << "EQAry:\n";
        for (int k = 1; k < newLabel; ++k) {
            out << "[" << k << "]";
        }
        out << "\n";
        for (int k = 1; k < newLabel; ++k) {
            out << " " << EQAry[k] << " ";
        }
        out << "\n\n";
    }//Connected_CC_Pass2

    void Connect_CC_Pass2(ofstream &out) {
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
                            zeroFramedAry[i][j] = min(min(c, d), x);
                            if (zeroFramedAry[i][j] != x) {
                                updateEQAry(x, zeroFramedAry[i][j]);
                            }
                        } else if (c == d && x > c) {//3.1B
                            //if X is different from C and D
                            zeroFramedAry[i][j] = c;
                            updateEQAry(x, c);
                        } else if (x != c && c != d && d != x) {//3.1C
                            // if X, C and D are different
                            zeroFramedAry[i][j] = min(min(c, d), x);
                            if (zeroFramedAry[i][j] != x) {
                                updateEQAry(x, zeroFramedAry[i][j]);
                            }
                        }
                    }
                    else if (c != 0) {//case 3.2
                        zeroFramedAry[i][j] = c;
                        updateEQAry(x, c);
                    }
                    else if (d != 0) {//case 3.3
                        zeroFramedAry[i][j] = d;
                        updateEQAry(x, d);
                    }

                }//if
            }//for j
        }//for i
        prettyPrint(2, out);
        out << "EQAry:\n";
        for (int k = 1; k < newLabel; ++k) {
            out << "[" << k << "]";
        }
        out << "\n";
        for (int k = 1; k < newLabel; ++k) {
            out << " " << EQAry[k] << " ";
        }
        out << "\n\n";
        manageEQAry();
        out << "EQAry After Management: \n";
        for (int k = 1; k < newLabel; ++k) {
            out << "[" << k << "]";
        }
        out << "\n";
        for (int k = 1; k < newLabel; ++k) {
            out << " " << EQAry[k] << " ";
        }
        out << "\n\n";
    }//Connected_CC_Pass2

    void Connect_CC_Pass3(ofstream &out, ofstream &out2) {
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
        out << "EQAry:\n";
        for (int k = 1; k < newLabel; ++k) {
            out << "[" << k << "]";
        }
        out << "\n";
        for (int k = 1; k < newLabel; ++k) {
            out << " " << EQAry[k] << " ";
        }
        out << "\n\n";
        for (int i = 1; i < propSize; ++i) {
            if (prop[i].numbpixels != 0) {
                out2 << "Label: " << prop[i].label << "\n";
                out2 << "# of Pixels: " << prop[i].numbpixels << "\n";
                out2 << "minRow: " << prop[i].minRow << " minCol: " << prop[i].minCol << " maxRow: " <<
                prop[i].maxRow <<
                " maxCol: " << prop[i].maxCol << "\n\n";
            }
        }//for i
    }//Connected_CC_Pass3

    void propUpdate(int label, int x, int y) {
        prop[label].numbpixels += 1;
        if (x < prop[label].minRow) {
            prop[label].minRow = x;
        }
        if (y < prop[label].minCol) {
            prop[label].minCol = y;
        }
        if (x > prop[label].maxRow) {
            prop[label].maxRow = x;
        }
        if (y > prop[label].maxCol) {
            prop[label].maxCol = y;
        }
    }//propUpdate

    void updateEQAry(int pos, int newVal) {
        if (newVal < EQAry[pos]) {
            EQAry[pos] = newVal;
        }
    }//updateEQAry

    void manageEQAry() {
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
        prop = new Property[nlu + 1];
        propSize = nlu + 1;
        for (int j = 0; j < nlu + 1; ++j) {
            prop[j].label = j;
            prop[j].minRow = (numRows * numCols) / 4;
            prop[j].minCol = (numRows * numCols) / 4;
        }


    }//manageEQAry

    void prettyPrint(int pass, ofstream &out) {
        out << "PrettyPrint of Connected_CC_Pass" << pass << ":\n";
        out << "NumRows:" << numRows << " NumCols:" << numCols << "\n";
        int temp = 0;
        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                temp = zeroFramedAry[i][j];
                if (temp > 0) {
                    out << temp << " ";
                } else {
                    out << "  ";
                }
            }//for j
            out << "\n";
        }//for i
        out << "\n\n";
    }//prettyPrint

    void toBinary(ofstream &out) {
        out << numRows << " " << numCols << " " << newMin << " " << newMax << "\n";
        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                if (zeroFramedAry[i][j] > 0) {
                    out << 1 << "";
                } else {
                    out << 0 << "";
                }
            }//for j
            out << "\n";
        }//for i
    }//toBinary
};


int main(int argc, char *argv[]) {
    if (!argv[1]) {
        cout << "Please provide an input..." << "\n";
        exit(1);
    }
    ifstream in(argv[1]);
    ofstream out1(argv[2]);
    ofstream out2(argv[3]);
    ofstream out3(argv[4]);

    ConnectedCC Connect1(in);
    Connect1.loadimage(in);
    Connect1.Connect_CC_Pass1(out1);
    Connect1.Connect_CC_Pass2(out1);
    Connect1.Connect_CC_Pass3(out1, out3);
    Connect1.toBinary(out2);

    in.close();
    out1.close();
    out2.close();
    out3.close();
    return 0;
};
//Angelo Zamudio CS381 Fall 16'
