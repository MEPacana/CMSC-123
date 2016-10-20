/*
 *Solution by Mike
 */
#include <iostream>
using namespace std;
template <class T>

class node{
public:
    T elem;
    node* next;
    node();
    node(T n){elem = n; next = NULL;}
};

template <class T>
class list{
public:
    int size;
    node<T> *top;
public:
    list();
    ~list();
    bool push(T);
    bool pop();
    T peek();
    void display();
};



int main (){
    list<int> l;
    int tstcsc = -1, oper = -1, item = -1;
    cin>>tstcsc;
    while(tstcsc){
        cin>>oper;
        if(oper == 1){
            cin>>item;
            l.push(item);
            l.display();
        } else if (oper == 2){
            l.pop();
            l.display();
        } else if (oper == 3){
            try {
                item = l.peek();
                cout<<item<<endl;
            } catch (int err){
                if(err = 69){
                    cout<<"stack is empty."<<endl;
                }
            }
        } else {
            l.display();
        }
        tstcsc--;
    }
    return 0;
}



template <class T>
list<T>::list(){
    size = 0;
    top = NULL;
}

template <class T>
list<T>::~list(){
    while(size > 0){
        pop();
    }
}

template <class T>
bool list<T>::push(T n){
    node<T> *x = new node<T>(n);

    if(size == 0){
        top = x;
    }
    else {
        x->next = top;
        top = x;
    }
    size++;
    return true;
}

template <class T>
bool list<T>::pop(){
    if(size==0){
        return false;
    }
    else{
        node<T> *del = top;
        top = del->next;
        del->next = NULL;
        delete del;
    }
    size--;
    return true;
}

template <class T>
T list<T>::peek(){
    if(size==0){
        throw 69;
    }
    else{
        return top->elem;
    }
}

template <class T>
void list<T>::display(){
    node<T> *n = top;
    int s = size;
    while(s){
        cout<<n->elem<<" ";
        n = n->next;
        s--;
    }
    cout<<endl;
}
