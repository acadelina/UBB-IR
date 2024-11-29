#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<stack>
#include<set>
#include<climits>
using namespace std;

ifstream f("in.txt");

struct nod{
int frec;
char lit;
nod* n1;
nod* n2;
};

nod* alocanod(int f,char l,nod* n1,nod* n2)
{
    nod* n=new nod();
    n->frec=f;
    n->lit=l;
    n->n1=n1;
    n->n2=n2;
    return n;
}

struct comp{
bool operator()(nod* n1,nod* n2)
{
    if(n1->frec==n2->frec)
        return n1->lit>n2->lit;
    return n1->frec>n2->frec;
}};

void codare(nod* rad,string str, unordered_map<char,string>&HC)
{
    if(rad==nullptr)
        return;
    if(rad->n1==nullptr&& rad->n2==nullptr)
        HC[rad->lit]=str;
    codare(rad->n1,str+"0",HC);
    codare(rad->n2,str+"1",HC);
}

void decodare(nod* rad,int &index,string str)
{
    if(rad==nullptr)
        return;
    if(rad->n1==nullptr&&rad->n2==nullptr)
    {
        cout<<rad->lit;
        return;
    }
    index++;
    if(str[index]=='0')
        decodare(rad->n1,index,str);
    else
        decodare(rad->n2,index,str);
}

void build(int frec[],char data[],int nrc,string str)
{
    priority_queue<nod*,vector<nod*>,comp> pq;
    for(int i=0;i<nrc;i++)
    {
        nod* n=alocanod(frec[i],data[i],nullptr,nullptr);
        pq.push(n);
    }
    while(pq.size()!=1)
    {
        nod* n1=pq.top();
        pq.pop();
        nod* n2=pq.top();
        pq.pop();
        int sum=n1->frec+n2->frec;
        nod* z=alocanod(sum,'\0',n1,n2);
        pq.push(z);
    }
    nod *rad=pq.top();

    unordered_map<char,string> HC;
    codare(rad,"",HC);
    string txt="";
    for(char a:str)
    {
        txt+=HC[a];
    }
    cout<<txt<<"\n";

    int index=-1;
    while(index<(int)txt.size()-2)
        decodare(rad,index,txt);
}

int citire(int frec[],char data[],string& str)
{
    int nrc=0,fr[256]={0};
    char c;
    while(!f.eof())
    {
        f.get(c);
        fr[c]++;
        str+=c;
    }

    for(int i=0;i<256;i++)
    {
        if(fr[i]>0)
        {
            frec[nrc]=fr[i];
            data[nrc]=char(i);
            nrc++;
        }
    }
    str[str.size()-1]='\0';
    return nrc;
}

int main()
{
    int frec[256]={};
    char data[256];
    string str;
    int nrc;
    nrc=citire(frec,data,str);
    build(frec,data,nrc,str);
}

