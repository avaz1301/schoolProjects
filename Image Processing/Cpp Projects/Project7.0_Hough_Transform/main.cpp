#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

class ImageProcessing {
    friend class HoughTransform;

private:
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int **imgAry;
public:
    ImageProcessing(ifstream &in) {
        minVal = 100;
        maxVal = 0;
        in >> numRows >> numCols >> minVal >> maxVal;
        imgAry = new int *[numRows];
        for (int i = 0; i < numRows; ++i) {
            imgAry[i] = new int[numCols]();
        }
        loadImage(in);
    }

    ~ImageProcessing() {
        delete imgAry;
    }

    void loadImage(ifstream &in) {
        if (in) {
            int pixel = 0;
            for (int i = 0; i < numRows; ++i) {
                for (int j = 0; j < numCols; ++j) {
                    in >> pixel;
                    imgAry[i][j] = pixel;
                }
            }
        }
    }

    void prettyPrint() {
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                if (imgAry[i][j] != 0) {
                    cout << imgAry[i][j] << " ";
                } else {
                    cout << "  ";
                }
            }
            cout << "\n";
        }
    }
};

struct xyCoord {
    int x;
    int y;
};

class HoughTransform {
private:
    xyCoord point;
    int angleInDegree;
    double angleInRadians;
    double pi;
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int **houghAry;

public:
    HoughTransform(ImageProcessing &img, ofstream &out, ofstream &out1) {
        numRows = 180;
        numCols = 2 * (int) sqrt((img.numCols * img.numCols) + (img.numRows * img.numRows));
        minVal = 100;
        maxVal = 0;
        pi = 3.14159;
        houghAry = new int *[numRows];
        for (int i = 0; i < numRows; ++i) {
            houghAry[i] = new int[numCols]();
        }
        for (int i = 0; i < img.numRows; ++i) {
            for (int j = 0; j < img.numCols; ++j) {
                if (img.imgAry[i][j] > 0) {
                    point.x = i;
                    point.y = j;
                    angleInDegree = 0;
                    while (angleInDegree <= 179) {
                        angleInRadians = (angleInDegree / 180.0) * pi;
                        int col = (int) computeDistance(point, angleInRadians);
                        int offcol= (numCols/2)+col;
                        houghAry[angleInDegree][offcol]++;
                        maxVal = (houghAry[angleInDegree][offcol] > maxVal) ? houghAry[angleInDegree][offcol] : maxVal;
                        minVal = (houghAry[angleInDegree][offcol] < minVal) ? houghAry[angleInDegree][offcol] : minVal;
                        angleInDegree++;

                    }//while
                }//if
            }//for j
        }//for i
        determineHeader(out);
        prettyPrint(out1);
    }

    ~HoughTransform() {
        delete houghAry;
    }

    double computeDistance(xyCoord &pt, double angle) {
        double t = angle - atan(pt.y / pt.x) - (pi / 2.0);
        return sqrt((pt.x * pt.x) + (pt.y * pt.y)) * cos(t);
    }

    void determineHeader(ofstream &out) {
        out << numRows << " " << numCols << " " << minVal << " " << maxVal << "\n";
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                out << houghAry[i][j] << " ";
            }
            out << "\n";
        }
    }//determineHeader

    void prettyPrint(ofstream &out) {
        out << numRows << " " << numCols << " " << minVal << " " << maxVal << "\n";
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                if (houghAry[i][j] > 0) {
                    out << houghAry[i][j] << " ";
                } else {
                    out << "  ";
                }
            }
            out << "\n";
        }//for
    }//prettyPrint
};

int main(int argc, char *argv[]) {
    ifstream in(argv[1]);
    ofstream out(argv[2]);
    ofstream out1(argv[3]);
    ImageProcessing img(in);
    HoughTransform hT(img, out, out1);
    in.close();
    out.close();
    out1.close();
    return 0;
}

//Angelo Zamudio CS381 Fall 16'
