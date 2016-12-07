#include <iostream>
#include<fstream>

using namespace std;

class MedianFilter {
private:
    int numRows = 0, numCols = 0, minVal = 0, maxVal = 0;
    int newMin = 0, newMax = 0;
    int **mirrorFramedAry;
    int **tempAry;
    int *neighborAry;

public:
    MedianFilter(ifstream &in) {
        in >> numRows >> numCols >> minVal >> maxVal;
        newMin = minVal;
        newMax = maxVal;

        mirrorFramedAry = new int *[numRows + 2];
        tempAry = new int *[numRows + 2];
        neighborAry = new int[9]();

        for (int i = 0; i < numRows + 2; ++i) {
            mirrorFramedAry[i] = new int[numCols + 2]();
            tempAry[i] = new int[numCols + 2]();
        }
    }

    ~MedianFilter() {
        delete mirrorFramedAry;
        delete tempAry;
        delete neighborAry;
    }

    void loadimage(ifstream &in) {
        if (in) {
            int pixel = 0;
            //process image into mirrorFramedArray starting at (1,1)
            for (int i = 1; i < numRows + 1; ++i) {
                for (int j = 1; j < numCols + 1; ++j) {
                    in >> pixel;
                    mirrorFramedAry[i][j] = pixel;
                }//for j
            }//for i
        }
        mirrorFramed();
    }//loadImage

    void mirrorFramed() {
        //fills first and last column with mirrored value
        for (int j = 0; j <= numRows + 1; ++j) {
            mirrorFramedAry[j][0] = mirrorFramedAry[j][1];
            mirrorFramedAry[j][numCols + 1] = mirrorFramedAry[j][numCols];
        }
        //fills first and last row with mirrored value
        for (int k = 0; k <= numCols + 1; ++k) {
            mirrorFramedAry[0][k] = mirrorFramedAry[1][k];
            mirrorFramedAry[numRows + 1][k] = mirrorFramedAry[numRows][k];
        }
        fillTempAry();
    }//mirrorFramed

    void fillTempAry() {
        //places median of each pixel neighborhood to tempAry[i][j]
        //and prints tempAry
        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                tempAry[i][j] = loadNeighbors(i, j);
            }//for j
        }//for i
    }//fillTempArray

    void Median3X3(ofstream &out) {
        out << numRows << " " << numCols << " " << newMin << " " << newMax << "\n";
        for (int i = 1; i < numRows + 1; ++i) {
            for (int j = 1; j < numCols + 1; ++j) {
                out << tempAry[i][j] << " ";
            }//for j
            out << "\n";
        }//for i
    }//printOutputImage

    int loadNeighbors(int row, int column) {
        int count = 0, candidate = 0;
        //adds values to neighborAry
        for (int i = row - 1; i <= row + 1; ++i) {
            for (int j = column - 1; j <= column + 1; ++j) {
                neighborAry[count++] = mirrorFramedAry[i][j];
            }//for j
        }//for i
        candidate = SelectionSort(neighborAry);
        //keeps track of newMin,newMax
        if (candidate < newMin) {
            newMin = candidate;
        } else if (candidate > newMax) {
            newMax = candidate;
        }
        return candidate;
    }//loadNeighbors

    int SelectionSort(int *&nAry) {
        int min = 0, temp = 0;
        //i from 0 to n-1
        for (int i = 0; i < 8; ++i) {
            min = i;
            //j from 0 to n
            for (int j = i + 1; j < 9; ++j) {
                if (nAry[j] < nAry[min]) {
                    min = j;
                }
            }//for j
            //swaps nAry[i] if new min found
            if (min != i) {
                temp = nAry[i];
                nAry[i] = nAry[min];
                nAry[min] = temp;
            }//if
            //stops sorting at fifth smallest element
            if (i == 4) {
                return nAry[i];
            }//if
        }//for i
    }//Selection
};


int main(int argc, char *argv[]) {
    if (!argv[1]) {
        cout << "Please provide an input and output file." << "\n";
        exit(1);
    }
    ifstream in(argv[1]);
    ofstream out(argv[2]);

    MedianFilter filter1(in);
    filter1.loadimage(in);
    filter1.Median3X3(out);

    in.close();
    out.close();
    return 0;
};
//Angelo Zamudio CS381 Fall 16'
