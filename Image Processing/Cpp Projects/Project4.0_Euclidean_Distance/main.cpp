#include <iostream>
#include <math.h>
#include<fstream>

using namespace std;

class EuclideanTransform {
private:
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    double newMin;
    double newMax;
    double sqRoot;
    double **zeroFramedAry;
    double *neighborAry;

public:
    EuclideanTransform(ifstream &in) {
        in >> numRows >> numCols >> minVal >> maxVal;
        sqRoot=sqrt(2);
        newMin=100;
        newMax=0;
        zeroFramedAry = new double *[numRows + 2];
        neighborAry = new double[5]();

        for (int i = 0; i < numRows + 2; ++i) {
            zeroFramedAry[i] = new double[numCols + 2]();
        }
    }

    ~EuclideanTransform() {
        for (int i = 0; i < numRows + 2; ++i) {
            delete zeroFramedAry[i];
        }
        delete zeroFramedAry;
        delete neighborAry;
    }

    void loadimage(ifstream &in) {
        if (in) {
            double pixel = 0.0;
            //process image into zeroFramedArray starting at (1,1)
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
        //fills first and last column with 0
        for (int j = 0; j <= numRows + 1; ++j) {
            zeroFramedAry[j][0] = 0;
            zeroFramedAry[j][numCols + 1] = 0;
        }
        //fills first and last row with 0
        for (int k = 0; k <= numCols + 1; ++k) {
            zeroFramedAry[0][k] = 0;
            zeroFramedAry[numRows + 1][k] = 0;
        }
    }//zeroFramed

    void loadNeighbors(int pass, int row, int column) {
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

    void firstPassEuclideanDistance(ofstream &out) {
        double mini;
        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                if (zeroFramedAry[i][j] > 0) {
                    loadNeighbors(1, i, j);
                    mini = min(neighborAry[1], min(neighborAry[2], min(neighborAry[3], neighborAry[4])));
                    zeroFramedAry[i][j] = mini;
                    newMin = (zeroFramedAry[i][j] < newMin) ? (zeroFramedAry[i][j]) : newMin;
                    newMax = (zeroFramedAry[i][j] > newMax) ? (zeroFramedAry[i][j]) : newMax;
                }//if
            }//for j
        }//for i
        prettyPrintDistance(1, out);
    }//firstPass

    void secondPassEuclideanDistance(ofstream &out, ofstream &out1) {
        double mini;
        newMin = 100;
        newMax = 0;
        for (int i = numRows + 1; i > 0; --i) {
            for (int j = numCols + 1; j > 0; --j) {
                if (zeroFramedAry[i][j] > 0) {
                    loadNeighbors(2, i, j);
                    mini = min( neighborAry[0], min(neighborAry[1], min(neighborAry[2], min(neighborAry[3], neighborAry[4]))));
                    zeroFramedAry[i][j] = mini;
                    newMin = (zeroFramedAry[i][j] < newMin) ? (zeroFramedAry[i][j]) : newMin;
                    newMax = (zeroFramedAry[i][j] > newMax) ? (zeroFramedAry[i][j]) : newMax;
                }//if
            }//for j
        }//for i
        prettyPrintDistance(2, out);

        double dist_pixel = 0;
        out1 << numRows << " " << numCols << " " << (int) (newMin + .5) << " " << (int) (newMax + .5) << "\n";
        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                if (zeroFramedAry[i][j] > 0) {
                    dist_pixel = (int) (zeroFramedAry[i][j] + .5);
                    out1 << dist_pixel << " ";
                } else {
                    out1 << 0 << " ";
                }
            }
            out1 << "\n";
        }
        out << "\n\n";
    }//secondEuclideanPass

    void prettyPrintDistance(int pass, ofstream &out) {
        out << "Result of Pass " << pass << ": \n";
        out << "NumRows:" << numRows << " NumCols:" << numCols << " NewMin:" << (int) (newMin + .5) << " NewMax:" <<
        (int) (newMax + .5) << "\n";
        int pixel = 0;
        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                if (zeroFramedAry[i][j] > 0) {
                    pixel = (int) (zeroFramedAry[i][j] + .5);
                    out << pixel << " ";
                } else {
                    out << "  ";
                }
            }
            out << "\n";
        }
        out << "\n\n";
    }//prettyPrint
};

int main(int argc, char *argv[]) {
    if (!argv[1]) {
        cout << "Please provide proper input and output files..." << "\n";
        exit(1);
    }
    ifstream in(argv[1]);
    ofstream out1(argv[3]);
    ofstream out2(argv[2]);

    EuclideanTransform Euclid1(in);
    Euclid1.loadimage(in);
    Euclid1.firstPassEuclideanDistance(out1);
    Euclid1.secondPassEuclideanDistance(out1, out2);

    in.close();
    out1.close();
    out2.close();
    return 0;
};
//Angelo Zamudio CS381 Fall 16'
