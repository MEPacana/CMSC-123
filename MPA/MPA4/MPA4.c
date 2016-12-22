#include <iostream>
#include <fstream>
#include <list>
#include <string.h>
#include <ctime>
using namespace std;

class node{///////////////////////////////////////////////////////NODE////////////////////////////////////////////////////////////////
public:
    bool type; //true for directory, false for file
    string filename,data;//TODO add time and date
    tm *timedate;
    node *prnt;
    list<node*> children;
    node(){
        data = "";
        type = true;
        prnt = NULL;
    }
    node(string filename, tm *timedate, bool type){
        this->filename = filename;
        this->timedate = timedate;
        data = "";
        this->type = type;
        prnt = NULL;
    }
    string whereis(string filename){
        if(this->filename == filename){
            return "/"+filename;
        }
        else{
            if(!children.empty()){
                list <node*>::iterator iter;
                string directory;
                for(iter = children.begin(); iter!=children.end() ;iter++){
                    directory = (*iter)->whereis(filename);
                    if(directory.compare("")!= 0){
                        string backslash("/"+this->filename);
                        backslash.append(directory);
                        return backslash;
                    }
                }
            }
            return "";
        }
    }
    node* nodeof(string filename){
        if(this->filename == filename){
            node *temp = this;
            return temp;
        }
        else{
            if(!children.empty()){
                list <node*>::iterator iter;
                for(iter = children.begin(); iter!=children.end() ;iter++){
                    node *temp = (*iter)->nodeof(filename);
                    if(temp!= NULL){
                        return temp;
                    }
                }
            }
            return NULL;
        }
    }
};/////////////////////////////////////////////////NODE///////////////////////////////////////////////////////////////////////////////

class tree{//////////////////////////////////////TREE////////////////////////////////////////////////////////////////////////////////////////
public:
    node *root;
    node *current;
public:
    tree(){
        time_t now = time(0);
        tm *ltm = localtime(&now);
        node *n = new node("root",ltm,true);
        root = current = n;
    }
    bool insert(string filename,bool type){
        time_t now = time(0);
        tm *ltm = localtime(&now);
        if(!this->search(filename,type)){
            node *n= new node(filename,ltm,type);
            n->prnt = current;
            list <node*>::iterator iter;
            for(iter = current->children.begin(); iter!=current->children.end() ;iter++){
                if((*iter)->filename.compare(n->filename) > 0){
                    break;
                }
            }
            current->children.insert(iter,n);
        }else{
            cout<<"mkdir: "<<filename<<": "<<"Already exists"<<endl;
        }
    }
    bool insert(bool type, string filename,string data,tm *timedate,node* prnt,list<node*> children){
        node *n= new node(filename,timedate,type);
        n->type = type;
        n->filename = filename;
        n->data = data;
        n->timedate = timedate;
        n->prnt = prnt;
        n->children = children;
        list <node*>::iterator iter;
        for(iter = current->children.begin(); iter!=current->children.end() ;iter++){
            if((*iter)->filename.compare(n->filename) > 0){
                break;
            }
        }
        current->children.insert(iter,n);
    }
    void showchildren(){
        list <node*>::iterator iter;
        for(iter = current->children.begin(); iter!=current->children.end() ;iter++){
            cout<<(*iter)->filename<<endl;

        }
    }
    void showchildren(string searchstring){
        list <node*>::iterator iter;
        for(iter = current->children.begin(); iter!=current->children.end() ;iter++){
            if((*iter)->filename.find(searchstring)+1 > 0){
                cout<<(*iter)->filename<<endl;
            }
        }
    }

    bool del(string filename){
        list <node*>::iterator iter;
        for(iter = current->children.begin(); iter!=current->children.end() ;iter++){
            if((*iter)->filename == filename){
                current->children.remove(*iter);
                return true;
            }
        }
        return false;
    }

