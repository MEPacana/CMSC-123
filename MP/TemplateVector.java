#include <iostream>
#define MAX 20
using namespace std;

template <class T>
class vector{
private:
	T *items;
	int size;
	int max;

	void expand();

public:
	vector();
	vector(const vector&);
	~vector();
	int getSize();
	void resetSize();
	T at(int);
	bool insert(T,int);
	bool remove(int);
	T operator[](int);
};

template <class T>
vector<T>::vector(const vector<T>& v){
	size = v.size;
	max = v.max;
	items = new T [max];
	copy(v.items,v.items+size,items);
}

template <class T>
vector<T>::vector(){
	items = new T[5];
	size = 0;
	max = 5;
}

template <class T>
vector<T>::~vector(){
	delete[] items;
}

template <class T>
ostream& operator<<(ostream& out,vector <T> arr){
    int j;
    
    for(j = 0 ; j < arr.getSize() ; j++){
        out<<arr[j]<<" ";
    }
    
    out<<endl;
    return out;
}

template <class T>
void vector<T>::expand(){
    T *cpy = new T[max];

    for(int i = 0; i < size; i++){
        cpy[i] = items[i];
    }

    max+=5;
    delete[]items;
    items = new T[max];
  
    for(int i = 0; i < size; i++){
        items[i] = cpy[i];
    }
    delete[]cpy;
}

template <class T>
bool vector<T>::insert(T n, int i){
    if(i < 0 || i > size){
        return false;
    }
    else{
        if(size == max){
            expand();
        }
        if(i==size){
            items[i]=n;
            size++;
        }
        else{
            for(int j = size ; j > i ; j--){
                items[j] = items[j-1];
            }
            items[i]=n;
            size++;
        }
    }
    return true;
}

template <class T>
void vector<T>::resetSize(){
	size = 0;
}

template <class T>
T vector<T>::operator[](int i){
	return items[i];
}

template <class T>
bool vector<T>::remove(int i){
    if(i<0 || i>=size|| size==0){
        return false;
    }
    else{
        if(i==size-1){
            size--;
        }
        else{
            for(int j=i;j<size;j++){
                items[j]=items[j+1];
            }
            size-=1;
        }
    }
    return true;
}

template <class T>
int vector<T>::getSize(){
	return size;
}

template <class T>
T vector<T>::at(int i){
	return items[i];
}

void purge(vector <int>&);
void checker(vector <string>);
void purge(vector <string>&);
void checker(vector <int>);

template <class T>
void display(vector <T>);

int main() {
    int tcase,i,x,j,type;
    string x2;
    cin>>tcase;
    for(i=0;i<tcase;i++){
        cin>>type;
        if(type==1){
            vector <int> arr;
            for(j=0;j<10;j++){
                cin>>x;
                arr.insert(x,j);
            }
            checker(arr);
            purge(arr);
            cout<<arr;
        }
        else{
            vector <string> arr;
            for(j=0;j<10;j++){
                cin>>x2;
                arr.insert(x2,j);
            }
            
            checker(arr);
            purge(arr);
            cout<<arr;
        }
    }
    return 0;
}

void checker(vector <int>arr){
    int j,count=1;
    if(arr.getSize()==1){
        cout<<"NO"<<endl;
        return;
    }
    for(j=0;j<arr.getSize()-1;j++){
        if(arr[j]==arr[j+1]){
            count++;
        }
        else if(arr[j]>arr[j+1]){
            cout<<"NO"<<endl;
            return;
        }
    }
    if(count==arr.getSize()){
        cout<<"NO"<<endl;
        return;
    }
    cout<<"YES"<<endl;
}

void checker(vector <string> arr){
    int j,count=1;
    if(arr.getSize()==1){
        cout<<"NO"<<endl;
        return;
    }
    for(j=0;j<arr.getSize()-1;j++){
        if(arr[j].compare(arr[j+1])==0){
            count++;
        }
        else if(arr[j].compare(arr[j+1])>0){
            cout<<"NO"<<endl;
            return;
        }
    }
    if(count==arr.getSize()){
        cout<<"NO"<<endl;
        return;
    }
    cout<<"YES"<<endl;
}

template <class T>
void display(vector <T> arr){
    int j;
    for(j=0;j<arr.getSize();j++){
        cout<<arr[j]<<" ";
    }
    cout<<endl;
}

void purge(vector <string> &arr){//************Check code**********
   int i,j;
   for(i=0;i<arr.getSize();i++){
     for(j=i+1;j<arr.getSize();j++){
         if(arr[i].compare(arr[j])==0){
           arr.remove(j);
            j--;
         }
     }
   }
}


void purge(vector <int> &arr){//************Check Code**********
   int i,j;
   for(i=0;i<arr.getSize();i++){
     for(j=i+1;j<arr.getSize();j++){
         if((arr)[i]==(arr)[j]){
           arr.remove(j);
            j--;
         }

     }

   }
}
