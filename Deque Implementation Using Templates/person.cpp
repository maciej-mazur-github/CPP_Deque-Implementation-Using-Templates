#include "person.h"


void Person::operator=(int arg) { name = ""; }
void Person::operator=(string arg) { name = arg; }

ostream& operator<<(ostream& out, const Person& arg)
{
	out << arg.name;
	return out;
}