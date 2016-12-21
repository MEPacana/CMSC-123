//I declare upon my honor that I made this mp by myself
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFSIZE 1000

typedef struct elem{//initializing structs
    char lib[100];
    struct elem *next;
}node;

typedef struct{//linked list for checking
    node *head, *tail;
    int size;
}list;


void init(list*);
void write(list*,FILE*,FILE*);
void addhead(list*,char*);
int checkhead(list*,char*);


int main(){//main
    list dir;//making my linked list
    init (&dir);
    FILE *ofp,*fp;//to write on file and read file
    fp=fopen("inputFile.cpp","r");
    ofp=fopen("outputFile.out","w");

    if(fp == NULL){
		printf("\nI couldn't open test.h for reading.");
	}
    if(ofp == NULL){
		printf("\nI couldn't open outpputFile for writing.");
	}
	write(&dir,ofp,fp);//to write on out file
    fclose(ofp);
    fclose(fp);
    return 0;
}

void init(list *d){//initializes linked list
    d->head=d->tail=NULL;
    d->size=0;
}

void write(list *d,FILE *ofp,FILE *fp){//writes on file
    char x[100];//my string
    int i,j;
    char word2[100];
    char* parse;
    for(;fgets(x,BUFFSIZE-1,fp)!=NULL;){//reads every line
        strcpy(word2, x);
        parse=strtok(word2," \"");//parsing
        i= strcmp(parse,"#include");//checks if header
        if(i==0){
            parse=strtok(NULL," \"");
            if(checkhead(d,parse)==0);//checks if used header
            else{
                FILE *fp2;
                fp2=fopen(parse,"r");
                addhead(d,parse);
                write(d, ofp, fp2);
                fprintf(ofp,"\n",x);//SPACING
            }
        }
        else{
            for(j=0;x[j]!='\0'&& x[j]!='\n';j++);
            if(x[j]=='\n'|| x[j]=='\0'){//I HAD NO SLEEP BECAUSE OF SPACING
                x[j]='\0';
            }
            if(x[0]!='\n' && x[0]!='\0')
                fprintf(ofp,"%s\n",x);
        }
    }
}
void addhead(list *dir,char *name){//Appends list of headers
    node *n=malloc(sizeof(node));
    n->next=NULL;
    int i;
    strcpy(n->lib, name);
    if(dir->size==0){
        dir->head = dir->tail = n;
    }
    else{
        dir->tail->next=n;
        dir->tail=n;
    }
    node *temp= dir->head;
    dir->size++;
    for(;temp!=NULL;){
        temp=temp->next;
    }
}
int checkhead(list *dir,char *name){//checks if there are reused headers
    node *temp= dir->head;
    int i;
    for(;temp!=NULL;){
        i=strcmp(temp->lib,name);
        if(i==0){
            return 0;
        }
        temp=temp->next;
    }
    return 1;
}
