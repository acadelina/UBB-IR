#include "validator.h"
#include"disciplina.h"
#include<ctype.h>
#include<cassert>
#include<vector>


void testValidare()
{
	Validator val;

	try {
		val.validare("abc3", 10, "tt", "prof");
	}
	catch (ValidationExceptions& ve)
	{
		assert(true);
		assert(ve.get_msj() != "");
		//assert(vex.get_msj() != NULL);
	}

	try {
		val.validare("abc", -10, "tt", "prof");
	}
	catch (ValidationExceptions& ve)
	{
		assert(true);
		assert(ve.get_msj() != "");
	}


	try {
		val.validare("abc", 10, "tt", "prof");
	}
	catch (ValidationExceptions& ve)
	{
		assert(true);
		assert(&ve != NULL);
	}

	val.validare("abc", 10, "tt", "Prof");
}