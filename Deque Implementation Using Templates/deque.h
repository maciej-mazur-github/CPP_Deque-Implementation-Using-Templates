#pragma once
#include <iostream>
#include <string.h>
#include <conio.h>
#include <cstdio>
using namespace std;



template <class T, int arraySize>
class Deque;

template <class T, int arraySize>
ostream& operator<<(ostream& out, Deque<T, arraySize>& arg);



template <class T, int arraySize>
class Deque
{
	enum ArrayDirection {rightWiseExpandable, leftWiseExpandable};

	struct Node
	{
		Node* nextNodePtr;
		Node* previousNodePtr;
		int chosenPosition;
		T* arrayPtr;
		int arrayDirection = rightWiseExpandable; // 0 means it is expanding right-hand side, 1 means left-hand side
		int arrayItemsCounter;

		Node(ArrayDirection arrayDirection = rightWiseExpandable)
		{
			nextNodePtr = previousNodePtr = nullptr;
			chosenPosition = arrayItemsCounter = 0;
			arrayPtr = new T[arraySize];

			for (int i = 0; i < arraySize; i++)
			{
				arrayPtr[i] = nullptr;
			}
		}
	};
};