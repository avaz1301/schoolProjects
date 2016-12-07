#include <iostream>
#include <fstream>
using namespace std;

class RunLengthDecode {
private:
    int numRows = 0, numCols = 0, minVal = 0, maxVal = 0;
    int rowPos = 0, colPos = 0, color = 0, length = 0;
    int **imageAry;
public:
    RunLengthDecode(ifstream &in, ofstream &out) {
        in >> numRows >> numCols >> minVal >> maxVal;
        imageAry = new int *[numRows];
        for (int i = 0; i < numRows; ++i) {
            imageAry[i] = new int[numCols]();
        }
        decode(in, out);
    }

    void decode(ifstream &in, ofstream &out) {
        if (in) {
            in >> rowPos >> colPos >> color >> length;
            cout << rowPos << " " << colPos << " " << color << " " << length << "\n";
            for (int i = rowPos; i < numRows; ++i) {
                if (i > rowPos) {
                    in >> rowPos >> colPos >> color >> length;
                }
                for (int j = 0; j < numCols; ++j) {
                    if (i == rowPos && (j >= colPos && j < colPos + length)) {
                        imageAry[i][j] = color;
                    } else if (i == rowPos && j == colPos + length) {
                        in >> rowPos >> colPos >> color >> length;
                        if (i == rowPos && j == colPos) {
                            imageAry[i][j] = color;
                        }
                    }
                }//for j
            }//for i
            printArray(out);
        }//if
    }//decode

    void printArray(ofstream &out) {
        out << numRows << " " << numCols << " " << minVal << " " << maxVal << "\n";
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                out << imageAry[i][j] << " ";
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
    RunLengthDecode decode1(in, out1);
    in.close();
    out1.close();
    return 0;
};

//Angelo Zamudio CS381 Fall 16'

