#include "console.h"
#include "disciplina.h"
#include"Myvector.h"
#include<iostream>
#include<string>
using namespace std;

void DisConsole::printAll(const Myvector < Disciplina>& dList)
{
	cout << "Lista curenta de discipline: \n";
	for (int i = 0; i < dList.size(); i++)
		cout << i << ".Denumire: " << dList.get(i).getDenum() << " Nr. ore: " << dList.get(i).getOre() << " Tip: " << dList.get(i).getTip() << " Profesor: " << dList.get(i).getProf() << "\n";

}

void DisConsole::printMeniu()
{
	cout << "MENIU:\n";
	cout << "1. Adauga disciplina\n";
	cout << "2. Modifica disciplina\n";
	cout << "3. Sterge disciplina\n";
	cout << "4. Cauta disciplina\n";
	cout << "5. Afisare discipline\n";
	cout << "6.Filtrare\n";
	cout << "7.Sortare\n";
	cout << "0. Iesire\n";
}

void DisConsole::addDisUI()
{
	string d, t, p;
	int o;
	cout << "Introduceti denumirea disciplinei: ";
	cin >> d;
	cout << "\nIntroduceti numarul de  ore: ";
	cin >> o;
	cout << "\nIntroduceti tipul disciplinei: ";
	cin >> t;
	cout << "\nIntroduceti profesorul: ";
	cin >> p;
	try
	{
		serv.addDis(d, o, t, p);
		cout << "Disciplina adaugata cu succes!\n";
	}
	catch (const int errCode)
	{
		if (errCode == 1)
			cout << "Disciplina deja existenta\n";
		else
			cout << "Date invalide!";
	}
	
}
	

void DisConsole::modifDisUI()
{
	string dv, d, t, p;
	int o;
	cout << "Introduceti denumirea disciplinei: ";
	cin >> dv;
	cout << "\nIntroduceti denumirea noua a disciplinei: ";
	cin >> d;
	cout << "\nIntroduceti numarul nou de  ore: ";
	cin >> o;
	cout << "\nIntroduceti tipul nou al disciplinei: ";
	cin >> t;
	cout << "\nIntroduceti profesorul nou: ";
	cin >> p;
	serv.modifyDis(dv, d, o, t, p);
	cout << "Disciplina a fost modificata cu succes!\n";
}

void DisConsole::printDis(Disciplina dis)
{
	cout << ".Denumire: " << dis.getDenum() << " Nr. ore: " << dis.getOre() << " Tip: " << dis.getTip() << " Profesor: " << dis.getProf() << "\n";
}

void DisConsole::findDisUI()
{
	string d;
	//Disciplina dis{ "",0,"","" };
	cout << "Introduceti denumirea disciplinei cautate: ";
	cin >> d;

	cout << "Disciplina cautata: \n";
	printDis(serv.findDis(d));
	//cout <<".Denumire: " << dis.getDenum() << " Nr. ore: " << dis.getOre() << " Tip: " << dis.getTip() << " Profesor: " << dis.getProf() << "\n";
	
}

void DisConsole::removeDisUI()
{
	string d;
	cout << "Introduceti denumirea disciplinei: ";
	cin >> d;
	serv.removeDis(d);
}

void DisConsole::filterDisUI()
{
	
	int field;
	cout << "Filtrare dupa nr. de ore(0)/cadru didactic(1): ";
	cin >> field;
	
	if (field == 0)
	{
		int ore;
		cout << "Dati nr de ore: ";
		cin >> ore;
		try
		{
			Myvector<Disciplina> fl = serv.filtrareOre(ore);
			cout << "Lista filtrate: \n";
			printAll(fl);
		}


		catch (...)
		{
			cout << "Nu exista discipline cu acest numar de ore!";
		}
	}
	else if (field == 1)
	{
		string ore;
		cout << "Dati cadrul didactic: ";
		cin >> ore;
		try
		{
			Myvector<Disciplina> fl = serv.filtrareCD(ore);
			cout << "Lista filtrate: \n";
			printAll(fl);
		}


		catch (...)
		{
			cout << "Nu exista discipline cu acest cadru didactic!";
		}
	}
	else
		cout << "Comanda invalida!";


}

void DisConsole::sortare()
{
	int field,ord;
	cout << "Sortaree dupa denumire(0)/nr ore(1)/prof+tip(2): ";
	cin >> field;
	cout << "Crescator(0)/Descrescator(1): ";
	cin >> ord;
	if (field == 0)
	{
		
		try
		{
			Myvector<Disciplina> fl = serv.sortByDenum(ord);
			cout << "Lista ordonata: \n";
			printAll(fl);
		}


		catch (...)
		{
			cout << "Ordinea sortarii invalide!\n";
		}
	}
	else if (field == 1)
	{
		
		try
		{
			Myvector<Disciplina> fl = serv.sortByOre(ord);
			cout << "Lista filtrate: \n";
			printAll(fl);
		}


		catch (...)
		{
			cout << "Ordinea sortarii invalide!\n";
		}
	}
	else if (field == 2)
	{

		try
		{
			Myvector<Disciplina> fl = serv.sortByPT(ord);
			cout << "Lista filtrate: \n";
			printAll(fl);
		}


		catch (...)
		{
			cout << "Ordinea sortarii invalide!\n";
		}
	}
	else
		cout << "Comanda invalida!";
}
void DisConsole::start()
{
	int cmd;
	while (true)
	{
		printMeniu();
		cin >> cmd;
		if (cmd == 1)
		{
			addDisUI();
		}
		else if (cmd == 2)
		{
			modifDisUI();
		}
		else if (cmd == 3)
		{
			removeDisUI();
		}
		else if (cmd == 4)
		{
			findDisUI();
		}
		else if (cmd == 5)
		{
			printAll(serv.getDList());
		}
		else if (cmd == 6)
		{
			filterDisUI();
		}
		else if (cmd == 7)
		{
			sortare();
		}
		else if(cmd==0)
		{
			break;
		}
		else
		{
			cout << "Comanda invalida!\n";
		}

	}
}