#include <iostream>
#include <fstream>

using namespace std;

class Morphology {
private:
    int numRowsImg;
    int numColsImg;
    int minValImg;
    int maxValImg;

    int numRowsStruct;
    int numColsStruct;
    int minValStruct;
    int maxValStruct;

    int rowOrigin;
    int colOrigin;
    int rowFrameSize;
    int colFrameSize;

    int **imgAry;
    int **morphAry;
    int **structElm;
    int **tempAry;
public:
    Morphology(ifstream &in1, ifstream &in2, ofstream &out1, ofstream &out2, ofstream &out3, ofstream &out4) {
        in1 >> numRowsImg >> numColsImg >> minValImg >> maxValImg;
        in2 >> numRowsStruct >> numColsStruct >> minValStruct >> maxValStruct;
        in2 >> rowOrigin >> colOrigin;
        computeFrameSize();

        morphAry = new int *[numRowsImg + rowFrameSize];
        tempAry = new int *[numRowsImg + rowFrameSize];
        for (int i = 0; i < numRowsImg + rowFrameSize; ++i) {
            morphAry[i] = new int[numColsImg + colFrameSize]();
            tempAry[i] = new int[numColsImg + colFrameSize]();
        }

        imgAry = new int *[numRowsImg + 2];
        for (int i = 0; i < numRowsImg + 2; ++i) {
            imgAry[i] = new int[numColsImg + 2]();
        }
        zeroFrame();
        loadImage(in1);

        structElm = new int *[numRowsStruct];
        for (int i = 0; i < numRowsStruct; ++i) {
            structElm[i] = new int[numColsStruct]();
        }
        loadStruct(in2);

        dilation(numRowsImg + 2, numColsImg + 2, imgAry, morphAry);
        cout << "Dilation result: \n";
        outputResult(numRowsImg + rowFrameSize, numColsImg + colFrameSize, morphAry, out1);
        prettyPrint(numRowsImg + rowFrameSize, numColsImg + colFrameSize, morphAry);
        resetMorph();

        erosion(numRowsImg + 2, numColsImg + 2, imgAry, morphAry);
        cout << "Erosion result: \n";
        outputResult(numRowsImg + rowFrameSize, numColsImg + colFrameSize, morphAry, out2);
        prettyPrint(numRowsImg + rowFrameSize, numColsImg + colFrameSize, morphAry);
        resetMorph();

        closing();
        cout << "Closing result: \n";
        outputResult(numRowsImg + rowFrameSize, numColsImg + colFrameSize, tempAry, out3);
        prettyPrint(numRowsImg + rowFrameSize, numColsImg + colFrameSize, tempAry);
        resetMorph();

        opening();
        cout << "Opening result: \n";
        outputResult(numRowsImg + rowFrameSize, numColsImg + colFrameSize, tempAry, out4);
        prettyPrint(numRowsImg + rowFrameSize, numColsImg + colFrameSize, tempAry);
        resetMorph();
    }

    ~Morphology() {
        delete imgAry;
        delete morphAry;
        delete structElm;
    }

    void loadImage(ifstream &in) {
        if (in) {
            int pixel = 0;
            for (int i = 1; i < numRowsImg + 1; ++i) {
                for (int j = 1; j < numColsImg + 1; ++j) {
                    in >> pixel;
                    imgAry[i][j] = pixel;
                }
            }
        }
    }

    void loadStruct(ifstream &in) {
        if (in) {
            int pixel = 0;
            for (int i = 0; i < numRowsStruct; ++i) {
                for (int j = 0; j < numColsStruct; ++j) {
                    in >> pixel;
                    structElm[i][j] = pixel;
                }
            }
        }
        prettyPrint(numRowsStruct, numColsStruct, structElm);
    }

    void zeroFrame() {
        for (int j = 0; j <= numRowsImg + 1; ++j) {
            imgAry[j][0] = 0;
            imgAry[j][numColsImg + 1] = 0;
        }
        //fills first and last row with mirrored value
        for (int k = 0; k <= numColsImg + 1; ++k) {
            imgAry[0][k] = 0;
            imgAry[numRowsImg + 1][k] = 0;
        }
    }

