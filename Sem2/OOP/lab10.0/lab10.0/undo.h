#pragma once
#include"disciplina.h"
#include"repoDis.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	//destructorul 
	virtual ~ActiuneUndo() = default;
};

class UndoAdd :public ActiuneUndo {
	Disciplina dis;
	RepoAbs& rep;
public:
	UndoAdd(const Disciplina& d, RepoAbs& rep) :rep{ rep }, dis{ d } {}
	void doUndo()override {
		int poz = rep.find(dis.getDenum());
		rep.remove(poz);
	}
};

class UndoRemove :public ActiuneUndo {
	Disciplina dis;
	RepoAbs& rep;
public:
	UndoRemove(const Disciplina& d, RepoAbs& rep) :rep{ rep }, dis{ d } {}
	void doUndo()override {
		rep.add(dis);
	}
};

class UndoModif :public ActiuneUndo {
	Disciplina dis;
	RepoAbs& rep;
public:
	UndoModif(const Disciplina& d, RepoAbs& rep) :rep{ rep }, dis{ d } {}
	void doUndo()override {
		int poz = rep.find(dis.getDenum());
		cout << poz;
		rep.modify(poz, dis);
	}
};