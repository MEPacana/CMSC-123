#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <sstream>

using namespace std;

class packet{
public:
    string elem;
    bitset<32> bsource,bdest;
    bitset<16>bseq,bpsize,bchecksum;
    string source,dest,seq,psize,checksum,packetdata,sourcedest;
    bool boolchecksum;
    int datasize;
    packet* next;
    string SBit(string);
    string SeqBit(string);
    string getSeqBit(){return seq;};
    string getSource(){return source;};
    string getDest(){return dest;};
    string getSize(){return psize;};
    string getPacketData(){return packetdata;};
    string getSourceDest(){return sourcedest;};
    bool compareCheckSum(string,string,string);
    string toPacketData(string);
    packet();
    packet(string n);
};

string IntToString ( int number )
{
  ostringstream oss;
  oss<< number;

  return oss.str();
}
packet::packet(string n){
    string tempsource, tempdest, tempseq, temppsize,tempchecksum,templine;
    elem = n;
    int x = 32;
    tempsource = n.substr(0,32);
    tempdest = n.substr(32,32);
    tempseq = n.substr(64,16);

    tempchecksum = n.substr(80,16);
    temppsize = n.substr(96,16);

    bitset<32> temp1(tempsource);
    bsource = temp1;
    source = SBit(tempsource);

    bitset<32> temp2(tempdest);
    bdest = temp2;
    dest = SBit(tempdest);
    sourcedest.append(source);
    sourcedest.append(".");
    sourcedest.append(dest);

    bitset<16> temp3(tempseq);
    bseq = temp3;
    seq = SeqBit(tempseq);

    bitset<16> temp4(temppsize);
    bpsize = temp4;
    psize = SeqBit(temppsize);

    boolchecksum=compareCheckSum(n,tempchecksum,psize);
    templine = n.substr(112,datasize);
    packetdata = toPacketData(templine);
    next = NULL;
}
bool packet::compareCheckSum(string n,string tempchecksum,string psize ){
    n.replace(80,16,"0000000000000000");
    string first,second;
    int nsize;
    istringstream (psize) >>nsize;
    datasize = nsize;
    nsize+=112;
    nsize+=nsize%16;
    first = "0000000000000000";
    second = n.substr(0,16);
    int x;
    bool carry=false;
    for(x = 0,carry= false; x < nsize;carry =false){
        for(int i = first.length()-1; i>=0 ;i--){
            if(second[i]=='1' || first[i]=='1' ){
                if((second[i]=='1' && first[i]=='0') ||(second[i]=='0' && first[i]=='1')){
                    if(carry){
                        second.replace(i,1,"0");
                    }
                    else{
                        second.replace(i,1,"1");
                    }

                }
                else if(second[i]=='0' && first[i]=='0'){
                    if(carry){
                        second.replace(i,1,"1");
                        carry = false;
                    }
                    else{
                        second.replace(i,1,"0");
                    }
                }
                else{
                    if(carry){
                        second.replace(i,1,"1");
                    }
                    else{
                        second.replace(i,1,"0");
                        carry = true;
                    }

                }
            }else{
                    if(carry){
                        second.replace(i,1,"1");
                        carry= false;
                    }
                    else{
                        second.replace(i,1,"0");
                    }
            }
        }
        if(carry){
            first.assign("0000000000000001");
        }
        else{
            x+=16;
            first.assign(n.substr(x,16));
        }
    }
    for(int i = second.length()-1; i>=0 ;i--){
        if(second[i]=='0'){
            second.replace(i,1,"1");
        }else{
            second.replace(i,1,"0");
        }
    }
    if(second.compare(tempchecksum) == 0){
        return true;
    }
    else{
        return false;
    }
}
string packet::toPacketData(string templine){
    string temppacketdata,temp;
    int i,tempascii;

    for(i = 0; i < templine.length(); i+=8){
        temp.assign(templine.substr(i,8));
        bitset<8> temp2(temp);
        tempascii = (short)(temp2.to_ulong());
        if(tempascii == 226 ||tempascii == 128 ||tempascii == 153){
            if(tempascii == 226){
                string k;
                k.append("'");
                temp = k;
                temppacketdata.append((string)temp);
            }
        }
        else{
            temp = IntToString (tempascii);
            temp = (char)tempascii;
            temppacketdata.append((string)temp);
        }
    }
    return temppacketdata;
}