    bool search(string filename){
        list <node*>::iterator iter;
        for(iter = current->children.begin(); iter!=current->children.end() ;iter++){
            if((*iter)->filename == filename){
                return true;
            }
        }
        return false;
    }
    bool search(string filename,bool type){
        list <node*>::iterator iter;
        for(iter = current->children.begin(); iter!=current->children.end() ;iter++){
           if((*iter)->filename.compare(filename)== 0){
                return true;
            }
        }
        return false;
    }
    node* searchnode(string filename){
        list <node*>::iterator iter;
        for(iter = current->children.begin(); iter!=current->children.end() ;iter++){
            if((*iter)->filename == filename ){
               break;
            }
        }
        return (*iter);
    }
    void show(string,string);
    void mv(string);
    bool cd(string,bool);
    void rm(string);
    void rn(string,string);
    node* cp(string,string);
    node* filedisplay(string,bool);
    string wheris(string);
    void mk(string,bool);
    void mkdir(string,string,string);
};/////////////////////////////////////////////////////////////////// TREE //////////////////////////////////////////////////////////

bool tree::cd(string filename, bool x){
    list <node*>::iterator iter;
    node *savecurrent = current;
    string tempfilename;
    if(filename.find("/")+1 !=0 ){
        while(filename.find("/")+1 !=0 ){
            tempfilename = filename.substr(0,filename.find("/"));
            filename = filename.substr(filename.find("/")+1,filename.length());
            if(tempfilename.compare("..") == 0){
                current = current->prnt;
            }
            else{
                for(iter = current->children.begin(); iter!=current->children.end() ;iter++){
                    if((*iter)->filename == tempfilename){
                        current = (*iter);
                        break;
                    }
                }
            }
        }
        if(filename.compare("..") == 0){
            current = current->prnt;
        }else{
            for(iter = current->children.begin(); iter!=current->children.end() ;iter++){
                if((*iter)->filename == filename){
                    current = (*iter);
                    break;
                }
            }

            if(iter == current->children.end()){
                current = savecurrent;
                return false;
            }
        }
    }else{
        if(filename.compare("..") == 0){
            current = current->prnt;
        }
        else{
            for(iter = current->children.begin(); iter!=current->children.end() ;iter++){
                if((*iter)->filename == filename){
                    current = (*iter);
                    break;
                }
            }
        }
    }
    return true;
}

node* tree::filedisplay(string filename, bool type){
    list <node*>::iterator iter;
    for(iter = current->children.begin(); iter!=current->children.end() ;iter++){
        if((*iter)->filename == filename && (*iter)->type == type){
            break;
        }
    }
    return (*iter);
}

void tree::mv(string path){
    string filename;
    node *thiscurrent = root;
    string arrfiles[100];
    int i=0;

    while(path.compare("")!=0){
        path = path.substr(path.find("/")+1,path.length());
        filename = path.substr(0,path.find("/"));
        if(filename.compare("root"));
        else if(filename.compare("") != 0){
            arrfiles[i++] = filename;
        }
    }
    int max = i;
    i=0;
    while( i<max ){
        list <node*>::iterator iter;//TODO when mu stop
        for(iter = thiscurrent->children.begin(); iter!=thiscurrent->children.end() ;iter++){
            if((*iter)->filename == arrfiles[i]){
                thiscurrent = (*iter);
                break;
            }
        }
    }
}
void tree::mkdir(string file,string operation,string filename){
    string tempfilename;
    node *savecurrent = current;
    if(operation.compare("mkdir")==0){
        list <node*>::iterator iter;
        for(iter = current->children.begin(); iter!=current->children.end() ;iter++){
            if((*iter)->filename == tempfilename){
                cout<<"mkdir:"<<" sp:"<<" Already exists"<<endl;
                return;
            }
        }
    }
    insert(filename,true);
    current = savecurrent;
}
void tree::mk(string path,bool type){
    string tempfilename;
    node *savecurrent = current;
    while(path.find("/")+1 !=0 ){
        tempfilename = path.substr(0,path.find("/"));
        path = path.substr(path.find("/")+1,path.length());
        list <node*>::iterator iter;//TODO when mu stop
        if(tempfilename.compare("..") == 0){
            current = current->prnt;
        }else{
            for(iter = current->children.begin(); iter!=current->children.end() ;iter++){
                if((*iter)->filename == tempfilename){
                    current = (*iter);
                    break;
                }
            }
        }
    }
    insert(path,type);
    current = savecurrent;
}

