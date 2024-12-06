#include"repo.h"
#include<cassert>

void DisRepo::add(const Disciplina& d) {
	
	dlist.add(d);
}

void DisRepo::remove(const int& position)
{
	dlist.remove(position);
}

void DisRepo::modify(const int& position, const Disciplina& newD)
{
	dlist.set(position,newD);
}

int DisRepo::find(const string& denumire) const
{
	for (int i = 0; i < int(dlist.size()); i++)
		if (dlist.get(i).getDenum() == denumire)
			return i;
	return -1;
}

const Myvector<Disciplina>& DisRepo::getList() const noexcept
{
	return dlist;
}

 size_t DisRepo::size() const noexcept
{
	return dlist.size();
}

void testRepo()
{
	Disciplina d1{ "info",4,"t1","Prof1" };
	Disciplina d2{ "infoo",4,"t2","Prof5" };
	Disciplina d3{ "infooo",4,"t1","Prof3" };
	DisRepo repo;
	repo.add(d1);
	repo.add(d2);

	assert(repo.size() == 2);
	assert(repo.getList().get(0).getDenum() == d1.getDenum());
	assert(repo.getList().get(0).getTip() == d1.getTip());

	repo.modify(0, d3);
	assert(repo.getList().get(0).getDenum() == d3.getDenum());
	assert(repo.getList().get(0).getTip() == d3.getTip());

	repo.remove(1);
	assert(repo.size() == 1);

	int poz = repo.find(d3.getDenum());
	assert(repo.getList().get(poz).getDenum() == d3.getDenum());
	assert(repo.getList().get(poz).getTip() == d3.getTip());

	poz = repo.find("dgfg");
	assert(poz == -1);
}