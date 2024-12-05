#include "Export.h"
#include<cassert>


void exportToCSV(string file, const vector<Disciplina>& all)
{
	ofstream out(file, ios::trunc);
	if (!out.is_open()) {
		throw RepositoryExceptions("Nu s-a putut deschide fisierul");

	}
	for (const auto& pr : all)
	{
		out << pr.getDenum() << "," << pr.getOre() << "," << pr.getTip() << "," << pr.getProf() << endl;

	}
	out.close();
}

void exportToHTML(string file, const vector<Disciplina>& all)
{
	ofstream out;
	out.open(file, ios::trunc);
	if (!out.is_open()) {
		throw RepositoryExceptions("Nu s-a putut deschide fisierul \n" );
	}
	out << "<html><body>" << endl;
	out << "<table border=\"1\" style=\"width:100 % \">" << endl;
	for (const auto& product : all) {
		out << "<tr>" << endl;
		out << "<td>" << product.getDenum() << "</td>" << endl;
		out << "<td>" << product.getOre() << "</td>" << endl;
		out << "<td>" << product.getTip() << "</td>" << endl;
		out << "<td>" << product.getProf() << "</td>" << endl;
		out << "</tr>" << endl;
	}
	out << "</table>" << endl;
	out << "</body></html>" << endl;
	out.close();
}

void testExport()
{
	DisRepo repo;
	Disciplina dis { "infoo", 4, "t1", "Prof1" };
	repo.add(dis);
	//Validator val;
	try
	{
		exportToCSV("/test.csv", repo.getList());
	}
	catch (RepositoryExceptions&)
	{
		assert(true);
	}

	try
	{
		exportToHTML("/test.html", repo.getList());
	}
	catch (RepositoryExceptions&)
	{
		assert(true);
	}
	ofstream outCSV("test.csv", ios::trunc);
	ofstream outHTML("test.html", ios::trunc);
	exportToCSV("test.csv", repo.getList());
	exportToHTML("test.html", repo.getList());
}