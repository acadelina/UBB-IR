#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<map>
#include<queue>
#include <algorithm>
class Nod {
public:
    Nod() {
        this->stang = nullptr;
        this->drept = nullptr;
        this->caracter = 0;
        this->frecventa = 0;
    };
    Nod* stang;
    Nod* drept;
    int frecventa;
    std::vector<char> lista_caractere;
    char caracter;
};
std::string textul_initial;
struct ComparaFrecv {
    bool operator()(Nod* const& nod1, Nod* const& nod2)
    {

        if (nod1->frecventa == nod2->frecventa) {
            return *std::min_element(nod1->lista_caractere.begin(), nod1->lista_caractere.end()) >
                *std::min_element(nod2->lista_caractere.begin(), nod2->lista_caractere.end());
               }

        return nod1->frecventa > nod2->frecventa;
    }
};


std::map<char, int> legenda;

std::priority_queue<Nod*, std::vector<Nod*>, ComparaFrecv> priorityQueue;

std::string citire();
int main();
std::string decodare_huffman(const std::string& text_de_decodat, Nod* varf);
Nod* creare_arbore();
void afisare_arbore(Nod* varf);

int main() {
    auto text_citit = citire();
    textul_initial = text_citit;

    auto varf = creare_arbore();        //asta ii varful;
    auto rezultat = decodare_huffman(text_citit, varf);

    std::cout << rezultat << '\n';
}

std::string citire() {
    std::ifstream fin("in.txt");
    std::string text;
    int nr;
    fin >> nr;
    char c;
    int frecv;
    while (nr > 0) {
        fin.get(c); //citim spatiul liber de la final
        fin.get(c);
        fin >> frecv;
        legenda[c] = frecv;
        nr--;
    }
    fin >> text;
    return text;
}

Nod* creare_arbore() {
    for (auto it : legenda) {
        auto nod_nou = new Nod{};
        nod_nou->caracter = it.first;
        nod_nou->frecventa = it.second;
        nod_nou->lista_caractere.push_back(it.first);
        priorityQueue.push(nod_nou);
    }
    auto n = legenda.size();
    for (auto i = 1; i < n; ++i) {
        auto z = new Nod{};
        auto x = priorityQueue.top();
        priorityQueue.pop();
        auto y = priorityQueue.top();
        priorityQueue.pop();
        z->stang = x;
        z->drept = y;
        z->frecventa = x->frecventa + y->frecventa;
        z->lista_caractere.insert(z->lista_caractere.end(), x->lista_caractere.begin(), x->lista_caractere.end());
        z->lista_caractere.insert(z->lista_caractere.end(), y->lista_caractere.begin(), y->lista_caractere.end());
        //        std::sort(z->lista_caractere.begin(), z->lista_caractere.end(), [](char a, char b){return a < b;});
        priorityQueue.push(z);
    }
    return priorityQueue.top();
}

std::string decodare_huffman(const std::string& text_de_decodat, Nod* varf) {
    auto i = 0;
    std::string rez_final;
    while (i < text_de_decodat.length()) {
        auto parcurs = varf;
        auto c = text_de_decodat[i];
        while (parcurs->drept != nullptr) {
            if (c == '0') {
                parcurs = parcurs->stang;
            }
            else
                parcurs = parcurs->drept;
            i++;
            c = text_de_decodat[i];
        }
        auto x = parcurs->caracter;
        rez_final += x;
        //        i++;
    }
    return rez_final;
}




