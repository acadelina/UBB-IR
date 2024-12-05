#pragma once
#include "Disciplina.h"
#include "repoDis.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::endl;

//exporta o lista de discipline intr-un fis csv
void exportToCSV(string file, const vector<Disciplina>& all);

//exporta o lista de discipline intr-un fis html
void exportToHTML(string file, const vector<Disciplina>& all);

void testExport();