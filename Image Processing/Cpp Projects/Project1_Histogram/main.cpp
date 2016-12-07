#include <iostream>
#include<fstream>

using namespace std;

class Histogram {
private:
    int *histogram;
    int numRows, numCols, minVal, maxVal;
public:
    Histogram(ifstream& in) {
        int temp=0;
        if (in) {
            in >> numRows >> numCols >> minVal >> maxVal;
            histogram = new int[maxVal + 1]();
            while (in >> temp) {
                histogram[temp] += 1;
            }//while
        }//if
    };

    ~Histogram() {
        delete[] histogram;
    };

    void computeHistogram(ofstream& out) {
        cout << numRows << " " << numCols << " " << minVal << " " << maxVal << "\n";
        out << numRows << " " << numCols << " " << minVal << " " << maxVal << "\n";
        for (int i = 0; i < maxVal + 1; ++i) {
            cout << "(" << i << ") : " << histogram[i];
            out << "(" << i << ") : " << histogram[i];
            for (int j = 0; j < histogram[i]; ++j) {
                if (j < 80) {
                    cout << "+";
                    out << "+";
                }//if
            }//for j
            cout << "\n";
            out << "\n";
        }//for i
    }//computeHistogram
};

int main(int argc, char *argv[]) {
    if(!argv[1]){
        cout<<"Please provide an input and output file."<<"\n";
        exit(1);
    }
    ifstream in(argv[1]);
    ofstream out(argv[2]);

    Histogram h1(in);
    h1.computeHistogram(out);

    in.close();
    out.close();
    return 0;
};

//Angelo Zamudio CS381 Fall 16'