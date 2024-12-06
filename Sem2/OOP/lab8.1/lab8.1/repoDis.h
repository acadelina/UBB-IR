#pragma once
#include"disciplina.h"
#include<vector>
#include<string>
#include<functional>
#include<fstream>
#include<map>
using namespace std;

class RepoAbs {

public:
	

	virtual void add(const Disciplina& d)=0;

	/*
	Modificare disciplina
	precoond: position->int
			  newD->disciplina
	*/
	virtual void modify(const int& position, const Disciplina& newD)=0;

	/*
	Sterge disciplina
	precond: position->int
	*/
	virtual void remove(int position)=0;

	/*
	Cauta disciplina
	precond: denumire->str
	postc: poz->int
	*/
	virtual int find(const string denumire)=0;

	/*
	Lista disciplinelor
	precond:
	postcond: lista
	*/
	virtual vector<Disciplina>& getList() =0;

	/*
	Dimensiunea listei
	preconditii:
	postconditii: dim->int
	*/
	virtual size_t size() const noexcept=0;

	virtual ~RepoAbs()=default;
};

class DictRepo:public RepoAbs {
private:
	float prob;
	map<size_t, Disciplina> dict;
	//void det_luck();
	bool exist(const Disciplina& d);
	//int prob=0;
	//vector<Disciplina> dlist;

public:
	DictRepo()=default ;
	DictRepo(float probabil) : prob(probabil) {};

	DictRepo(const DictRepo& o) = delete;
	//bool exist(const Disciplina& d) const;
	/*
	Adaugare disciplina
	precond: d->disciplina
	*/

	void add(const Disciplina& d) override;

	/*
	Modificare disciplina
	precoond: position->int
			  newD->disciplina
	*/
	void modify(const int& position, const Disciplina& newD) override;

	/*
	Sterge disciplina
	precond: position->int
	*/
	void remove(int position) override;

	/*
	Cauta disciplina
	precond: denumire->str
	postc: poz->int
	*/
	int find(const string denumire) override;

	/*
	Lista disciplinelor
	precond:
	postcond: lista
	*/
	vector<Disciplina> all;
	vector<Disciplina>& getList() override;


	
	/*
	Dimensiunea listei
	preconditii:
	postconditii: dim->int
	*/
	size_t size() const noexcept override;

	~DictRepo() = default;
};

class DisRepo :public RepoAbs {
private:
	vector<Disciplina> dlist;
	bool exist(const Disciplina& d) const ;
public:
	DisRepo()=default;
	DisRepo(const DisRepo& d) = delete;

	
	/*
	Adaugare disciplina
	precond: d->disciplina
	*/

	virtual void add(const Disciplina& d) override;

	/*
	Modificare disciplina
	precoond: position->int
			  newD->disciplina
	*/
	virtual void modify(const int& position, const Disciplina& newD) override;

	/*
	Sterge disciplina
	precond: position->int
	*/
	virtual void remove(int position) override;

	/*
	Cauta disciplina
	precond: denumire->str
	postc: poz->int
	*/
	int find(const string denumire) override ;

	/*
	Lista disciplinelor
	precond:
	postcond: lista
	*/
	vector<Disciplina>& getList() override;

	/*
	Dimensiunea listei
	preconditii:
	postconditii: dim->int
	*/
	size_t size() const noexcept override;

	virtual ~DisRepo();
};

class RepositoryExceptions {
	string mesage;
public:

	RepositoryExceptions(string msg) : mesage{ msg } {}

	string getMsg() { return this->mesage; }

};

class FileRepo :public DisRepo {
private:
	void loadFromFile();
	void saveToFile();
	string file;
	void clearFile() {
		ofstream f(file, ios::trunc);
		f.close();
	}
public:
	FileRepo(string file) :DisRepo(), file{ file } {
		loadFromFile();//incarcam datele din fisier
	}
	void add(const Disciplina& d) override {
		DisRepo::add(d);
		saveToFile();
	}
	void modify(const int& position, const Disciplina& newD)override {
		DisRepo::modify(position, newD);
		saveToFile();
	}
	void remove(int poz) override {
		DisRepo::remove(poz);
		saveToFile();
	}
};


void testRepo();
void testRepoFile();
void testDictRepo();