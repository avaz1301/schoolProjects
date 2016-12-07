//Angelo Zamudio CS381 Summer 16'

#include <iostream>
#include <fstream>
#include <sstream>
#include "Polynomial.h"

using namespace std;

Polynomial::Polynomial(int c, int p, Polynomial *n) {
    coeff = c;
    pow = p;
    next_node = n;
}

Polynomial::Polynomial(int c, int p) {
    coeff = c;
    pow = p;
    next_node = nullptr;
}

Polynomial::Polynomial() {
    coeff = 0;
    pow = 0;
    next_node = nullptr;
}

Polynomial::~Polynomial() {
    delete next_node;
}

int Polynomial::getCoeff() { return coeff; }

int Polynomial::getPow() { return pow; }

Polynomial *Polynomial::getNext() {
    return next_node;
}

void Polynomial::setNext(Polynomial *next_n) { next_node = next_n; }

void Polynomial::setCoeff(int c) { coeff = c; }

void Polynomial::setPow(int p) { pow = p; }

void Polynomial::printPoly() {
    cout << getCoeff() << "^" << getPow() << endl;
}//printNode

//Traverses polynomial printing out reach term in a readable format.
void print_poly(Polynomial* x, ofstream& out){
    Polynomial* first = x;
    if(x==NULL){
        cout<<"List is Empty."<<endl;
        out<<"List is Empty.\n";
        return;
    }
    while(x){
        if(x->getCoeff() != 0){
            ///////////////////////////////////////////////
            if(x != first && x->getCoeff()<0){
                cout<<(-1 * x->getCoeff())<<"x^";
                cout<<x->getPow();

                out<<(-1 * x->getCoeff())<<"x^";
                out<<x->getPow();
            }else{
                cout<<x->getCoeff()<<"x^";
                cout<<x->getPow();

                out<<x->getCoeff()<<"x^";
                out<<x->getPow();
            }
            ///////////////////////////////////////////////
            if(x->getNext() != NULL && x->getNext()->getCoeff()!=0){
                if(x->getNext()->getCoeff()<0){
                    cout<<" - ";
                    out<<" - ";
                }else{
                    cout<<" + ";
                    out<<" + ";
                }
            }
            x=x->getNext();
        }//if
        else{
            x=x->getNext();
        }//else
    }//while
    cout<<endl;
    out<<"\n";
}//print_poly;

//Add specified node to the end of desired Linked List
void add_node_to_end(Polynomial* & front, Polynomial* incoming){
    if(front==NULL){
        front=incoming;
        return;
    }
    Polynomial* current=front;
    while(current->getNext()!=NULL){
        current=current->getNext();
    }
    current->setNext(incoming);
}//add_node_to_end;

//Used in consolidating polynomial
Polynomial* insert(Polynomial* z, Polynomial* in){
    int in_coe=in->getCoeff();
    int in_pow=in->getPow();
    //if polynomial is initially empty
    if(z==NULL){
        z=new Polynomial(in_coe,in_pow);
        return z;
    }else{
        //if polynomial is not empty
        //and node is to be inserted in the middle of polynomial
        Polynomial* current=z;
        Polynomial* previous=z;
        while(current) {
            //add to front of polynomial
            if(in_pow > current->getPow() && current==previous){
                in->setNext(current);
                z=in;
                break;
            }//add between current node and previous node
            else if(in_pow < previous->getPow() && in_pow > current->getPow()) {
                previous->setNext(in);
                in->setNext(current);
                break;
            }//if incoming node is of equal power add to coefficient of current node
            else if(in_pow == current->getPow()){
                current->setCoeff(in_coe + current->getCoeff());
                break;
            }else{
                previous=current;
                current=current->getNext();
            }//else
        }//while
        //if at the end of the polynomial, add node to end of poly.
        if(current==NULL){
            previous->setNext(in);
        }//if
        return z;
    }//else
}//insert

Polynomial* consolidate_poly(Polynomial* a){
    Polynomial* temp_list = NULL;
    Polynomial* current   = a;

    while(current){
        Polynomial* temp_node=new Polynomial(current->getCoeff(),current->getPow());
        temp_list=insert(temp_list, temp_node);
        current=current->getNext();
    }//while

    return temp_list;
}//consolidate

