#include <iostream>
#include<fstream>

using namespace std;

class Threshold {
private:
    int **thr_Ary;
    int numRows, numCols, minVal, maxVal, thr_Val;
public:
    Threshold(ifstream &in, int thr) {
        thr_Val = thr;
        int temp = 0;
        in >> numRows >> numCols >> minVal >> maxVal;
        thr_Ary = new int *[numRows];
        for (int i = 0; i < numRows; ++i) {
            thr_Ary[i] = new int[numCols];
        }
        if (in) {
            for (int i = 0; i < numRows; ++i) {
                for (int j = 0; j < numCols; ++j) {
                    in >> temp;
                    thr_Ary[i][j] = temp;
                }//for j
            }//for i
        }//if
    };

    ~Threshold() {
        delete thr_Ary;
    };

    void computeThreshold(ofstream &out) {
        out << numRows << " " << numCols<< " " << minVal<< " " << maxVal << "\n";
        int temp = 0;
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                if (thr_Ary[i][j] < thr_Val) {
                    out << "0 ";
                } else {
                    out << "1 ";
                }//else
            }//for j
            out << "\n";
        }//for i
    }//computeThreshold
};

int main(int argc, char *argv[]) {
    if (!argv[1]) {
        cout << "Please provide an input and output file." << "\n";
        exit(1);
    }
    string out_file;
    int thr_value = 0;
    cout << "Please Enter a Threshold Value(between 1-63): ";
    cin >> thr_value;
    out_file = "thr_" + to_string(thr_value) + ".txt";

    ifstream in(argv[1]);
    ofstream out(out_file);

    Threshold h1(in, thr_value);
    h1.computeThreshold(out);

    in.close();
    out.close();
    return 0;
};

//Angelo Zamudio CS381 Fall 16'