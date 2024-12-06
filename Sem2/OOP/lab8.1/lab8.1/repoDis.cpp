#include"repoDis.h"
#include<cassert>


DisRepo::~DisRepo()
{

}
bool DisRepo::exist(const Disciplina& d) const {
	for (const auto& p1 : dlist) {
		if (d.getDenum() == p1.getDenum()) {
			return true;
		}
	}
	return false;
}

void DisRepo::add(const Disciplina& d) {
	if (exist(d))
	throw RepositoryExceptions("Disciplina exista deja!");
	this->dlist.push_back(d);
	
}

void DisRepo::remove(int position)
{
	
	size_t dim = dlist.size();
	if (position != dim - 1)
	{
		for (position; position < dim - 1; position++)
			dlist[position] = dlist[position + 1];
		dlist.pop_back();
	}
	else {
		dlist.pop_back();
	}
}

void DisRepo::modify(const int& position, const Disciplina& newD)
{
	//vector<Disciplina> dlist = RepoAbs::getList();
		
			dlist[position].setDenum(newD.getDenum());
			dlist[position].setOre(newD.getOre());
			dlist[position].setTip(newD.getTip());
			dlist[position].setProf(newD.getProf());
}


int DisRepo::find(const string denumire) 
{
	int i = -1, poz = -1;

	//int iterator{ -1 }, position{ -1 };

	//int dimensionStore = store.size();
	for ( auto& element : dlist) {
		i += 1;
		if (element.getDenum() == denumire) {
			
			poz = i;

		}
		
	}
	if (poz == -1)
		throw RepositoryExceptions("Nu exista disciplina cu denumirea data! ");
	return poz;
}

vector<Disciplina>& DisRepo::getList() 
{
	return dlist;
}

size_t DisRepo::size() const noexcept
{
	return dlist.size();
}



bool DictRepo::exist(const Disciplina& d) {
	for (const auto& p1 : DictRepo::getList()) {
		if (d.getDenum() == p1.getDenum()) {
			return true;
		}
	}
	return false;
}

void DictRepo::add(const Disciplina& d) {
	if(prob<0.5)
		throw (prob);
	if (exist(d))
		throw RepositoryExceptions("Disciplina exista deja!");
	this->dict[dict.size()] = d;
	}

void DictRepo::remove(int position)
{
	
	if (prob < 0.5)
		throw (prob);
	dict.erase(position);
	map<size_t, Disciplina>sec;
	sec.clear();
	for (auto& it : dict) {
		sec.insert(make_pair(sec.size(), it.second));
	}
	dict = sec;
	//throw (prob);
	}

void DictRepo::modify(const int& position, const Disciplina& newD)
{
	if (prob < 0.5)
		throw (prob);
	for (auto& it : dict) {
		if (it.first == position)
		{
			dict.erase(position);
			dict.insert(make_pair(position, newD));
			//break;
		}
	}
	//throw (prob)
	}


int DictRepo::find(const string denumire)
{
	int i = -1, poz = -1;

	//int iterator{ -1 }, position{ -1 };

	//int dimensionStore = store.size();
	for (auto& element : DictRepo::getList()) {
		i += 1;
		if (element.getDenum() == denumire) {

			poz = i;

		}

	}
	if (poz == -1)
		throw RepositoryExceptions("Nu exista disciplina cu denumirea data! ");
	return poz;
}

vector<Disciplina>& DictRepo::getList()
{
	all.clear();

	for (auto& d : dict)
	{
		all.push_back(d.second);
	}
	return all;
}


size_t DictRepo::size() const noexcept
{
	return dict.size();
}



void FileRepo::loadFromFile()
{
	std::ifstream in;
	in.open(file);
	
	while (!in.eof())
	{
		string d, t, p;
		int o;
		in >> d >> o >> t >> p;
		if (in.eof())
			break;
		Disciplina dis{ d,o,t,p};
		DisRepo::add(dis);
	}
	in.close();
}

void FileRepo::saveToFile() {
	std::ofstream out;
	out.open(file, ios::trunc);
	
	for (auto& p : DisRepo::getList())
	{
		out << p.getDenum();
		out << std::endl;
		out << p.getOre();
		out << std::endl;
		out << p.getTip();
		out << std::endl;
		out << p.getProf();
		out << std::endl;
	}
	out.close();
}

