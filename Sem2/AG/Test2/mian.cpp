






























//CODARE DECODARE PRUFER
#include <iostream>
#include<fstream>
#include<vector>
using namespace std;
ifstream f("in.txt");

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




//CODARE DECODARE HUFFMAN

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




//FORD FULKERSON



#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <stack>
using namespace std;
ifstream f("in.txt");
ofstream g("out.txt");

int n;

bool DFS(vector<vector<int>>graf, vector<int>& parinte)
{
	//facem un vector de parinti pentru a putea parcurge inapoi pt actualizari flux
	stack<int> st;
	vector<bool> vizitat(n);

	for (int i = 0; i < n; i++)
		vizitat[i] = 0;

	st.push(0);
	parinte[0] = -1;
	vizitat[0] = 1;
	while (!st.empty())
	{
		int nod = st.top();
		st.pop();
		for (int i = 0; i < graf[nod].size(); i++)
		{
			if (graf[nod][i] != 0 && !vizitat[i])
			{
				parinte[i] = nod;
				if (i == n - 1)
					return true;
				vizitat[i] = 1;
				st.push(i);
			}
		}
	}
	return false;
}


int FordFulkerson(vector<vector<int>>graf, int s, int d)
{
	vector<int> parinte;
	parinte.resize(graf.size());
	int flux_maxim = 0;

	//cat timp mai exista parcurgeri
	while (DFS(graf,parinte))
	{
		int flux_curent = INT_MAX;

		//cautam minimul ce poate intra pe drumul gasit
		for (int u = d; u != s; u = parinte[u])
		{
			int v = parinte[u];
			flux_curent = min(flux_curent, graf[v][u]);
		}
		//actualizam fluxurile
		for (int u = d; u != s; u = parinte[u])
		{
			int v = parinte[u];
			graf[v][u] = graf[v][u] - flux_curent;
			graf[u][v] = graf[u][v] + flux_curent;
		}

		//fluxul maxim va fi suma fluxurilor de pe fiecare drum
		flux_maxim = flux_maxim + flux_curent;
	}
	return flux_maxim;
}


int main()
{
	int m, x, y, z;
	vector<vector<int>> graf;
	f >> n >> m;
	for (int i = 0; i < n; i++)
	{
		vector<int> linie(n);
		graf.push_back(linie);
	}
	for (int i = 0; i < m; i++)
	{
		f >> x >> y >> z;
		graf[x][y] = z;
	}
	cout << FordFulkerson(graf, 0, n - 1);

}





//EDMONDS KARP



#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
ifstream f("in.txt");
ofstream g("out.txt");


bool BFS(vector<vector<int>>graf, int s, int d, vector<int>& parinte)
{	//facem un vector de parinti pentru a putea parcurge inapoi pt actualizari flux
	vector<bool> viz;
	viz.resize(graf.size());
	parinte[s] = -1; viz[s] = true;
	queue<int> coada;
	coada.push(s);
	while (!coada.empty())
	{
		int x = coada.front();
		coada.pop();
		for (int i = 0; i < graf[x].size(); i++)
		{
			if (graf[x][i] != 0 && viz[i] == false)
			{
				parinte[i] = x;
				viz[i] = true;
				coada.push(i);
				if (i == d) return true;
			}
		}
	}
	return false;
}


int EdmondsKarp(vector<vector<int>>graf, int s, int d)
{
	vector<int> parinte;
	parinte.resize(graf.size());
	int flux_maxim = 0;

	//cat timp mai exista parcurgeri
	while (BFS(graf, s, d, parinte))
	{
		int flux_curent = INT_MAX;

		//cautam minimul ce poate intra pe drumul gasit
		for (int u = d; u != s; u = parinte[u])
		{
			int v = parinte[u];
			flux_curent = min(flux_curent, graf[v][u]);
		}
		//actualizam fluxurile
		for (int u = d; u != s; u = parinte[u])
		{
			int v = parinte[u];
			graf[v][u] = graf[v][u] - flux_curent;
			graf[u][v] = graf[u][v] + flux_curent;
		}
		flux_maxim = flux_maxim + flux_curent;
	}
	return flux_maxim;
}


