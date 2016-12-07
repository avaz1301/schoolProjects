//Angelo Zamudio CS381 Summer 16'

#ifndef polynomial_h
#define polynomial_h

class Polynomial {
    private:
        int coeff, pow;
        Polynomial * next_node;
    public:
        Polynomial(int, int, Polynomial *);

        Polynomial(int, int);

        Polynomial();

        ~Polynomial();

        int getCoeff();

        int getPow();

        Polynomial * getNext();

        void setNext(Polynomial *);

        void setCoeff(int);

        void setPow(int);

        void printPoly();
};

#endif