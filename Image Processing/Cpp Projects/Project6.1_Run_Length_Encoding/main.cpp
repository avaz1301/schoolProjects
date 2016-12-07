#include <iostream>
#include <fstream>
using namespace std;

class RunLengthEncode {
private:
    int numRows = 0, numCols = 0, minVal = 0, maxVal = 0;
    int rowPos = INT_MAX, colPos = INT_MAX;
    int curr_Color = 0, curr_length = 0;
    int **imageAry;

public:
    RunLengthEncode(ifstream &in, ofstream &out) {
        in >> numRows >> numCols >> minVal >> maxVal;
        imageAry = new int *[numRows];
        for (int i = 0; i < numRows; ++i) {
            imageAry[i] = new int[numCols]();
        }
        loadimage(in);
        encode(out);
    }

    ~RunLengthEncode() {
        delete imageAry;
    }

    void loadimage(ifstream &in) {
        if (in) {
            int pixel = 0;
            //process image into mirrorFramedArray starting at (1,1)
            for (int i = 0; i < numRows; ++i) {
                for (int j = 0; j < numCols; ++j) {
                    in >> pixel;
                    imageAry[i][j] = pixel;
                }//for j
            }//for i
        }
    }//loadImage

    void encode(ofstream &out) {
        out << numRows << " " << numCols << " " << minVal << " " << maxVal << "\n";
        int pixel = 0;
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                pixel = imageAry[i][j];
                if (pixel == 0) {
                    if (curr_length > 0) {
                        out << curr_length << " \n";
                        curr_Color = 0;
                        curr_length = 0;
                    } else {
                        curr_Color = 0;
                        curr_length = 0;
                    }
                } else {
                    if (pixel == curr_Color) {
                        curr_length++;
                    } else {
                        if (curr_length > 0) {
                            out << curr_length << " \n";
                            curr_Color = 0;
                            curr_length = 0;
                        }
                        rowPos = i;
                        colPos = j;
                        curr_Color = pixel;
                        curr_length = 1;
                        out << rowPos << " " << colPos << " " << curr_Color << " ";
                    }
                }
            }//for j
            if (curr_length > 0) {
                out << curr_length << " \n";
                curr_Color = 0;
                curr_length = 0;
            }
        }//for i
        out << "\n";
    }

    void printArray() {
        cout << numRows << " " << numCols << " " << minVal << " " << maxVal << "\n";
        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                cout << imageAry[i][j] << " ";
            }//for j
            cout << "\n";
        }//for i
        cout << "\n\n";
    }
};

int main(int argc, char *argv[]) {
    if (!argv[1]) {
        cout << "Please provide an input..." << "\n";
        exit(1);
    }
    ifstream in(argv[1]);
    ofstream out1(argv[2]);
    RunLengthEncode encode1(in, out1);
    in.close();
    out1.close();
    return 0;
};

//Angelo Zamudio CS381 Fall 16'