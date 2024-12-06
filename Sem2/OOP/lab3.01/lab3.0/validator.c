#include<string.h>
#include<ctype.h>
#include<assert.h>

int validare(char tip[], int pret, int cant)
{
	char* tipuri[4] = { "laptop", "frigider", "televizor", "altceva" };

	int ok = 0;
	for (int i = 0; i < 4; i++)
	{

		if (strcmp(tipuri[i], tip) == 0)
			ok = 1;
	}
	if (!ok)
		return 1;

	if (pret <= 0)
	{
		return 2;


	}
	if (cant <= 0)
	{
		return 3;


	}
	return 0;
}

void testVal()
{
	assert(validare("televizo",  100, 20) == 1);
	assert(validare("televizor",  -100, 20) == 2);
	assert(validare("televizor",  100, -20) == 3);
	assert(validare("televizor",  100, 20) == 0);
}