node* tree::cp(string filename, string copyfilename){
    list <node*>::iterator iter,iter2;
    node* savecurrent = current;
    while(filename.find("../")==0){
        current= current->prnt;
        filename =  filename.substr(filename.find("/")+1,filename.length());
    }
    for(iter = current->children.begin(); iter!=current->children.end() ;iter++){
        if((*iter)->filename == filename){
            break;
        }
    }
    current = savecurrent;
    while(copyfilename.find("../")==0){
        current= current->prnt;
        copyfilename =  copyfilename.substr(copyfilename.find("/")+1,copyfilename.length());
    }
    for(iter2 = current->children.begin(); iter2!=current->children.end() ;iter2++){
        if((*iter2)->filename == copyfilename){
            break;
        }
    }
    if(iter2 == current->children.end()){
        this->insert((*iter)->type,copyfilename,(*iter)->data,(*iter)->timedate,(*iter)->prnt,(*iter)->children);
    }
    current = savecurrent;
}

void tree::rn(string filename,string copyfilename){
    list <node*>::iterator iter,iter2;
    node* savecurrent = current;
    while(filename.find("../")==0){
        current= current->prnt;
        filename =  filename.substr(filename.find("/")+1,filename.length());
    }
    for(iter = current->children.begin(); iter!=current->children.end() ;iter++){
        if((*iter)->filename == filename){
            break;
        }
    }
    current = savecurrent;
    while(copyfilename.find("../")==0){
        current= current->prnt;
        copyfilename =  copyfilename.substr(copyfilename.find("/")+1,copyfilename.length());
    }
    for(iter2 = current->children.begin(); iter2!=current->children.end() ;iter2++){
        if((*iter2)->filename == copyfilename){
            break;
        }
    }
    if(iter2 == current->children.end()){
        (*iter)->filename = copyfilename;
    }
    current = savecurrent;
}