int main()
{
	int n, m, x, y, z;
	vector<vector<int>> graf;
	f >> n >> m;
	for (int i = 0; i < n; i++)
	{
		vector<int> linie(n);
		graf.push_back(linie);
	}
	for (int i = 0; i < m; i++)
	{
		f >> x >> y >> z;
		graf[x][y] = z;
	}
	g << EdmondsKarp(graf, 0, n - 1);

}





//CICLU EULERIAN FLEURY

#include <iostream>
#include <fstream>
#define MAX_V 50
using namespace std;


int cauta_nod_start(int graf_copy[][MAX_V], int nr_vf)
{
    for(int i=0;i<nr_vf;i++)
    {
        int grad = 0;
        for(int j=0;j<nr_vf;j++)
        {
            if(graf_copy[i][j]==1)
                grad++;
        }
        if(grad%2!=0)
            return i;
    }
    return 0;
}

int nr_muchii(int graf_copy[][MAX_V],int nr_vf)
{
    int cate=0;
    for(int i=0;i<nr_vf;i++)
    {
        for(int j=0;j<nr_vf;j++)
        {
            if(graf_copy[i][j]==1)
                cate++;
        }
    }
    return cate;
}

bool e_punte(int u,int v, int graf_copy[][MAX_V], int nr_vf)
{
    int grad = 0;
    for(int i=0;i< nr_vf;i++)
    {
        if(graf_copy[v][i])
        {
            grad++;
        }
        if(grad>1)
            return false;
    }
    return true;
}


void fleury(int start, int graf_copy[][MAX_V], int nr_vf)
{
    static int muchii = nr_muchii(graf_copy,nr_vf);
    for(int v=0;v<nr_vf;v++)
    {
        // daca muchia exista si nu este punte
        if(graf_copy[start][v]==1)
        {
            if(muchii<=1  || !e_punte(start,v,graf_copy,nr_vf))
            {
                cout<<start<<"--"<<v<<" ";
                // stergerea muchiei din graf
                graf_copy[start][v] = 0;
                graf_copy[v][start] = 0;

                // scaderea nr de muchii
                muchii--;

                fleury(v,graf_copy,nr_vf);
            }
        }
    }
}

int main() {
    ifstream f("2-in.txt");

    int nr_vf,nr_m;
    f>>nr_vf>>nr_m;

    int graf[MAX_V][MAX_V];
    for(int i=0;i<nr_vf;i++)
        for(int j=0;j<nr_vf;j++)
            graf[i][j]=0;


    int a,b;
    for(int i=1;i<=nr_m;i++)
    {
        f>>a>>b;
        graf[a][b]=1;
        graf[b][a]=1;
    }

    // copie graf
    int graf_copy[MAX_V][MAX_V];
    for(int i=0;i<nr_vf;i++)
        for(int j=0;j<nr_vf;j++)
            graf_copy[i][j]=graf[i][j];

    cout<<"Ciclu eulerian: ";
    fleury(cauta_nod_start(graf_copy,nr_vf),graf_copy,nr_vf);


    f.close();
    return 0;
}



//POMPARE PREFLUX

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

//pompare
struct nod{
int h=0;
int e=0;};

void pompare(int x,vector<vector<int>>& g,vector<nod>& noduri,set<int>& activ)
{
    for(int i=0;i<g.size();i++)
    {
        if(g[x][i]&&noduri[i].h==noduri[x].h-1)
        {
            int fl=min(g[x][i],noduri[x].e);
            g[x][i]-=fl;
            g[i][x]+=fl;
            noduri[x].e-=fl;
            noduri[i].e+=fl;
            activ.insert(i);
        }
    }
}

void inaltare(int x,vector<vector<int>>& g,vector<nod>& noduri)
{
    int mini=INT_MAX;
    for(int i=0;i<g.size();i++)
    {
        if(g[x][i])
        {
            mini=min(mini,noduri[i].h);
        }
        noduri[x].h=mini+1;
    }
}

int PT(int s,int d,vector<vector<int>> g)
{
    set<int> activ;
    vector<vector<int>> grez=g;
    int h=g.size();
    vector<nod> noduri(h);
    noduri[s].h=h;

    for(int i=0;i<g[s].size();i++)
    {
        if(g[s][i])
        {
            grez[i][s]=grez[s][i];
            grez[s][i]=0;
            noduri[i].e=g[s][i];
            activ.insert(i);
        }
    }

    while(!activ.empty())
    {
        int x=*activ.begin();
        activ.erase(activ.begin());
        if(x!=s&& x!=d)
        {
            while(noduri[x].e!=0)
            {
                pompare(x,grez,noduri,activ);
                inaltare(x,grez,noduri);
            }
        }
    }
    return noduri[d].e;
}

