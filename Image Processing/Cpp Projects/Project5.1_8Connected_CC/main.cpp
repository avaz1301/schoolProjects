#include <iostream>
#include <fstream>

using namespace std;

struct Property {
    int label = 0;
    int numbpixels = 0;
    int minRow = 0, minCol = 0, maxRow = 0, maxCol = 0;
};

class EightConnectedCC {
private:
    int numRows = 0, numCols = 0, minVal = 0, maxVal = 0;
    int newMin = 100, newMax = 0, newLabel = 0;
    int **zeroFramedAry;
    int *EQAry;
    int *neighborAry;
    Property *prop;
    int propSize = 0;
public:
    EightConnectedCC(ifstream &in) {
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

    ~EightConnectedCC() {
        delete zeroFramedAry;
        delete EQAry;
        delete neighborAry;
        delete prop;
    }

    void loadImage(ifstream &in, ofstream &out, ofstream &out2) {
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
        Connect_CC_Pass1(out);
        Connect_CC_Pass2(out);
        Connect_CC_Pass3(out, out2);
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

    void loadNeighbors(int pass, int row, int column) {
        //adds values to neighborAry
        if (pass == 1) {
            neighborAry[0] = zeroFramedAry[row - 1][column - 1];
            neighborAry[1] = zeroFramedAry[row - 1][column];
            neighborAry[2] = zeroFramedAry[row - 1][column + 1];
            neighborAry[3] = zeroFramedAry[row][column - 1];
        } else if (pass == 2) {
            neighborAry[0] = zeroFramedAry[row][column + 1];
            neighborAry[1] = zeroFramedAry[row + 1][column - 1];
            neighborAry[2] = zeroFramedAry[row + 1][column];
            neighborAry[3] = zeroFramedAry[row + 1][column + 1];
        }
    }//loadNeighbors

    void Connect_CC_Pass1(ofstream &out) {
        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                if (zeroFramedAry[i][j] == 1) {
                    loadNeighbors(1, i, j);
                    int a = neighborAry[0], b = neighborAry[1];
                    int c = neighborAry[2], d = neighborAry[3];

                    if (a == 0 && b == 0 && c == 0 && d == 0) {//case 1
                        newLabel++;
                        zeroFramedAry[i][j] = newLabel;
                    } else {
                        int local_min = INT_MAX;
                        for (int k = 0; k < 4; k++) {
                            if (neighborAry[k] != 0) { local_min = min(local_min, neighborAry[k]); }
                        }
                        zeroFramedAry[i][j] = local_min;
                    }
                }//if > 1
            }//for j
        }//for i
    }//Connected_CC_Pass2

    void Connect_CC_Pass2(ofstream &out) {
        for (int i = numRows + 1; i > 0; --i) {
            for (int j = numCols + 1; j > 0; --j) {
                if (zeroFramedAry[i][j] > 0) {
                    loadNeighbors(2, i, j);
                    int x = zeroFramedAry[i][j];
                    int e = neighborAry[0];
                    int f = neighborAry[1];
                    int g = neighborAry[2];
                    int h = neighborAry[3];

                    if (e != 0 && f != 0 && g != 0 && h != 0) {//case 3.1
                        int local_min = INT_MAX;
                        for (int k = 0; k < 4; k++) {
                            if (neighborAry[k] != 0) { local_min = min(local_min, neighborAry[k]); }
                        }
                        if (local_min < x) {
                            zeroFramedAry[i][j] = local_min;
                            updateEQAry(x, local_min);
                        }
                    }//if != 0
                }//if > 0
            }//for j
        }//for i
        manageEQAry();
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
        printArray(out);
        printPropFile(out2);
    }//Connected_CC_Pass3

    void propUpdate(int label, int x, int y) {
        prop[label].numbpixels += 1;
        if (x < prop[label].minRow) {
            prop[label].minRow = x - 1;
        }
        if (y < prop[label].minCol) {
            prop[label].minCol = y - 1;
        }
        if (x > prop[label].maxRow) {
            prop[label].maxRow = x - 1;
        }
        if (y > prop[label].maxCol) {
            prop[label].maxCol = y - 1;
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

    void printPropFile(ofstream &out) {
        for (int i = 1; i < propSize; ++i) {
            if (prop[i].numbpixels != 0) {
                out << prop[i].label << " " << prop[i].numbpixels << " " << prop[i].minRow << " " << prop[i].minCol
                    << " " << prop[i].maxRow << " " << prop[i].maxCol << "\n";
            }
        }//for i
    }

    void printArray(ofstream &out) {
        out << numRows << " " << numCols << " " << newMin << " " << newMax << "\n";
        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                out << zeroFramedAry[i][j] << " ";
            }//for j
            out << "\n";
        }//for i
        out << "\n\n";
    }
};

int main(int argc, char *argv[]) {
    if (!argv[1]) {
        cout << "Please provide an input..." << "\n";
        exit(1);
    }
    ifstream in(argv[1]);
    ofstream out1(argv[2]);
    ofstream out2(argv[3]);
    EightConnectedCC Connect1(in);
    Connect1.loadImage(in, out1, out2);
    in.close();
    out1.close();
    out2.close();
    return 0;
};
//Angelo Zamudio CS381 Fall 16'
