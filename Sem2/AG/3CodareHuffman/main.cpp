#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>

using namespace std;
ifstream f("in.txt");
// structura nod
struct Node{
    char litera;
    int frecv;
    Node *stg,*dreapta;
};

// alocare nod nou
Node* alocaNod(char ch, int frecv,Node* stg,Node* dreapta)
{
    Node* nod = new Node();

    nod->litera=ch;
    nod->frecv=frecv;
    nod->stg=stg;
    nod->dreapta=dreapta;

    return nod;
}

// functie de comparare
// ordinea: frecventa(in caz de egalitate litera cu cod ASCII mai mic)
struct comp{
    bool operator()(Node* nod1,Node* nod2)
    {
        if(nod1->frecv == nod2->frecv)
        {
            return nod1->litera > nod2->litera;
        }
        return nod1->frecv > nod2->frecv;
    }
};

// codare
// traversarea arborelui si stocarea codurilor intr-un dictionar
void encode(Node* radacina, string str, unordered_map<char,string> &huffmanCode)
{
    if(radacina== nullptr) // am ajuns la capatul arborelui
        return;

    // am gasit o frunza
    if(radacina->stg == nullptr && radacina->dreapta == nullptr)
    {
        huffmanCode[radacina->litera] = str;
    }

    encode(radacina->stg,str+"0",huffmanCode);
    encode(radacina->dreapta,str+"1",huffmanCode);
}



void buildHuffmanTree(char data[],int frecv[], int nr_caract,string text)
{
    // coada de prioritati cu nodurile ordonate dupa frecventa
    priority_queue<Node*, vector<Node*>,comp> pq;

    // crearea unui nod frunza pentru fiecare caracter si adaugarea acestuia in pq
    for(int i=0;i<nr_caract;i++)
    {
        Node* n = alocaNod(data[i],frecv[i], nullptr, nullptr);
        pq.push(n);
    }

    while(pq.size()!=1)
    {
        // extragerea vf cu frecv minima din coada de prioritati
        Node* left =pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();



        // suma frecventelor minime
        int sum=left->frecv + right->frecv;

        // alocarea unui nou nod parinte
        // acest nod are ca si copii pe cele 2 noduri
        // extrase mai sus
        Node* z= alocaNod('\0',sum,left,right);

        pq.push(z);
    }

    // radacina arborelui
    Node* radacina = pq.top();

    // traversarea arborelui si construirea codului Huffman
    unordered_map<char,string> huffmanCode;
    encode(radacina,"",huffmanCode);

    cout<<"Codurile Huffman sunt pentru fiecare litera:\n";
    for(auto pair:huffmanCode){
        cout<<pair.first<<" "<<pair.second<<endl;
    }

    cout<<"Codul lui Huffman: ";
    string str = "";
    for(char ch:text)
    {
        str+=huffmanCode[ch];
    }
    cout<<str<<endl;


    }





int citire(char data[],int frecv[],string &text)
{

    int fr[256]={0};

    // citirea unui singur caracter
    char c;

    while(!f.eof())
    {
        f.get(c);
        fr[c]++;
        text+=c;
    }
    fr[c]--; // ultimul caract este citit de 2 ori
    fr[c]--;
    text[text.size()-1]='\0';
//    cout<<text;


    int j=0,nr_caract=0;
    for(int i=0;i<256;i++)
    {
        if(fr[i]!=0)
        {
            data[j] = char(i);
            frecv[j] = fr[i];
            nr_caract++;
            j++;
            //cout<<char(i)<<" "<<fr[i]<<endl;
        }
    }
    f.close();

    return nr_caract;

}

void afisare(char data[],int frecv[],int nr_caract)
{
    cout<<nr_caract<<endl;
    for(int i=0;i<nr_caract;i++)
    {
        cout<<data[i]<<" "<<frecv[i]<<endl;
    }
}

int main() {
    char data[256];
    int frecv[256]={0};
    int nr_caract;
    string text;
    nr_caract=citire(data,frecv,text);
    afisare(data,frecv,nr_caract);

    buildHuffmanTree(data,frecv,nr_caract,text);
    return 0;
}
