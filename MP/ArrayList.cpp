/*
 *Solution by Michael Pacana (MEPacana)
 */

class array{
private:
	int items[MAX];
	int size;
public:
	array();
	array(int);
	int getSize();
	void resetSize();
	int at(int);
	bool insert(int,int);
	bool remove(int);
    	int operator[](int);
};

array::array(){
	size = 0;
}

array::array(int n){
	size = 0;
	for(int i = 0; i < MAX; i++){
		items[i] = n;
        size++;
    }
}

bool array::insert(int n, int i){
    if(i < 0 || i > size || size == MAX){
        cout<<" false";
        return false;
    }
    else{
        if(i >= size){
            items[i]=n;
            size++;
        }
        else{
            for(int j = size-1 ; j > i ; j--){
                items[j+1]=items[j];
            }
            items[i]=n;
            size++;
        }
    }
    return true;
}

void array::resetSize(){
	size = 0;
}

int array::operator[](int i){
	return items[i];
}

bool array::remove(int i){
    if(i < 0 || i >= size|| size == 0){
        return false;
    }
    else{
        if(i == size-1){
            size--;
        }
        else{
            for(int j = i; j < size ; j++){
                items[j]=items[j+1];
            }
            size-=1;
        }
    }
    return true;
}

int array::getSize(){
	return size;
}

int array::at(int i){
	return items[i];
}

void purge(array*);

void display(array);

void checker(array);

int main() {
    int tcase,i,x,j;
    array arr;
    cin>>tcase;
    for(i = 0 ; i < tcase ; i++){
        for( j = 0 ; j < 10 ; j++){
            cin>>x;
            arr.insert(x,j);
        }
        purge(&arr);
        checker(arr);
        display(arr);
        arr.resetSize();
    }
    return 0;
}
void checker(array arr){
    int j, count = 1;
    if(arr.getSize() == 1){
        cout<<"NO"<<endl;
        return;
    }
    for(j = 0 ; j < arr.getSize() - 1 ; j++){
        if(arr[j] == arr[j+1]){
            count++;
        }
        else if(arr[j] > arr[j+1]){
            cout<<"NO"<<endl;
            return;
        }
    }
    if(count == arr.getSize()){
        cout<<"NO"<<endl;
        return;
    }
    cout<<"YES"<<endl;
}

void display(array arr){
    int j;
    for(j = 0; j < arr.getSize() ; j++){
        cout<<arr[j]<<" ";
    }
    cout<<endl;
}

void purge(array *arr){
   int i,j;
   for(i = 0 ; i < arr->getSize() ; i++){
     for(j = i + 1 ; j < arr->getSize() ; j++){
         if((*arr)[i]==(*arr)[j]){
           arr->remove(j);
            j--;
         }
     }
   }
}
