#include <iostream>
#include <bits/stdc++.h>

using namespace std;
ifstream f("in.txt");
struct nod{
    int parinte{};
    bool e_frunza=true;
    bool e_in_arbore=true;
};

int alte_vf_decat_radacina(nod vf[],int m)
{
    // verific daca in arbore exista cel putin un varf != radacina
    for(int i=0;i<m;i++)
    {
        if(vf[i].parinte!=-1 && vf[i].e_in_arbore)
            return 1;
    }
    return 0;
}

int cauta_frunza(nod vf[],int m)
{
    // cauta si returneaza frunza de valoare minima care se regaseste in arbore
    for(int i=0;i<m;i++)
    {
        if(vf[i].e_frunza && vf[i].e_in_arbore)
            return i;
    }
    return -1;
}

int cati_copii(nod vf[],int parinte,int m)
{
    // determina cati copii are un parinte (copii inca prezenti in arbore)
    int copii=0;
    for(int i=0;i<m;i++)
    {
        if(vf[i].parinte==parinte && vf[i].e_in_arbore)
            copii++;
    }
    return copii;
}


void tree_to_code(nod vf[], int m)
{
    vector<int> prufer;

    while(alte_vf_decat_radacina(vf,m)==1)
    {
        int poz_frunza_minima= cauta_frunza(vf,m);

        prufer.push_back(vf[poz_frunza_minima].parinte);
        vf[poz_frunza_minima].e_in_arbore=false; // scot frunza din arbore

        // daca parintele nu mai are alti copii, acesta se transforma in frunza
        if(cati_copii(vf,vf[poz_frunza_minima].parinte,m)==0)
        {
            vf[vf[poz_frunza_minima].parinte].e_frunza=true;
        }

    }

    cout<<"Codul lui Prufer:\n";
    for(int i : prufer)
        cout<<i<<" ";
}

int main() {

    int m;
    f>>m;

    nod vf[m];
    for(int i=0;i<m;i++)
    {
        f>>vf[i].parinte;

        // varful parinte al lui vf[i] nu este frunza
        if(vf[i].parinte!=-1) // daca nu e radacina
        {
            vf[vf[i].parinte].e_frunza=false;
        }
    }




    tree_to_code(vf,m);

    f.close();
    return 0;
}
