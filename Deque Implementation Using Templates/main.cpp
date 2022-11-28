#include <iostream>
#include <string.h>
#include <conio.h>
#include <cstdio>
#include "deque.h"
#include "person.h"
using namespace std;



int main()
{
	Deque<int, 3> intDeque;
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	int f = 6;
	int g = 7;
	int h = 99;

	//intDeque.pushBack(a);
	//intDeque.pushBack(b);
	//intDeque.pushBack(c);
	//intDeque.pushBack(d);
	//intDeque.pushBack(e);
	//intDeque.pushBack(f);
	//intDeque.pushBack(g);

	intDeque.removeChosenElement();
	cout << "Some pause message\n";

	intDeque.pushFront(a);
	intDeque.pushBack(b);
	intDeque.pushFront(c);
	intDeque.pushBack(d);
	intDeque.pushFront(e);
	intDeque.pushBack(f);
	intDeque.pushFront(g);

	cout << intDeque;
	intDeque.removeChosenElement();
	cout << endl;

	intDeque.setChosenElementIndex(7);
	//intDeque.removeChosenElement();
	intDeque.insertElement(h);
	cout << intDeque;

	intDeque.setChosenElementIndex(5);
	intDeque.printCurrentChosenElementLocation();

	try
	{
		cout << intDeque.returnChosenElement();
	}
	catch (const char* msg)
	{
		cerr << msg << endl;
	}

	try
	{
		intDeque.popBack();
		intDeque.popFront();
		intDeque.popBack();
		intDeque.popFront();
		intDeque.popBack();
		intDeque.popFront();
		intDeque.popBack();
		//intDeque.popFront();
	}
	catch (const char* msg)
	{
		cerr << msg << endl;
	}
	cout << intDeque;
	cout << endl;

	/*intDeque.popFront();
	intDeque.popFront();
	intDeque.popFront();
	intDeque.popFront();
	intDeque.popFront();
	intDeque.popFront();

	cout << intDeque;
	cout << endl;*/

	

	/*intDeque.popFront();
	intDeque.popFront();
	intDeque.popFront();
	intDeque.popFront();
	intDeque.popFront();
	intDeque.popFront();
	intDeque.popFront();
	cout << intDeque;*/
	try
	{
		cout << intDeque.returnChosenElement();
	}
	catch(const char* msg)
	{
		cerr << msg << endl;
	}



	Deque<string, 4> stringDeque;
	string string1 = "word1";
	string string2 = "word2";
	string string3 = "word3";
	string string4 = "word4";
	string string5 = "word5";
	string string6 = "word6";
	string string7 = "word7";

	stringDeque.pushBack(string1);
	stringDeque.pushFront(string2);
	stringDeque.pushBack(string3);
	stringDeque.pushFront(string4);
	stringDeque.pushBack(string5);
	stringDeque.pushFront(string6);
	stringDeque.pushBack(string7);

	cout << stringDeque;



	Deque<Person, 5> personDeque;
	Person person1("Peter");
	Person person2("John");
	Person person3("Alan");
	Person person4("Nelly");
	Person person5("Linda");
	Person person6("Joyce");
	Person person7("Cecille");

	personDeque.pushFront(person1);
	personDeque.pushBack(person2);
	personDeque.pushFront(person3);
	personDeque.pushBack(person4);
	personDeque.pushFront(person5);
	personDeque.pushBack(person6);
	personDeque.pushFront(person7);

	cout << personDeque;

	personDeque.popBack();
	personDeque.popFront();
	cout << personDeque;
}