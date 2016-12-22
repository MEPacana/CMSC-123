//i made this on my own
#include <iostream>
#include <stdio.h>
#include <stack>
#include <queue>
#include <fstream>
#include <list>
#include <fstream>
#include <typeinfo>
using namespace std;

class squares{
public:
    char n;
    int x,y;
    bool visited;
    squares(){n=x=y=0;visited=false;}
    squares(char n){
        visited = false;
        this->n = n;
        x = y = 0;
    }
    squares(char n,int x, int y){
        this->n = n;
        this->x = x;
        this->y = y;
        visited= false;
    }
    friend ostream& operator<<(ostream&,squares);
};

ostream& operator<<(ostream& out,squares x){
    out<<x.n;
    return out;
}

class maze{/////////////////////////////////// M A Z E //////////////////////////////////////////
public:
    squares **themaze;
    int rows,coloumns;
    squares startSquare;
    squares endSquare;
    maze();
    maze(int, int);
    maze(maze*);
    maze(list<char>,int,int);
    ~maze();
    void tostring();
};
maze::~maze(){
    delete[] themaze;
}

maze::maze(int coloumns, int rows){
    this->rows = rows;
    this->coloumns = coloumns;
    themaze = new squares*[rows];
    for(int i=0; i<rows; i++){
        themaze[i] = new squares[coloumns];
        for(int j = 0; j < coloumns;j++){
            themaze[i][j].x = j;
            themaze[i][j].y = i;
        }
    }
}
maze::maze(maze *m){
    this->rows = m->rows;
    this->coloumns = m->coloumns;
    this->themaze = m->themaze;
    this->startSquare= m->startSquare;
    this->endSquare = m->endSquare;
}
void maze::tostring(){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < coloumns ; j++){
            cout<<*(themaze)+i+j;
        }
        cout<<"\n";
    }
}//////////////////////////////////////////////////////// M A Z E ////////////////////////////////////////////////////

template <class T>//////////////////////////////////////////A G E N D A//////////////////////////////////////////
class agenda{
private:
    T *adt;
    int type;
public:
    agenda();
    ~agenda(){delete adt;}
    void add(squares);
    bool remove();
    bool isempty();
    int getsize();
    squares peek();
};


template <class T>
 squares agenda<T>::peek(){
   if(adt->size() == 0){
        cout<<"sa peek";
        throw 69;
   }
   else{
     if(type == 1){
        return ((stack<squares>*)adt)->top();
    }
    else{
        return ((queue<squares>*)adt)->front();
    }
   }
}

template <class T>
int agenda<T>::getsize(){
   return adt->size();
}

template <class T>
agenda<T>::agenda(){
    adt = new T();
    string t1 = typeid(*adt).name();
    string t2 = typeid(stack<squares>).name();
    string t3 = typeid(queue<squares>).name();
    if(t1.compare(t2)==0){
        type = 1;
    }
    else if(t1.compare(t3)==0){
        type = 2;
    }
}

template <class T>
bool agenda<T>::isempty(){
    if(adt->size() == 0){
        return true;
    }
    return false;
}

template <class T>
bool agenda<T>::remove(){
    if(isempty()){
        return false;
    }
    if(type == 1){
        ((stack<squares>*)adt)->pop();
    }
    else if(type == 2){
        ((queue<squares>*)adt)->pop();
    }
    return true;
}

