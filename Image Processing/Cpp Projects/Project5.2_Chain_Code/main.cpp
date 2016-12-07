#include <iostream>
#include <fstream>

using namespace std;

class Image {
    friend class CCProperty;

    friend class ChainCode;

private:
    int numRows = 0, numCols = 0, minVal = INT_MAX, maxVal = 0;
    int **zeroFramedAry;
public:
    Image(ifstream &in) {
        in >> numRows >> numCols >> minVal >> maxVal;
        zeroFramedAry = new int *[numRows + 2];
        for (int i = 0; i < numRows + 2; ++i) {
            zeroFramedAry[i] = new int[numCols + 2]();
        }
        loadImage(in);
    }

    ~Image() {
//        delete zeroFramedAry;
    }

    void loadImage(ifstream &in) {
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
};

struct Property {
    int label = 0;
    int numpixels = 0;
    int minRow = 100, minCol = 100, maxRow = 0, maxCol = 0;
};

class CCProperty {
    friend class ChainCode;

private:
    Property *propAry;
    int maxCC, label, numPixels, minRow, minCol, maxRow, maxCol;
public:
    CCProperty(Image img, ifstream &in) {
        maxCC = img.maxVal;
        propAry = new Property[maxCC + 1];
        //go through property file and populate propAry with all connected components
        for (int i = 1; i < maxCC + 1; ++i) {
            if (in) {
                in >> label >> numPixels >> minRow >> minCol >> maxRow >> maxCol;
                propAry[i].label = label;
                propAry[i].numpixels = numPixels;
                propAry[i].minRow = minRow;
                propAry[i].minCol = minCol;
                propAry[i].maxRow = maxRow;
                propAry[i].maxCol = maxCol;
            }
        }
    }

    ~CCProperty() {
        delete propAry;
    }
};

struct Pointer {
    int row, col;

    void setPointer(int r, int c) {
        row = r;
        col = c;
    }
};

class ChainCode {
private:
    int currentCC = 0, minRowOffset, maxRowOffset, minColOffset, maxColOffset;
    Pointer *neighborCoord;
    Pointer startP, currentP, nextP;
    int nextQ = 0, pChain, lastQ;
    int nextDirTable[8] = {6, 0, 0, 2, 2, 4, 4, 6};
public:
    ChainCode(Image &img, CCProperty &cc, ofstream &out) {
        //set flag when we find first pixel of value currentCC
        bool startSet = false;
        neighborCoord = new Pointer[8];
        currentCC++;
        //iterate through each CC in the propAry
        while (currentCC <= cc.maxCC) {
            minRowOffset = cc.propAry[currentCC].minRow;
            maxRowOffset = cc.propAry[currentCC].maxRow;
            minColOffset = cc.propAry[currentCC].minCol;
            maxColOffset = cc.propAry[currentCC].maxCol;
            //search bounding box for first pixel equal to currentCC
            for (int i = minRowOffset + 1; i < maxRowOffset + 1; ++i) {
                for (int j = minColOffset + 1; j < maxColOffset + 1; ++j) {
                    int pixel = img.zeroFramedAry[i][j];
                    //when found, set start flag to ensure Chain Code only happens once per label
                    if (pixel == currentCC && (!startSet)) {
                        startSet = true;
                        out << i << " " << j <<" "<< currentCC<<" --> ";
                        //set StartP, currentP, lastQ and nextQ for first iteration
                        startP.setPointer(i, j);
                        currentP.setPointer(i, j);
                        lastQ = 4;
                        nextQ = (lastQ + 1) % 8;
                        //find first pChain direction for currentCC
                        pChain = findNextP(currentP, nextP, nextQ, currentCC, img);
                        out << pChain << " ";
                        //check for negative value to prevent Index out of Bounds Exception
                        //set lastQ to value of pChain in Direction Table
                        (pChain - 1 == -1) ? lastQ = nextDirTable[7] : lastQ = nextDirTable[pChain - 1];
                        //move currentP to nextP
                        currentP.setPointer(nextP.row, nextP.col);
                        //repeat findNextP until currentP == startP;
                        while ((currentP.row != startP.row) | (currentP.col != startP.col)) {
                            //set start position for next iteration of findNextP
                            nextQ = (lastQ + 1) % 8;
                            pChain = findNextP(currentP, nextP, nextQ, currentCC, img);
                            out << pChain << " ";
                            (pChain - 1 == -1) ? lastQ = nextDirTable[7] : lastQ = nextDirTable[pChain - 1];
                            currentP.setPointer(nextP.row, nextP.col);
                        }//while
                        out << "\n";
                    }
                }//for j
            }//for i
            //move to next CC in propAry
            currentCC++;
            //reset start flag
            startSet = false;
        }//while
    }

    ~ChainCode() {
        delete neighborCoord;
    }

    int findNextP(Pointer &currentP, Pointer &nextP, int next_Q, int current_CC, Image &img) {
        int chainDir = 0;
        //load 8 neighbors with respect to currentP
        loadNeighborCoords(currentP.row, currentP.col);
        int i = nextQ;
        //search neighbors until first neighbor with the same label is found
        while (img.zeroFramedAry[neighborCoord[i].row][neighborCoord[i].col] != current_CC) {
            i = (i + 1) % 8;
        }
        chainDir = i;
        //set neighbor as nextP
        nextP.setPointer(neighborCoord[i].row, neighborCoord[i].col);
        return chainDir;
    }//findNext

    void loadNeighborCoords(int row, int col) {
        neighborCoord[0].setPointer(row, col + 1);
        neighborCoord[1].setPointer(row - 1, col + 1);
        neighborCoord[2].setPointer(row - 1, col);
        neighborCoord[3].setPointer(row - 1, col - 1);
        neighborCoord[4].setPointer(row, col - 1);
        neighborCoord[5].setPointer(row + 1, col - 1);
        neighborCoord[6].setPointer(row + 1, col);
        neighborCoord[7].setPointer(row + 1, col + 1);
    }//loadNeighbors

    void prettyPrint(Image &img, ofstream &out) {
        cout << "\n\n";
        for (int i = 1; i < img.numRows + 1; ++i) {
            for (int j = 1; j < img.numCols + 1; ++j) {
                if (img.zeroFramedAry[i][j] != 0) {
                    out << img.zeroFramedAry[i][j] << " ";
                } else {
                    out << "  ";
                }
            }//for j
            out << "\n";
        }//for i
    }//prettyprint
};


int main(int argc, char *argv[]) {
    if (!argv[1]) {
        cout << "Please provide an input..." << "\n";
        exit(1);
    }
    ifstream in(argv[1]);
    ifstream in2(argv[2]);
    ofstream out(argv[3]);
    ofstream out2(argv[4]);
    Image img(in);
    CCProperty ccp(img, in2);
    ChainCode cc(img, ccp, out);
    cc.prettyPrint(img, out2);
    in.close();
    in2.close();
    out.close();
    out2.close();
    return 0;
}


//Angelo Zamudio CS381 Fall 16'
