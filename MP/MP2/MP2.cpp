#include <stdio.h>
int secondsearch(int[]);
int firstsearch(int[]);
int bubble(int[]);
int main(){
    int i,numb[10],ans;
    for(i=0;i<10;i++){
        scanf("%i",&numb[i]);
    }
    ans=firstsearch(numb);
    printf("First Search:\n");
    if(ans==-1){
        printf("none\n");
    }
    else{
        printf("%i, at index %i\n",ans,ans);
    }
    ans=secondsearch(numb);
    printf("Second Search:\n");
    if(ans==-1){
        printf("none\n");
    }
    else{
        printf("%i,at index %i\n",ans,ans);
    }
}
int bubble(numb[]){
    int i,j;
    for(i=0;numb[i];i++){
        for(j=i;j<10;j++){
            if(numb[j]<numb[j+10])
        }
    }
}
int firstsearch(int numb[]){
    int i;
    for(i=0;i<10;i++){
        if(i==numb[i]){
            printf("%i compared to %i\n",i, numb[i]);
            return i;
        }
    }
    return -1;
}
int secondsearch(int numb[]){
    int i,ub=10,lb=9,mid;
    for(i=0;i<10;i++){
        mid=(ub-lb)/2;
        if(numb[mid+1]>mid+1){
            ub=mid-1;
        }
        else if(numb[mid+1]<mid+1){
            lb=mid+1;
        }
        else {
            return mid+1;
        }
    }
    return -1;
}
