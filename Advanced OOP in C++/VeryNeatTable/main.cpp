//Angelo Zamudio CS381 Summer 16'


#include <iostream>
#include "VNT.cpp"
using namespace std;

int main(int argc, char * argv[]) {
    cout<<"NOTE: # symbol represents INT_MAX.....\n\n";
    VNT<int> a(4,4);
    cout<<"VNT A(empty): \n";
    a.printMatrix();

    int q[16]= {17,12,1,99,81,-2,100, 59,0, 66, 210 ,-55, -1, 3, 5, 35};
    a.sort( q, (sizeof(q)/sizeof(*q)) );

    cout<<"VNT A after sort() of q[15]: \n";
    a.printMatrix();

    cout<<"Get value in a[2][2] with opertator[]: "<<a[2][2]<<"\n\n";

    cout<<"Calling find() on VNT A: \n";
    a.find(-55);
    a.find(35);
    a.find(210);
    a.find(1);
    a.find(59);
    a.find(13);
    cout<<"\n";

    VNT<int> b(3,3);
    cout<<"VNT B after 3 add()'s: \n";
    b.add(84);
    b.add(16);
    b.add(-3);
    b.printMatrix();

    VNT<int> c(3,3);

    cout<<"VNT C after sort() of z[9]: \n";
    int z[9]= {59, 0, 66, 210 ,-55, -1, 3, 5, 35};
    c.sort( z, (sizeof(z)/sizeof(*z)) );
    c.printMatrix();

    cout<<"getMIN on VNT C: "<<c.getMin()<<"\n";
    c.printMatrix();
    cout<<"\n";

    cout<<"getMin again on VNT C: "<<c.getMin()<<"\n";
    c.printMatrix();

    return 0;
}