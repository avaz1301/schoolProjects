#include <iostream>
#include<fstream>

using namespace std;

void prettyPrint(ifstream &in, ofstream &out) {
    int numRows = 0, numCols = 0, minVal = 0, maxVal = 0, temp = 0;
    in >> numRows >> numCols >> minVal >> maxVal;
    if (in) {
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                in >> temp;
                if (temp > 0) {
                    out << temp << " ";
                } else {
                    out << "  ";
                }
            }//for j
            out << "\n";
        }//for i
    }//if
};

int main(int argc, char *argv[]) {
    if (!argv[1]) {
        cout << "Please provide an input and output file." << "\n";
        exit(1);
    }
    string out_file;
    out_file = argv[1];
    size_t lastindex = out_file.find_last_of(".");
    out_file = out_file.substr(0, lastindex);
    out_file = out_file + "_PP.txt";

    ifstream in(argv[1]);
    ofstream out(out_file);

    prettyPrint(in, out);

    in.close();
    out.close();
    return 0;
};


//Angelo Zamudio CS381 Fall 16'