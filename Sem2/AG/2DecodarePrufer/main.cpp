#include <iostream>
#include <bits/stdc++.h>

using namespace std;
ifstream f("in.txt");

void code_to_tree(vector<int> &prufer, int m)
{
    int rad,y,x;
    int tata[100]; // vectorul de parinti

    // se parcurge de m-1 ori
    for(int i=0;i<m;i++)
    {
        x=prufer[0]; // iau primul element din codul lui Prufer
        if(i==m-1) // selectez radacina
        {
            rad=x;
        }
        y=m+1;
        // caut cel mai mic nr natural care NU se gaseste in prufer[]
        for(int l=0;l<=m;l++)
        {
            bool gasit=false;
            for(int j=0;j<prufer.size() && !gasit;j++)
            {
                if(prufer[j]==l)
                {
                    gasit=true;
                }
            }
            if(!gasit && l < y){
                y=l;
            }
        }
        tata[y]=x; // x devine parintele lui y
        prufer.erase(prufer.begin()+0); // se sterge x din codul lui Prufer
        prufer.push_back(y); // se adauga y in Prufer
    }

    cout<<"Decodare Prufer:\n";
    cout<<m+1<<endl;
    tata[rad]=-1;
    for(int i=0;i<=m;i++){
        cout<<tata[i]<<" ";
    }
}



int main() {


    int m;
    f>>m;

    vector<int> prufer;
    int cif;

    for(int i=0;i<m;i++)
    {
        f>>cif;
        prufer.push_back(cif);
    }

    cout<<"Codul Prufer:";
    for(int i=0;i<m;i++)
    {
        cout<<prufer[i]<<" ";
    }
    cout<<endl;

    code_to_tree(prufer, m);


    f.close();
    return 0;
}
