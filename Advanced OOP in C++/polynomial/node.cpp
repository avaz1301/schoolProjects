//#include <iostream>
//using namespace std;
//
//class node{
//private:
//    int coeff, pow;
//    node * next;
//public:
//    node(int c, int p, node* n){
//        coeff=c;
//        pow=p;
//        next=n;
//    }
//
//    node(int c, int p){
//        coeff=c;
//        pow=p;
//        next=NULL;
//    }
//
//    node(){
//        coeff=0;
//        pow=0;
//        next=NULL;
//    }
//
//    ~node() {
//        //delete next;
//    }
//
//    int getCoeff(){ return coeff; }
//
//    int getPow(){ return pow; }
//
//    node * getNext(){ return next; }
//
//    void setNext(node * next_n){ next=next_n; }
//
//    void setCoeff(int c){ coeff=c; }
//
//    void setPow(int p){ pow=p; }
//
//    void printNode(){
//        if(NULL){
//            cout<<"node is null"<<endl;
//            return;
//        }
//        cout<<getCoeff()<<"^"<<getPow()<<endl;
//    }
//};
//
//void print_poly(node* x){
//    if(x==NULL){
//        cout<<"List is Empty."<<endl;
//        return;
//    }
//    while(x){
//        if(x->getCoeff()!=0){
//            cout<<x->getCoeff()<<"x^";
//            cout<<x->getPow();
//            if(x->getNext()!=NULL && x->getNext()->getCoeff()!=0){
//                cout<<" + ";
//            }
//            x=x->getNext();
//        }//if
//        else{
//            x=x->getNext();
//        }//else
//    }//while
//    cout<<endl;
//};
//
//void print_poly_recur(node* x){
//    if(x==NULL){ return;}
//    cout<<x->getCoeff()<<"x^";
//    cout<<x->getPow();
//    if(x->getNext()!=NULL){
//        cout<<" + ";
//    }
//    print_poly_recur(x->getNext());
//    cout<<endl;
//}
//
////node<int>* init_poly_list(int s){
////    node<int> * head=new node<int>();
////    int temp_size=s;
////    if(temp_size<=0){
////        return head->getNext();
////    }
////    node<int>* first, *p, *q;
////    first = p = head->getNext();
////    for(int i=2; i<=temp_size;i++){
////        q=new node<int>();
////        p->setNext(q);
////        p=q;
////    }
////    return first;
////}first
//
//void add_node_to_end(node* & front, node* incoming){
//    if(front==NULL){
//        front=incoming;
//        return;
//    }
//    node* current=front;
//    while(current->getNext()!=NULL){
//        current=current->getNext();
//    }
//    current->setNext(incoming);
//};
//
//node* add_poly(node*& a, node*& b){
//
//    if(a==NULL){
//        return b;
//    }else if(b==NULL){
//        return a;
//    }else{
//        node* temp;
//        node* currenta = a;
//        node* currentb = b;
//
//        while(currenta && currentb){
//            if(currenta->getPow() > currentb->getPow()){
//                add_node_to_end(temp,new node(currenta->getCoeff(),currenta->getPow()));
//                currenta = currenta->getNext();
//            }else if(currenta->getPow() < currentb->getPow()){
//                add_node_to_end(temp,new node(currentb->getCoeff(),currentb->getPow()));
//                currentb = currentb->getNext();
//            }else{
//                int new_coeff = currenta->getCoeff()+currentb->getCoeff();
//                add_node_to_end(temp, new node(new_coeff,currenta->getPow()));
//                currenta = currenta->getNext();
//                currentb = currentb->getNext();
//            }//else
//            print_poly(temp);
//        }//while
//
//        if(currenta == nullptr){
//            cout<<"currenta is null";
//            while(currentb){
//                add_node_to_end(temp, new node(currentb->getCoeff(), currentb->getPow()));
//                currentb=currentb->getNext();
//            }//while
//        }else if(currentb == nullptr){
//            cout<<"currentb is null";
//            while(currenta){
//                add_node_to_end(temp, new node(currenta->getCoeff(), currenta->getPow()));
//                currenta=currenta->getNext();
//            }//while
//        }//else if
////      print_poly(temp);
//        return temp;
//    }//else
//
//}//add_poly
//
//node* insert(node* z, node* in){
//    int in_coe=in->getCoeff();
//    int in_pow=in->getPow();
//    if(z==NULL){
//        z=new node(in_coe,in_pow);
//        return z;
//    }else{
//        node* current=z;
//        node* previous=z;
//        while(current) {
//            if(in_pow > current->getPow() && current==previous){
//                in->setNext(current);
//                z=in;
//                break;
//            } else if(in_pow < previous->getPow() && in_pow > current->getPow()) {
//                previous->setNext(in);
//                in->setNext(current);
//                break;
//            }else if(in_pow == current->getPow()){
//                current->setCoeff(in_coe + current->getCoeff());
//                break;
//            }else{
//                previous=current;
//                current=current->getNext();
//            }//else
//        }//while
//        if(current==NULL){
//            previous->setNext(in);
//        }//if
//        return z;
//    }//else
//}//insert
//
//node* consolidate_poly(node* a){
//    node* temp_list = NULL;
//    node* current   = a;
//
//    while(current){
//        node* temp_node=new node(current->getCoeff(),current->getPow());
//        temp_list=insert(temp_list, temp_node);
//        current=current->getNext();
//    }//while
//
//    return temp_list;
//}//consolidate