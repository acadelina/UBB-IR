#include"Repo.h"
#include<sstream>
void FileRepo::load()
{
	ifstream fin(filename);
	string line;
	while (getline(fin, line))
	{
		if (line.empty())
			continue;
		auto ss = stringstream(line);
		vector<string> prod;
		string p;
		while (getline(ss, p, ';'))
		{
			prod.push_back(p);
		}
		auto P = Produs(stoi(prod[0]), prod[1], prod[2], stoi(prod[3]), prod[4]);
		add(P);
	}
}

void FileRepo::save()
{
	ofstream fout(filename);
	for (auto& p : produse)
	{
		fout << p.getId() << ";" << p.getNume() << ";" << p.getTip() << ";" << p.getPret() << ";" << p.getProd() << "\n";
	}
}

bool FileRepo::validareId(int id)
{
	for (auto& p : produse)
	{
		if (p.getId() == id)
			return false;
	}
	return true;
}

void FileRepo::add(Produs& p)
{
	if (!validareId(p.getId()))
		throw RepoExceptions("Id existent!");
	produse.push_back(p);
	save();
}

void FileRepo::modifica(int pos, Produs& p)
{
	produse[pos].setNume(p.getNume());
	produse[pos].setPret(p.getPret());
	produse[pos].setProd(p.getProd());
	produse[pos].setTip(p.getTip());
	save();
}

void FileRepo::sterge(int pos)
{
	size_t dim = produse.size();
	if (pos != dim - 1)
	{
		for (pos; pos < dim - 1; pos++)
			produse[pos] = produse[pos + 1];
		produse.pop_back();
	}
	else
		produse.pop_back();
	save();
}

int FileRepo::cauta(Produs& p)
{
	int poz = -1;
	for (int i = 0; i < produse.size(); i++)
		if (produse[i].getId() == p.getId())
		{
			poz = i;
			break;
		}
	if (poz == -1)
		throw RepoExceptions("Nu exista produsul cautat!");
	return poz;

}
vector<Produs>& FileRepo::getAll()
{
	return produse;
}