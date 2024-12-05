#include "validator.h"
#include"disciplina.h"
#include<ctype.h>
#include<cassert>

int validare(string denum, int ore, string tip, string prof)
{
	if (ore < 0)
		return 0;
	for (size_t i = 0; i < denum.size(); i++)
		if (isdigit(denum.at(i)))
			return 0;
	/*for (size_t i = 0; i < prof.size(); i++)
		if (isdigit(prof.at(i)));
			//return 0;*/
	if(isupper(prof.at(0))==0)
		return 0;
	return 1;

}

void testVal()
{
	assert(validare("abc3", 10, "tt", "prof") == 0);

	assert(validare("abc", -10, "tt", "prof") == 0);

	assert(validare("abc", 10, "tt", "prof") == 0);

	assert(validare("abc", 10, "tt", "Prof") == 1);
}