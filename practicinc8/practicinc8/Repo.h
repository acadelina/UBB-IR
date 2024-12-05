#pragma once
#include"Domain.h"
#include<vector>

class Repo{
	vector<Melodie> mel;
	string filename;
	void load();
	void save();
public:
	Repo(string filename) :filename{ filename } {
		load();
	}
	/*
	Functie care modifica titlul si rankul unei melodii
	prec: id-int
		  titlu-string
		  rank-int
	*/
	void modif(int id, string titlu, int rank);
	/*
	Functie care sterger o mel dupa id
	prec: id-int
	*/
	void del(int id);
	/*
	Functie care cauta pozitia unei melodii dupa id
	prec: id-int
	postc: poz-int
	*/
	int cauta(int id);

	vector<Melodie> getAll();


};

/*
3,titlu3,artist3,9
4,titlu8,artist4,1
5,titlu3,artist5,3
*/
void testRepo();