template <class T>
void agenda<T>::add(squares x){
    if(type==1){
        ((stack<squares>*)adt)->push(x);
    }
    else{
        ((queue<squares>*)adt)->push(x);
    }
}
template <class T>
class mazesolver{///////////////////////////////////////M A Z E S O L V E R///////////////////////////////////////
private:
    agenda<T> *a;
    agenda< stack<squares> > *moves;
    maze *m;
public:
    mazesolver(maze*);
    ~mazesolver();
    maze solve();
    void writesolution();
};
template <class T>
void mazesolver<T>::writesolution(){
    ofstream file;
    file.open("test.out",ios_base::app);
    for(int i = 0 ;i < m->rows;  i++){//getting of input
        for( int j = 0 ; j< m->coloumns; j++){
            file<<m->themaze[i][j].n;
        }
        file<<endl;
    }
    file<<endl;
    file.close();
}
template <class T>
maze mazesolver<T>::solve(){
    moves->add(m->startSquare);
    bool backtracking = false;
    while(m->startSquare.x != m->endSquare.x || m->startSquare.y != m->endSquare.y){
    if(m->startSquare.x > 0 && !m->themaze[m->startSquare.y][m->startSquare.x-1].visited &&(m->themaze[m->startSquare.y][m->startSquare.x-1].n == '.' || m->themaze[m->startSquare.y][m->startSquare.x-1].n == '*')){
            squares *temp= new squares(m->themaze[m->startSquare.y][m->startSquare.x-1].n,m->startSquare.x-1,m->startSquare.y);
            a->add(*temp);
        }
        if(m->startSquare.y > 0&& !m->themaze[m->startSquare.y-1][m->startSquare.x].visited &&(m->themaze[m->startSquare.y-1][m->startSquare.x].n == '.' ||  m->themaze[m->startSquare.y-1][m->startSquare.x].n == '*')){
            squares *temp= new squares(m->themaze[m->startSquare.y-1][m->startSquare.x].n,m->startSquare.x,m->startSquare.y-1);
            a->add(*temp);
        }
        if(m->startSquare.x > 0&& !m->themaze[m->startSquare.y][m->startSquare.x+1].visited &&(m->themaze[m->startSquare.y][m->startSquare.x+1].n == '.' ||  m->themaze[m->startSquare.y][m->startSquare.x+1].n == '*')){
            squares *temp= new squares(m->themaze[m->startSquare.y][m->startSquare.x+1].n,m->startSquare.x+1,m->startSquare.y);
            a->add(*temp);
        }
        if(m->startSquare.y > 0 && !m->themaze[m->startSquare.y+1][m->startSquare.x].visited &&(m->themaze[m->startSquare.y+1][m->startSquare.x].n == '.' ||  m->themaze[m->startSquare.y+1][m->startSquare.x].n== '*')){
            squares *temp= new squares(m->themaze[m->startSquare.y+1][m->startSquare.x].n,m->startSquare.x,m->startSquare.y+1);
            a->add(*temp);
        }
        if(a->isempty()){
            if(moves->isempty()){
                writesolution();
                return *m;
            }
            else{
                squares temp = moves->peek();
                m->themaze[temp.y][temp.x].visited = true;//check if empty
                if(m->themaze[temp.y][temp.x].n != 'o'){
                    m->themaze[temp.y][temp.x].n = '.';
                }
                moves->remove();
                if(moves->isempty()){
                    writesolution();
                    return *m;
                }
                a->add(moves->peek());
            }
        }
        else{
           moves->add(a->peek());
            squares temp = a->peek();
            if( m->themaze[temp.y][temp.x].n != 'o' && m->themaze[temp.y][temp.x].n !='*'){
               m->themaze[temp.y][temp.x].n = 'x';
            }
        }
        squares temp = a->peek();
        m->startSquare.x = temp.x;
        m->startSquare.y = temp.y;
        m->startSquare.n =   temp.n;
        while(!(a->isempty())){
            a->remove();
        }
        for(int i = 0 ;i < m->rows;  i++){//getting of input
            for( int j = 0 ; j< m->coloumns; j++){
                cout<<m->themaze[i][j].n;
            }
            cout<<endl;
        }
        cout<<endl;
    }
    writesolution();
    return *m;
}

template <class T>
mazesolver<T>::mazesolver(maze *thismaze){
    a= new agenda<T>;
    m = thismaze;
    moves = new agenda< stack<squares> >();
}
//////////////////////////////////////////////////////////M A Z E S O L V E R//////////////////////////////////
//int main(){
//    agenda<stack<square> > a; //how to know what type of agenda is a?
//    agenda<queue<square> > b; //how to know what type of agenda is b?
//
//    return 0;
//}/////////////////////////////////////////////////////////////A G E N D A///////////////////////////////////////

int main (){
    ofstream file2("test.out");
    ifstream file("maze.in");
    if(file.is_open()){
		int cases;
		file>>cases;
		while(cases>0){
            int width, height;
            file>>height;
            file>>width;
            maze *maze1 = new maze(width,height);//making an empty maze
            maze *maze2 = new maze(width,height);
            char x;
            for(int i = 0 ;i < height;  i++){//getting of input
                for( int j = 0 ; j< width; j++){
                    file>>x;
                    maze1->themaze[i][j].n = maze2->themaze[i][j].n = x;
                    maze1->themaze[i][j].x = maze2->themaze[i][j].x = j;
                    maze1->themaze[i][j].y = maze2->themaze[i][j].y = i;
                    if(maze1->themaze[i][j].n == 'o'){
                        maze1->startSquare = maze2->startSquare = maze1->themaze[i][j];
                    }
                    else if(maze1->themaze[i][j].n == '*'){
                        maze1->endSquare = maze2->endSquare = maze1->themaze[i][j];
                    }
                    maze1->themaze[i][j].x = maze2->themaze[i][j].x = j;
                    maze1->themaze[i][j].y = maze2->themaze[i][j].x = i;
                }
                cout<<endl;
            }
            cout<<endl;
            cout<<"QUEUE"<<endl;
            mazesolver<queue<squares> > *ms= new mazesolver<queue<squares> >(maze1);
            maze final1= ms->solve();
            cout<<"STACK"<<endl;
            mazesolver<stack<squares> > *ms2= new mazesolver<stack<squares> >(maze2);
            maze final2= ms2->solve();
			cases--;
		}
		file.close();
	}
	return 0;
}