int main()
{
    int n,m,x,y,c;
    vector<vector<int>>g;
    f>>n>>m;
    for(int i=0;i<n;i++)
    {
        vector<int> linie(n);
        g.push_back(linie);
    }
    for(int i=0;i<m;i++)
    {
        f>>x>>y>>c;
        g[x][y]=c;
    }

    cout<<PT(0,g.size()-1,g);
}





//POMPARE TOPOLOGICA
#include <iostream>
#include <queue>
#include <limits.h>
#include <string.h>
#include <fstream>
#include <list>
#include <stack>
#include <vector>
#include <unordered_set>
using namespace std;

ifstream fin2("graf.in");
ofstream fout2("out2.txt");

void pompare(int** graf, int** flux, int* exces, const int u, const int v)
{
    const int delta = std::min(exces[u], graf[u][v] - flux[u][v]);
    flux[u][v] += delta;
    flux[v][u] -= delta;
    exces[u] -= delta;
    exces[v] += delta;
}

void inalta(int** graf, int** flux, int* inaltime, const int u, const int noduri)
{
    int inaltimeMin = INT_MAX;
    for (int v = 0; v < noduri; ++v)
        if (graf[u][v] - flux[u][v] > 0) // capacitate reziduala
            inaltimeMin = std::min(inaltimeMin, inaltime[v]);

    inaltime[u] = inaltimeMin + 1;
}

void descarca(int** graf, int** flux, int* inaltime, int* exces, int* curent, const int u, const int noduri)
{
    while (exces[u] > 0)
    {
        if (curent[u] == noduri) // daca nu mai avem vecini in care sa pompam
        {
            inalta(graf, flux, inaltime, u, noduri); // inaltam nodul curent
            curent[u] = 0; // resetam faptul ca am vizitat vecinii deci putem sa-i revizitam
            continue;
        }

        const int v = curent[u];
        if (graf[u][v] - flux[u][v] > 0 && inaltime[u] == inaltime[v] + 1) // daca pot sa pompez
            pompare(graf, flux, exces, u, v); // atunci pompez
        else
            ++curent[u]; // continui cu urmatorul vecin
    }
}

int pompare_topologica(int** graf, int** flux, const int sursa, const int destinatie, const int noduri)
{
    std::list<int> L;
    L.clear();

    int* inaltime = new int[noduri] {};
    int* exces = new int[noduri] {};
    int* curent = new int[noduri] {};

    inaltime[sursa] = noduri;
    exces[sursa] = INT_MAX;
    for (int v = 0; v < noduri; ++v)
    {
        if (v != sursa)
            pompare(graf, flux, exces, sursa, v); // pompez din sursa cat de mult pot vecinilor

        if (v != sursa && v != destinatie)
            L.push_back(v); // L = V \ { s, t }
    }

    std::list<int>::iterator it = L.begin();
    while (it != L.end())
    {
        int u = *it;
        int inaltime_veche = inaltime[u];

        descarca(graf, flux, inaltime, exces, curent, u, noduri);

        if (inaltime[u] > inaltime_veche)
            L.splice(L.begin(), L, it); // mut elementul si iteratorul la inceput

        ++it; // continui cu urmatorul element
    }

    int fluxMaxim = exces[destinatie];

    delete[] curent;
    delete[] exces;
    delete[] inaltime;

    return fluxMaxim;
}

int main() {
    int noduri, arce;
    fin2 >> noduri >> arce;
    int** graf = new int* [noduri] {};
    int** flux = new int* [noduri] {};
    for (int i = 0; i < noduri; ++i)
    {
        graf[i] = new int[noduri] {};
        flux[i] = new int[noduri] {};
    }
    for (int i = 0; i < arce; ++i)
    {
        int x, y, cost;
        fin2 >> x >> y >> cost;
        graf[x][y] = cost;
    }

    fout2 << pompare_topologica(graf, flux, 0, noduri - 1, noduri);

    for (int i = 0; i < noduri; ++i)
    {
        delete[] flux[i];
        delete[] graf[i];
    }
    delete[] flux;
    delete[] graf;
    fin2.close();
    fout2.close();

    return 0;

}
