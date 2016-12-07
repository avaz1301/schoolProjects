//Angelo Zamudio CS381 Summer 16'
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
using namespace std;

class PolynomialMap {
private:
    std::map<int, int> poly;
public:
    PolynomialMap() { }

    ~PolynomialMap() { }

    bool alreadyIndexed(int coeff, int pow) {
        map<int, int>::iterator i = poly.find(pow);
        if (i != poly.end()) {
            i->second += coeff;
            return true;
        }//if
        return false;
    }//alreadyIndexed

    void addTerm(int coeff, int pow) {
        if (alreadyIndexed(coeff, pow)) {
            return;
        } else {
            poly[pow] = {coeff};
            return;
        }//else
    }//addTerm

    void printPoly() {
        map<int, int>::reverse_iterator rit;
        for (rit = poly.rbegin(); rit != poly.rend(); ++rit) {
            if (rit->second != 0) {
                if (rit == poly.rbegin()) {
                    cout << rit->second << "^" << rit->first;
                } else if (rit->second < 0) {
                    cout << " - " << (rit->second * -1) << "^" << rit->first;
                } else {
                    cout << " + " << rit->second << "^" << rit->first;
                }//if
            }//if
        }//for
        cout << "\n";
    };//printPoly

    PolynomialMap &operator+(const PolynomialMap &rhs) {
        PolynomialMap *temp = new PolynomialMap();
        for (auto i: this->poly) {
            temp->addTerm(i.second, i.first);
        }
        for (auto k: rhs.poly) {
            temp->addTerm(k.second, k.first);
        }
        return *temp;
    }//op+

    PolynomialMap &operator-(const PolynomialMap &rhs) {
        PolynomialMap *temp = new PolynomialMap();
        for (auto i: this->poly) {
            temp->addTerm(i.second, i.first);
        }
        for (auto k: rhs.poly) {
            temp->addTerm((-1 * k.second), k.first);
        }
        return *temp;
    }//op-

    PolynomialMap &operator*(const PolynomialMap &rhs) {
        PolynomialMap *temp = new PolynomialMap();
        for (auto i: this->poly) {
            for (auto k: rhs.poly) {
                temp->addTerm((i.second * k.second), (i.first + k.first));
            }
        }
        return *temp;
    }//op*

    PolynomialMap &operator=(const PolynomialMap &rhs) {
        if (this == &rhs) {
            return *this;
        }
        map<int, int> temp;
        for (auto i: rhs.poly) {
            temp[i.first] = {i.second};
        }
        poly = temp;
        return *this;
    }//op=
};

int main(int argc, char *argv[]) {
    PolynomialMap polys[2], sum, diff, prod;
    ifstream in(argv[1]);
    string line;
    int count = 0, coefficient, power;
    if (in) {
        while (getline(in, line)) {
            stringstream ss(line);
            while (ss >> coefficient >> power) {
                cout<<coefficient<<","<< power<<"   ";
                polys[count].addTerm(coefficient,power);
            }//while
            cout<<"\n";
            count++;
        }//while
    }//open
    in.close();
    cout<<"POLYNOMIAL A: \n";
    polys[0].printPoly();
    cout<<"\n";
    cout<<"POLYNOMIAL B: \n";
    polys[1].printPoly();
    cout<<"\n";
    sum=polys[0]+polys[1];
    cout<<"POLYNOMIAL SUM (A+B): \n";
    sum.printPoly();
    cout<<"\n";
    cout<<"POLYNOMIAL DIFF (A-B): \n";
    diff=polys[0]-polys[1];
    diff.printPoly();
    cout<<"\n";
    cout<<"POLYNOMIAL PROD (A*B): \n";
    prod=polys[0]*polys[1];
    prod.printPoly();
    return 0;
}