string packet::SBit(string tempsource){

    string fnum,snum,tnum,fonum,temp;
    int sfnum,ssnum,stnum,sfonum;
    fnum = tempsource.substr(0,8);
    snum = tempsource.substr(8,8);
    tnum = tempsource.substr(16,8);
    fonum = tempsource.substr(24,8);
  bitset<8> bfnum(fnum),bsnum(snum),btnum(tnum),bfonum(fonum);
    sfnum = (short)(bfnum.to_ulong());
    ssnum = (short)(bsnum.to_ulong());
    stnum = (short)(btnum.to_ulong());
    sfonum = (short)(bfonum.to_ulong());
    fnum = IntToString (sfnum);
    snum = IntToString (ssnum);
    tnum = IntToString (stnum);
    fonum = IntToString (sfonum);
    temp = (fnum+"."+snum+"."+tnum+"."+fonum);
    return temp;
}
string packet::SeqBit(string tempseq){
    bitset<16> bseq(tempseq);
    int stempseq;
    stempseq = (short int)(bseq.to_ulong());
    if(stempseq < 0){
        stempseq *= -1;
    }
    tempseq = IntToString (stempseq);
    return tempseq;
}


template <class T>
class list{
public:
    int size;
    packet *head,*tail;
public:
    list();
    ~list();
    list(const list&);
    list& operator=(const list&);
    bool insert(int, T);
    bool insert2(int, T);
    T get(int);
    string getPacketData(int);
    string getSource(int);
    string getPSize(int);
    string getDest(int);
    string getSeq(int);
    string getSourceDest(int);
    bool getCheckSum(int);
    int order(T);
    bool set(T ,int);
    void display();
    bool remove(int);

};
template <class T>
int list<T>::order(T n){
    string sourcedest = n.getSourceDest();
    string seqnum = n.getSeqBit();
    T *temp = head;
    int x, temp1, temp2;
    istringstream (seqnum) >>temp1;
    bool place;
    for(x = 0,place = false; x < size ;x++,temp=temp->next){
        if(sourcedest.compare(temp->getSourceDest()) == 0){
            place = true;
            string tempseq = temp->getSeqBit();
            istringstream (temp->getSeqBit()) >>temp2;
            if(temp1 < temp2){
                return x;
            }
        }
        else if(sourcedest.compare(temp->getSourceDest()) != 0){
            if(place){
                return x;
            }
        }
    }
    return x;
}
template <class T>
void display(list <T>);

template <class T>
list<T>::list(){
    size = 0;
    head = tail = NULL;
}

