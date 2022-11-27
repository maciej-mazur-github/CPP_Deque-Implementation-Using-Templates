#include <iostream>
#include <string.h>
#include <conio.h>
#include <cstdio>
#include "deque.h"
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

	//intDeque.pushBack(a);
	//intDeque.pushBack(b);
	//intDeque.pushBack(c);
	//intDeque.pushBack(d);
	//intDeque.pushBack(e);
	//intDeque.pushBack(f);
	//intDeque.pushBack(g);

	intDeque.pushFront(a);
	intDeque.pushFront(b);
	intDeque.pushFront(c);
	intDeque.pushFront(d);
	intDeque.pushFront(e);
	intDeque.pushFront(f);
	intDeque.pushFront(g);
	intDeque.popFront();
	intDeque.popFront();
	intDeque.popFront();
	intDeque.popFront();
	intDeque.popFront();
	intDeque.popFront();
	intDeque.popFront();

	cout << intDeque;
	cout << endl;

	/*try
	{
		intDeque.popBack();
		intDeque.popBack();
		intDeque.popBack();
		intDeque.popBack();
		intDeque.popBack();
		intDeque.popBack();
		intDeque.popBack();
		intDeque.popBack();
	}
	catch(const char* msg)
	{
		cerr << msg << endl;
	}*/

	intDeque.popFront();
	intDeque.popFront();
	intDeque.popFront();
	intDeque.popFront();
	intDeque.popFront();
	intDeque.popFront();
	intDeque.popFront();
	cout << intDeque;
	cout << "\nEnd message";
}