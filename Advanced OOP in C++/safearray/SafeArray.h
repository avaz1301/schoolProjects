//
//
#include <iostream>

template<class T> // forward declaration
class SA;

template<class T> //forward declaration
std::ostream &operator<<(std::ostream &os, SA<T> s);

#ifndef  SA___REALLY_____LONG
#define SA___REALLY_____LONG

template<class T>
class SA {
private:
    int low, high;
    T *p;
public:
    // default constructor
    // allows for writing things like SA a;
    SA();

    // 2 parameter constructor lets us write
    // SA x(10,20);
    SA(int l, int h);

    // single parameter constructor lets us
    // create a SA almost like a "standard" one by writing // SA x(10); and getting an array x indexed from 0 to 9
    SA(int i);

    // copy constructor for pass by value and
    // initialization
    SA(const SA &s);

    // destructor
    ~SA();

    //overloaded [] lets us write
    // SA x(10,20); x[15]= 100;
    T& operator[](int i);

    // overloaded assignment lets us assign
    // one SA to another
    SA& operator=(const SA s);

    // overloads << so we can directly print SAs
    //template <class T>
    friend std::ostream &operator<<<T>(std::ostream &os, SA<T> s);
};

#endif // ! SA___REALLY_____LONG

