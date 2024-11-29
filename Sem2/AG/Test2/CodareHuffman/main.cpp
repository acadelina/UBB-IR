#include <iostream>
#include<fstream>
#include<queue>
#include<unordered_map>
using namespace std;
ifstream f("in.txt");

struct Nod{
    char litera;
    int frecv;
    Nod *stg,*dr;
};

Nod* alocaNod(char ch,int frecv,Nod* st,Nod* dr)
{

    Nod* nod=new Nod();
    nod->litera=ch;
    nod->frecv=frecv;
    nod->stg=st;
    nod->dr=dr;

    return nod;
}
struct comp{
bool operator()(Nod* nod1,Nod* nod2)
{
    if(nod1->frecv==nod2->frecv)
    {
        return nod1->litera>nod1->litera;
    }
    return nod1->frecv>nod2->frecv;
}
};

void codare(Nod* rad,string str, unordered_map<char,string> &huffmanCode)
{
    if(rad==nullptr)
        return;//am ajuns la capatul arborelui

    //am gasit o frunza
    if(rad->stg ==nullptr&& rad->dr==nullptr)
    {
        huffmanCode[rad->litera]=str;
    }

    codare(rad->stg,str+"0",huffmanCode);
    codare(rad->dr,str+"1",huffmanCode);
}

void decodare(Nod* rad,int& index,string str)
{
    if(rad==nullptr)
        return;

    if(rad->dr==nullptr&& rad->stg==nullptr)
    {
        cout<<rad->litera;
        return;
    }
    index++;
    if(str[index]=='0')
        decodare(rad->stg,index,str);
    else
        decodare(rad->dr,index,str);
}

void buildHuffman(char data[],int frecv[],int nr_char,string text)
{
    priority_queue<Nod*,vector<Nod*>,comp>pq;

    //crearea unui nod frunza pt fiecare caracter

    for(int i=0;i<nr_char;i++)
    {
        Nod* n=alocaNod(data[i],frecv[i],nullptr,nullptr);
        pq.push(n);
    }

    while(pq.size()!=1)
    {
        //extragem vf cu frecv min
        Nod* left=pq.top();
        pq.pop();
        Nod* right=pq.top();
        pq.pop();

        //suma frecv minime
        int sum=left->frecv+right->frecv;

        //alocarea unui nod parinte a celor doua noduri
        Nod* z=alocaNod('\0',sum,left,right);

        pq.push(z);
    }

    //radacina arborelui
    Nod* rad=pq.top();

    //traversarea arborelui si construirea codului Huffman
    unordered_map<char,string> huffmanCode;
    codare(rad,"",huffmanCode);

    cout<<"Codurile Huffman pt fiecare litera:\n";
    for(auto pair:huffmanCode)
    {
        cout<<pair.first<<" "<<pair.second<<"\n";
    }

    cout<<"Codul lui Huffman: ";
    string str="";
    for(char ch:text)
    {
        str+=huffmanCode[ch];
    }
    cout<<str<<"\n";

    //decodarea
    cout<<"Decodare Huffman:\n";
    int index=-1;
    while(index<(int)str.size()-2)
    {
        decodare(rad,index,str);
    }

}


int citire(char data[],int frecv[],string &text)
{
    int fr[256]={0};
    char c;

    while(!f.eof())
    {
        f.get(c);
        fr[c]++;
        text+=c;
    }
    fr[c]--;
    text[text.size()-1]='\0';


    int j=0,nr_char=0;
    for(int i=0;i<256;i++)
    {
        if(fr[i]!=0)
        {
            data[j]=char(i);
            frecv[j]=fr[i];
            nr_char++;
            j++;
        }
    }
    f.close();
    return nr_char;
}

void afis(char data[],int frecv[],int nr_char)
{
    cout<<nr_char<<'\n';
    for(int i=0;i<nr_char;i++)
    {
        cout<<data[i]<<" "<<frecv[i]<<"\n";
    }
}
int main()
{
    char data[256];
    int frecv[256]={};
    int nr_char;
    string text;
    nr_char=citire(data,frecv,text);
    afis(data,frecv,nr_char);
    buildHuffman(data,frecv,nr_char,text);
    return 0;
}