    void computeFrameSize() {
        rowFrameSize = numRowsStruct;
        colFrameSize = numColsStruct;
    }

    void dilation(int row, int col, int **ary, int **res) {
        for (int i = numRowsStruct / 2; i < row - (numRowsStruct / 2); ++i) {
            for (int j = numColsStruct / 2; j < col - (numRowsStruct / 2); ++j) {
                int pixel = ary[i][j];
                if (pixel != 0) {
                    int r_c = 0;
                    int c_c = 0;
                    for (int k = i - rowOrigin; k <= i + (numRowsStruct / 2); ++k) {
                        for (int l = j - colOrigin; l <= j + (numColsStruct / 2); ++l) {
                            if (ary[k][l] == 0 && structElm[r_c][c_c] == 1) {
                                res[k][l] = 1;
                            } else if (ary[k][l] == 1 && structElm[r_c][c_c] == 1) {
                                res[k][l] = 1;
                            }
                            c_c++;
                        }
                        r_c++;
                        c_c = 0;
                    }
                }
            }
        }
    }

    void erosion(int row, int col, int **ary, int **res) {
        for (int i = numRowsStruct / 2; i < row - (numRowsStruct / 2); ++i) {
            for (int j = numColsStruct / 2; j < col - (numRowsStruct / 2); ++j) {
                int pixel = ary[i][j];
                if (pixel != 0) {
                    bool stands = true;
                    int r_c = 0;
                    int c_c = 0;
                    for (int k = i - rowOrigin; k <= i + (numRowsStruct / 2); ++k) {
                        for (int l = j - colOrigin; l <= j + (numColsStruct / 2); ++l) {
                            if (ary[k][l] == 0 && structElm[r_c][c_c] == 1) {
                                stands = false;
                            }
                            c_c++;
                        }
                        r_c++;
                        c_c = 0;
                    }
                    if (stands) {
                        res[i][j]=1;
                    }//if
                }//if
            }//for j
        }//for i;;;;
    }

    void closing() {
        //erosion(-) + dilation(+)
        dilation(numRowsImg + 2, numColsImg + 2, imgAry, morphAry);
        erosion(numRowsImg + rowFrameSize, numColsImg + colFrameSize, morphAry, tempAry);
    }

    void opening() {
        //dilation(+) + erosion(-)
        erosion(numRowsImg + 2, numColsImg + 2, imgAry, morphAry);
        dilation(numRowsImg + rowFrameSize, numColsImg + colFrameSize, morphAry, tempAry);
    }

    void outputResult(int row, int col, int **array, ofstream &out) {
        out << numRowsImg << " " << numColsImg << " " << minValImg << " " << maxValImg << "\n";
        for (int i = 1; i < numRowsImg + 1; ++i) {
            for (int j = 1; j < numColsImg + 1; ++j) {
                out << array[i][j] << " ";
            }//for j
            out << "\n";
        }
    }

    void resetMorph() {
        for (int i = 0; i < numRowsImg + rowFrameSize; ++i) {
            for (int j = 0; j < numColsImg + colFrameSize; ++j) {
                morphAry[i][j] = 0;
                tempAry[i][j] = 0;
            }//for j
        }
    }


    void prettyPrint(int row, int col, int **array) {
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (array[i][j] != 0) {
                    cout << array[i][j] << " ";
                } else {
                    cout << "  ";
                }
            }//for j
            cout << "\n";
        }
    }//PP
};


int main(int argc, char *argv[]) {
    ifstream in(argv[1]);
    ifstream in2(argv[2]);
    ofstream out1(argv[3]);
    ofstream out2(argv[4]);
    ofstream out3(argv[5]);
    ofstream out4(argv[6]);
    Morphology m1(in, in2, out1, out2, out3, out4);
    in.close();
    in2.close();
    out1.close();
    out2.close();
    out3.close();
    out4.close();
    return 0;
}
//Angelo Zamudio CS381 Spring 16'