template <class T>
list<T>::list(const list<T>&l){
    size = 0;
    head = tail = NULL;
    packet *temp = l.head;
    for(int i = 0; i < l.size ; i++, temp = temp->next){
        insert(i,temp->elem);
    }
}
template <class T>
bool list<T>::insert(int i, T n){
    if(i<0 || i>size){
        return false;
    }
    T *x = new T(n);
    if(size == 0){
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
        T *temp = head;
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
    if(n<0 || n>=size){
        throw 69;
    }
    else{
        packet *temp = head;
        for(int i = 0; i < n; i++, temp = temp->next);
        return temp->elem;
    }
}
template <class T>
string list<T>::getSource(int n){
    string source;
    if(n<0 || n>=size){
        throw 69;
    }
    else{
        packet *temp = head;
        for(int i = 0; i < n; i++, temp = temp->next);
        source = temp->source;
    }
    return source;
}

template <class T>
bool list<T>::getCheckSum(int n){
    bool checksum;
    if(n<0 || n>=size){
        throw 69;
    }
    else{
        packet *temp = head;
        for(int i = 0; i < n; i++, temp = temp->next);
        checksum = temp->boolchecksum;
    }
    return checksum;
}

template <class T>
string list<T>::getDest(int n){
    string dest;
    if(n<0 || n>=size){
        throw 69;
    }
    else{
        packet *temp = head;
        for(int i = 0; i < n; i++, temp = temp->next);
        dest = temp->dest;
    }
    return dest;
}

template <class T>
string list<T>::getSeq(int n){
    string seq;
    if(n<0 || n>=size){
        throw 69;
    }
    else{
        packet *temp = head;
        for(int i = 0; i < n; i++, temp = temp->next);
        seq = temp->seq;
    }
    return seq;
}

template <class T>
string list<T>::getPSize(int n){
    string psize;
    if(n<0 || n>=size){
        throw 69;
    }
    else{
        packet *temp = head;
        for(int i = 0; i < n; i++, temp = temp->next);
        psize = temp->psize;
    }
    return psize;
}

template <class T>
string list<T>::getPacketData(int n){
    string packetData;
    if(n<0 || n>=size){
        throw 69;
    }
    else{
        packet *temp = head;
        for(int i = 0; i < n; i++, temp = temp->next);
        packetData = temp->packetdata;
    }
    return packetData;
}

template <class T>
string list<T>::getSourceDest(int n){
    string sourcedest;
    if(n<0 || n>=size){
        throw 69;
    }
    else{
        packet *temp = head;
        for(int i = 0; i < n; i++, temp = temp->next);
        sourcedest = temp->sourcedest;
    }
    return sourcedest;
}
template <class T>
bool list<T>::set(T n,int pos){
    if(pos<0 || pos>=size){
        return false;
    }
    else{
        packet *temp = head;
        for(int pos2 = 0; pos2 < pos; pos2++){
            temp = temp->next;
        }
        temp->elem = n;
    }
    return true;
}

template <class T>
list<T>::~list(){
	packet *temp = head;

    while(head != NULL){
        remove(size-1);
    }
}

template <class T>
bool list<T>::remove(int pos){
    if(pos<0 || pos>=size){
        return false;
    }
    else if(size==0){
        return false;
    }
    else{
        packet *temp = head;
        if(pos==0){
            head = head->next;
            delete temp;
        }
        else{
            for(int pos2 = 0; pos2 < pos-1; pos2++){
                temp = temp->next;
            }
            if(pos == size - 1){
                delete tail;
                tail = temp;
                tail->next = NULL;
            }
            else{
                packet *temp2 = temp->next;
                temp->next = temp2->next;
                delete temp2;
            }
        }
    }
    size--;
    return true;
}


template <class T>
void display(list <T>l){
    ofstream file("output_in_order.out");
    string sourcedeckcomparer = l.getSource(0);
    int iexpectedseq = 0,icurrentseq = 0;
    bool repeat = false;
    for(int i = 0; i < l.size; repeat = false){
        istringstream (l.getSeq(i)) >>icurrentseq;
        if(!(l.getCheckSum(i))){
            cout<<"[line corrupted]"<<endl;
            file<<"[line corrupted]"<<endl;
            i++;
        }
        else{
            if(sourcedeckcomparer.compare(l.getSource(i)) != 0){
                file<<"--------------------------------------------------------------------------------\n"<<endl;
                cout<<"--------------------------------------------------------------------------------\n"<<endl;
                sourcedeckcomparer.assign(l.getSource(i));
                iexpectedseq = 0;
            }
            if(iexpectedseq - 1 == icurrentseq){
                iexpectedseq -=1;
                repeat = true;
            }
            if(iexpectedseq != icurrentseq){
                if(iexpectedseq == 0){
                    cout<<"[title missing]"<<endl;
                    file<<"[title missing]"<<endl;
                }
                else{
                    cout<<"[line missing]"<<endl;
                    file<<"[line missing]"<<endl;
                }
            }
            else{
                if(!repeat){
                    cout<<l.getPacketData(i)<<endl;
                    file<<l.getPacketData(i)<<endl;
                    if(l.getSeq(i).compare("0") == 0){
                        file<<l.getPacketData(i)<<" "<<l.getSeq(i)<<endl;
                        cout<<l.getSource(i)<<"/"<<l.getDest(i)<<endl;
                    }
                }
                i++;
            }
        }
        iexpectedseq++;
   }
   file.close();
   cout<<endl;
}


int main(){
	ifstream file("cases_random.in");
	if(file.is_open()){

        list <packet> packetlist;
        list <list<packet> >poemlist;

 		string lines,temp;
		bitset<16> bsource,bdest;
		int temppos;
		while(getline(file,lines)){
            packet temppacket(lines);
            temp = temppacket.getSeqBit();
            istringstream (temp) >>temppos;
            packetlist.insert(packetlist.order(temppacket),temppacket);
		}
        display(packetlist);//file writing
		file.close();
	}
	return 0;
}