/*const vector<Disciplina>& RepoAbs::getList() const noexcept
{
	map<int, Disciplina> dict = ddict;
	vector<Disciplina> lista;

	for (auto& d : dict)
	{
		lista[d.first] = d.second;
	}
	return lista;
}

bool RepoAbs::exist(const Disciplina& d) const {
	for (const auto& p1 : RepoAbs::getList()) {
		if (d.getDenum() == p1.getDenum()) {
			return true;
		}
	}
	return false;
}


void RepoAbs::add(const Disciplina& d) {
	if (exist(d))
		throw RepositoryExceptions("Disciplina exista deja!");
	this->dlist.push_back(d);

}*/
void testRepo()
{
	Disciplina d1{ "info",4,"t1","Prof1" };
	Disciplina d2{ "infoo",4,"t2","Prof5" };
	Disciplina d3{ "infooo",4,"t1","Prof3" };
	DisRepo repo;
	repo.add(d1);
	repo.add(d2);

	assert(repo.size() == 2);
	assert(repo.getList()[0].getDenum() == d1.getDenum());
	assert(repo.getList()[0].getTip() == d1.getTip());

	
	repo.modify(0, d3);
	assert(repo.getList()[0].getDenum() == d3.getDenum());
	assert(repo.getList()[0].getTip() == d3.getTip());

	repo.remove(1);
	assert(repo.size() == 1);
	/*vector<Disciplina> dlist = repo.getList();
	for (int i = 0; i < repo.size(); i++)
		cout << dlist[i].getDenum() << " ";*/
	
	int poz = repo.find(d3.getDenum());
	
	assert(repo.getList()[poz].getDenum() == d3.getDenum());
	assert(repo.getList()[poz].getTip() == d3.getTip());
	try {
		poz = repo.find("dgfg");
	}
	catch (RepositoryExceptions& re )
	{
		assert( true);
		assert(re.getMsg()!="");
	}
	//assert(poz == -1);
	
	
}

void testRepoFile()
{

	Disciplina d1{ "info",4,"tip1","Prof1" };
	Disciplina d2{ "infoo",4,"t2","Prof5" };
	Disciplina d3{ "info",4,"t1","Prof3" };
	FileRepo repo{ "testFile.txt" };
	
	
	repo.add(d1);
	repo.add(d2);

	assert(repo.size() == 2);
	assert(repo.getList()[0].getDenum() == d1.getDenum());
	assert(repo.getList()[0].getTip() == d1.getTip());


	repo.modify(0, d3);
	assert(repo.getList()[0].getDenum() == d3.getDenum());
	assert(repo.getList()[0].getTip() == d3.getTip());

	repo.remove(1);
	assert(repo.size() == 1);
	/*vector<Disciplina> dlist = repo.getList();
	for (int i = 0; i < repo.size(); i++)
		cout << dlist[i].getDenum() << " ";*/

	int poz = repo.find(d3.getDenum());

	assert(repo.getList()[poz].getDenum() == d3.getDenum());
	assert(repo.getList()[poz].getTip() == d3.getTip());
	try {
		poz = repo.find("dgfg");
	}
	catch (RepositoryExceptions& re)
	{
		assert(true);
		assert(re.getMsg() != "");
	}
	//assert(poz == -1);
	FileRepo repo2{ "testFile2.txt" };
	repo2.getList();


}

void testDictRepo()
{

	Disciplina d1{ "info",4,"tip1","Prof1" };
	Disciplina d2{ "infoo",4,"t2","Prof5" };
	Disciplina d3{ "info",4,"t1","Prof3" };
	float p = float(0.6);
	DictRepo repo(p);

	
	repo.add(d1);
	
	try {
		repo.add(d1);
	}
	catch (...) {
		assert(true);
	}
	
	repo.add(d2);
	
	//assert(repo.size() == 1);
	assert(repo.getList()[0].getDenum() == d1.getDenum());
	assert(repo.getList()[0].getTip() == d1.getTip());

	
		repo.modify(0, d3);

	
	assert(repo.getList()[0].getDenum() == d3.getDenum());
	assert(repo.getList()[0].getTip() == d3.getTip());

	
	repo.remove(1);
	
	assert(repo.size() == 1);
	/*vector<Disciplina> dlist = repo.getList();
	for (int i = 0; i < repo.size(); i++)
		cout << dlist[i].getDenum() << " ";*/

	int poz = repo.find(d3.getDenum());

	assert(repo.getList()[poz].getDenum() == d3.getDenum());
	assert(repo.getList()[poz].getTip() == d3.getTip());
	try {
		poz = repo.find("dgfg");
	}
	catch (RepositoryExceptions& re)
	{
		assert(true);
		assert(re.getMsg() != "");
	}
	//assert(poz == -1);




}