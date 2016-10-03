   for(int i = 0; n.insert(i, temp->elem); i++, temp = temp->next);
    return n;
}*/

template <class T>
bool list<T>::insert(int i, T n){
    node<T> *x = new node<T>(n);
    if(i<0 || i>size){
        return false;
    }
    else if(head == NULL){
        tail = head = x;
    }
    else if(i==size){
        tail->next = x;
        tail = x;
    } 
    else if(i == 0){
        x->next = head;
        head = x;
    }
    else {
        node<T> *temp = head;
            for(int j = 0; j < i-1; j++){
                temp = temp->next;
            }
            x->next = temp->next;
            temp->next = x;
    }
    size++;
    return true;
}

template <class T>
T list<T>::get(int n){
    node<T> *temp = head;
    for(int i = 0; i < n; i++, temp = temp->next);
    return temp->elem;
}
template <class T>
void display(list<T>);

int main(){
    list<int> List;
    int tst, pos, item;
    cin>>tst;
    while(tst>0){         
        cin>>pos;
       
        cin>>item;
          
        List.insert(pos, item);
        display(List);
        tst--;
    }
    return 0;
}

template <class T>
void display(list<T> l){
    for(int i = 0; i < l.size; i++){
        cout<<l.get(i)<<" ";
    }
    cout<<endl;
}