int main(){//////////////////////////////////////////////////// MAIN ////////////////////////////////////////////////////////////////
    ofstream ofile("MPA4.out");
    ifstream ifile("MPA4.in");
    string lines,temp,parse;
    time_t now = time(0);
    tm *ltm = localtime(&now);
	tree mytree;
	if(ifile.is_open()){
		while(getline(ifile,lines)){
			temp = lines;
			int a;
            parse = temp.substr(0,temp.find(" "));
			if(parse =="mkdir"){
                parse = temp.substr(a =temp.find(" ")+1,temp.length());
                if(a!=0){
                    if(temp.find("/")+1 == 0){
                        mytree.insert(parse,true);
                    }
                    else{
                        mytree.mk(parse,true);
                    }
                }
                else{
                    cout<<"usage: mkdir <directory name>"<<endl;//TODO check all
                }
			}
			else if(parse=="cd"){
                    bool cdbool = true;
                parse = temp.substr(temp.find(" ")+1,temp.length());
                bool found;
                if(mytree.search(parse,true) || parse.compare("..") == 0 || temp.find("/")+1 != 0){
                    found = mytree.cd(parse,false);
                }
                else{
                    cout<<"cd: "<<parse<<" No such file or directory"<<endl;
                    cdbool = false;
                }
                if(!found &&cdbool){
                    cout<<"cd: "<<parse<<" No such file or directory"<<endl;
                }
			}
            else if(parse=="edit" || parse==">" || parse==">>"){
                parse = temp.substr(temp.find(" ")+1,temp.length());
                if(mytree.search(parse,false)){
                    string appenddesc;
                    node *tempdesc;
                    tempdesc = mytree.filedisplay(parse,false);
                    cout<<"Please input the data and press ENTER when done:"<<endl;
                    cin>>appenddesc;
                    tempdesc->data.append(appenddesc);
                }else{
                    mytree.insert(parse,false);
                }
			}
            else if(parse=="rm" ||  parse =="rmdir"){
                parse = temp.substr(temp.find(" ")+1,temp.length());
                mytree.del(parse);
			}
			else if(parse=="ls"){
                parse = temp.substr(temp.find(" ")+1,temp.length());
                temp = temp.substr(temp.find(" ")+1,temp.length());
                if(parse.compare("ls")== 0 && parse.length() == 2){
                     mytree.showchildren();
                }else{
                    if(parse[0] == '*'){
                        parse = parse.substr(parse.find("*")+1,parse.length());
                    }
                    if(parse[parse.length()-1] == '*'){
                        parse = parse.substr(0,parse.find("*"));
                    }
                    mytree.showchildren(parse);
                }
			}
			else if(parse=="rn"){
                string filename,copyfilename;
                temp = temp.substr(temp.find(" ")+1,temp.length());
                filename = temp.substr(0,temp.find(" "));
                if(mytree.search(filename)){
                    temp = temp.substr(temp.find(" ")+1,temp.length());
                    copyfilename = temp.substr(0,temp.length());
                    temp = temp.substr(temp.find(" ")+1,temp.length());
                    mytree.rn(filename,copyfilename);
                }else{
                    cout<<"usage:\t rn: <directory name> <new directory name>"<<endl;
                }
            }
			else if(parse=="cp"){
                string filename,copyfilename;
                temp = temp.substr(temp.find(" ")+1,temp.length());
                filename = temp.substr(0,temp.find(" "));
                if(mytree.search(filename)){
                    temp = temp.substr(temp.find(" ")+1,temp.length());
                    copyfilename = temp.substr(0,temp.length());
                    temp = temp.substr(temp.find(" ")+1,temp.length());
                    mytree.cp(filename,copyfilename);
                }else{
                    cout<<"usage:\t cp source_file/source_directory "<<"\n\ttarget_file/target_directory"<<endl;
                }
			}
            else if(parse=="mv"){
                string filename,replacement;
                parse = temp.substr(temp.find(" ")+1,temp.length());
                if(parse.find("/")== 0){
                    mytree.mv(parse);
                }else{
                    string filename,copyfilename;
                    temp = temp.substr(temp.find(" ")+1,temp.length());
                    filename = temp.substr(0,temp.find(" "));
                    if(mytree.search(filename)){
                        temp = temp.substr(temp.find(" ")+1,temp.length());
                        copyfilename = temp.substr(0,temp.length());
                        temp = temp.substr(temp.find(" ")+1,temp.length());
                        mytree.rn(filename,copyfilename);
                    }else{
                        cout<<"usage:\t rn: <directory name> <new directory name>"<<endl;
                    }
                }
			}
            else if(parse=="show"){
                parse = temp.substr(temp.find(" ")+1,temp.length());
                mytree.filedisplay(parse,false);
			}
            else if(parse=="whereis"){
                parse = temp.substr(temp.find(" ")+1,temp.length());
                cout<<mytree.root->whereis(parse)<<endl;
			}else{//TODO
			    string directory, file, operation;
                if(parse[parse.length()-1] == '$'){
                    file = parse.substr(0,parse.find('$'));
                    parse = temp.substr(temp.find(" ")+1,temp.length());
                }
                operation = parse.substr(0,parse.find(" "));
                parse = parse.substr(parse.find(" ")+1,parse.length());
                mytree.mkdir(file,operation,parse);
			}
		}
		ifile.close();
	}
    return 0;
}