Polynomial* add_poly(Polynomial*& a, Polynomial*& b){
    if(a==NULL){
        return b;
    }else if(b==NULL){
        return a;
    }else{
        Polynomial* temp_sum=NULL;
        Polynomial* currenta = a;
        Polynomial* currentb = b;

        while(currenta && currentb){
            if(currenta->getPow() > currentb->getPow()){
                add_node_to_end(temp_sum,new Polynomial(currenta->getCoeff(),currenta->getPow()));
                currenta = currenta->getNext();

            }else if(currenta->getPow() < currentb->getPow()){
                add_node_to_end(temp_sum,new Polynomial(currentb->getCoeff(),currentb->getPow()));
                currentb = currentb->getNext();

            }else{
                int new_coeff = (currenta->getCoeff()+currentb->getCoeff());
                add_node_to_end(temp_sum, new Polynomial(new_coeff,currenta->getPow()));
                currenta = currenta->getNext();
                currentb = currentb->getNext();
            }//else
        }//while

        if(currenta == nullptr){
//            cout<<"currenta is null\n";
            while(currentb){
                add_node_to_end(temp_sum, new Polynomial(currentb->getCoeff(), currentb->getPow()));
                currentb=currentb->getNext();
            }//while
        }else if(currentb == nullptr){
//            cout<<"currentb is null\n";
            while(currenta){
                add_node_to_end(temp_sum, new Polynomial(currenta->getCoeff(), currenta->getPow()));
                currenta=currenta->getNext();
            }//while
        }//else if
//        print_poly(temp_sum);
        return temp_sum;
    }//else

}//add_poly

Polynomial* sub_poly(Polynomial*& a, Polynomial*& b){
    if(a==NULL){
        return b;
    }else if(b==NULL){
        return a;
    }else{
        Polynomial* temp_diff=NULL;
        Polynomial* currenta = a;
        Polynomial* currentb = b;

        while(currenta && currentb){
            if(currenta->getPow() > currentb->getPow()){
                add_node_to_end(temp_diff,new Polynomial(currenta->getCoeff(),currenta->getPow()));
                currenta = currenta->getNext();

            }else if(currenta->getPow() < currentb->getPow()){
                add_node_to_end(temp_diff,new Polynomial(currentb->getCoeff(),currentb->getPow()));
                currentb = currentb->getNext();

            }else{
                int new_coeff = (currenta->getCoeff()-currentb->getCoeff());
                add_node_to_end(temp_diff, new Polynomial(new_coeff,currenta->getPow()));
                currenta = currenta->getNext();
                currentb = currentb->getNext();
            }//else
        }//while

        if(currenta == nullptr){
//            cout<<"currenta is null\n";
            while(currentb){
                add_node_to_end(temp_diff, new Polynomial(currentb->getCoeff(), currentb->getPow()));
                currentb=currentb->getNext();
            }//while
        }else if(currentb == nullptr){
//            cout<<"currentb is null\n";
            while(currenta){
                add_node_to_end(temp_diff, new Polynomial(currenta->getCoeff(), currenta->getPow()));
                currenta=currenta->getNext();
            }//while
        }//else if
//        print_poly(temp_diff);
        return temp_diff;
    }//else
}//sub poly

Polynomial* mul_poly(Polynomial*& a, Polynomial*& b){
    Polynomial* temp_prod = NULL;
    Polynomial* term_a    = a;
    Polynomial* term_b    = b;

    while(term_a){
        if(term_b){
            int new_coeff = term_a->getCoeff()*term_b->getCoeff() ;
            int new_pow   = (term_a->getPow()+term_b->getPow());
            add_node_to_end(temp_prod, new Polynomial(new_coeff, new_pow));
            term_b=term_b->getNext();
        }else{
            term_a = term_a->getNext();
            term_b = b;
        }//else
    }//while

    Polynomial* ret_prod = consolidate_poly(temp_prod);

    //print_poly(ret_prod);
    return ret_prod;

}//mul poly


int main(int argc, char *argv[]) {
    ifstream in(argv[1]);
    ofstream out(argv[2]);
    Polynomial *polys[7];
    string line;
    int count = 0, t_c = 0, t_p = 0;
    if (in) {
        while (getline(in, line, ',')) {
            stringstream ss(line);
            while (ss >> t_c >> t_p) {
                add_node_to_end(polys[count], new Polynomial(t_c, t_p));
            }
            count = count + 1;
        }
    }//open
    in.close();
    polys[2] = consolidate_poly(polys[0]);
    polys[3] = consolidate_poly(polys[1]);
    polys[4] = add_poly(polys[2], polys[3]);
    polys[5] = sub_poly(polys[2], polys[3]);
    polys[6] = mul_poly(polys[2], polys[3]);

    out << "Polynomial A -> ";
    print_poly(polys[0], out);
    out << "\n";
    out << "Polynomial B -> ";
    print_poly(polys[1], out);
    out << "\n";
    out << "Polynomial A_1 (Polynomial A consolidated) -> ";
    print_poly(polys[2], out);
    out << "\n";
    out << "Polynomial B_1 (Polynomial B consolidated) -> ";
    print_poly(polys[3], out);
    out << "\n";
    out << "Polynomial SUM (A + B) -> ";
    print_poly(polys[4], out);
    out << "\n";
    out << "Polynomial DIFF (A - B) -> ";
    print_poly(polys[5], out);
    out << "\n";
    out << "Polynomial PROD (A * B) -> ";
    print_poly(polys[6], out);
    out << "\n";

    out.close();
    return 0;
}//main