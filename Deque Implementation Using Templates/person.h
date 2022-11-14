#pragma once
#include <iostream>
#include <string.h>
#include <conio.h>
#include <cstdio>

using namespace::std;

class Person
{
	string name;
public:
	Person(string arg = "")
		: name(arg) {}
	Person(int a)
		: name("") {}

	void operator=(int arg);
	void operator=(string arg);


	friend ostream& operator<<(ostream& out, const Person& arg);
};

