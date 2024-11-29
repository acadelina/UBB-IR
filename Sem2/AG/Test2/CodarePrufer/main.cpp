#include <iostream>
#include<fstream>
#include<vector>
using namespace std;
ifstream f("in.txt");
//CODARE PRUFER
struct nod{
int parinte;
bool e_fr=true;
bool in_ar=true;
};
int alte_vf_decat_rad(nod vf[],int m)
{
    //se verifica daca exista cel putin inca un nod pe langa rad
    for(int i=0;i<m;i++)
    {
        if(vf[i].parinte!=-1 && vf[i].in_ar)
            return 1;
    }
    return 0;
}

int frunz_min(nod vf[],int m)
{
    //frunza de val min
    for(int i=0;i<m;i++)
        if(vf[i].e_fr && vf[i].in_ar)
            return i;
    return -1;
}

int nr_copii(nod vf[],int par,int m)
{

    int copii=0;
    for(int i=0;i<m;i++)
    {
        if(vf[i].parinte==par && vf[i].in_ar)
            copii++;
    }
    return copii;
}

vector<int> codare(nod vf[],int m)
{
    vector<int> prufer;


    while(alte_vf_decat_rad(vf,m)==1)
    {

        int fr_min=frunz_min(vf,m);
        prufer.push_back(vf[fr_min].parinte);//adaugam parintele frunzei in codare
        vf[fr_min].in_ar=false;//scoatem frunza din arbore

        if(nr_copii(vf,vf[fr_min].parinte,m)==0)
            vf[vf[fr_min].parinte].e_fr=true;//daca parintele frunzei adaugate nu mai are copii devine frunza


    }
    cout<<"Codul Prufer:\n";
    for(int i:prufer)
        cout<<i<<" ";
    return prufer;
}

void decodare(vector<int> prufer,int m)
{

    int rad,x,y;
    int tata[100];

    for(int i=0;i<m;i++)
    {
        x=prufer[0];
        if(i==m-1)
        {
            rad=x;
        }
        y=m+1;
        //caut cel mai mic nr care nu se gaseste in prufer
        for(int l=0;l<=m;l++)
        {

            bool gasit=false;
            for(int j=0;j<prufer.size()&&!gasit;j++)
            {
                if(prufer[j]==l)
                {
                    gasit=true;
                }
            }
            if(!gasit&&l<y)
                    y=l;

        }

        tata[y]=x;//x devine tatal lui y
        prufer.erase(prufer.begin()+0);
        prufer.push_back(y);
    }
    cout<<"Decodare prufer:\n";
    cout<<m+1<<"\n";
    tata[rad]=-1;
    for(int i=0;i<=m;i++)
        cout<<tata[i]<<" ";
}
int main()
{
    int m;
    f>>m;
    nod vf[m];
    for(int i=0;i<m;i++)
    {

        f>>vf[i].parinte;
        if(vf[i].parinte!=-1)
            vf[vf[i].parinte].e_fr=false;
    }
    //codare(vf,m);
    decodare(codare(vf,m),m-1);
    f.close();
    return 0;
}
