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

	Node* firstNodePtr;
	Node* lastNodePtr;
	Node* chosenNodePtr;
	int numberOfNodes;
	int numberOfElements;

public:
	Deque()
	{
		firstNodePtr = lastNodePtr = chosenNodePtr = nullptr;
		numberOfNodes = 0;
	}

	~Deque();

	void pushFront(T& arg);
	void pushBack(T& arg);
	T popBack();
	T popFront();
	void setChosenNode(int nodeNumber);
	void printChosenNodeArray();
	void removeChosenElement();
	void addElement(T& addedElement);
	T& returnChosenElement(int index);
	void setChosenElementIndex(int index);

	friend ostream& operator<< <T, arraySize> (ostream& out, Deque& arg);

private:
	void gotoNext_node();
	void addLeftWiseNode();
	void addRightWiseNode();
	//void remove_remaining_node();    // remove the one and only node from dequeue (1-node deck)
	void removeLastNode();   // remove the far right node
	void removeFirstNode();
	void shiftElementsRight();
	void shiftElementsLeft();
};


template <class T, int arraySize>
Deque<T, arraySize>::~Deque()
{
	if (!firstNodePtr)     // if Deque is empty
		return;

	while (lastNodePtr)
	{
		removeLastNode();
	}
}


template <class T, int arraySize>
void Deque<T, arraySize>::pushBack(T& arg)
{
	if (!firstNodePtr || lastNodePtr->arrayDirection == leftWiseExpandable || (lastNodePtr->arrayDirection == rightWiseExpandable && lastNodePtr->arrayItemsCounter == arraySize))   // when Deque is empty or it only contains leftwise expandable node arrays, or when its last node array is rightwise expandable but it is full and therefore Deque needs an expansion by another rightwise expandable node array to contain the newly pushed element
	{
		addRightWiseNode();
		lastNodePtr[0] = arg;    // after expanding Deque by another rightwise expandable node array the newly pushed back element will be placed at [0] position
	}
	else
	{
		int position = lastNodePtr->arrayItemsCounter;
		lastNodePtr[position] = arg;
	}

	return;
}


template <class T, int arraySize>
void Deque<T, arraySize>::pushFront(T& arg)
{
	if (!firstNodePtr || firstNodePtr->arrayDirection == rightWiseExpandable || (firstNodePtr->arrayDirection == leftWiseExpandable && firstNodePtr->arrayItemsCounter == arraySize))   // analogous to pushBack(T& arg) start
	{
		addLeftWiseNode();
		firstNodePtr[arraySize - 1] = arg;
	}
	else
	{
		int position = arraySize - firstNodePtr->arrayItemsCounter - 1;
		firstNodePtr[position] = arg;
	}
}


template <class T, int arraySize>
void Deque<T, arraySize>::addLeftWiseNode()
{
	Node* newNodePtr = new Node();    // default constructor argument value is rightWiseExpandable

	if (!firstNodePtr)              // if Deque was empty the newly added node has to become either the first and the last node
	{
		firstNodePtr = lastNodePtr = newNodePtr;
	}
	else
	{
		firstNodePtr->previousNodePtr = newNodePtr;
		newNodePtr->nextNodePtr = firstNodePtr;
		firstNodePtr = newNodePtr;
	}
}


template <class T, int arraySize>
void Deque<T, arraySize>::addRightWiseNode()
{
	Node* newNodePtr = new Node();    // default constructor argument value is rightWiseExpandable

	if (!firstNodePtr)              // if Deque was empty the newly added node has to become either the first and the last node
	{
		firstNodePtr = lastNodePtr = newNodePtr;
	}
	else
	{
		lastNodePtr->nextNodePtr = newNodePtr;
		newNodePtr->previousNodePtr = lastNodePtr;
		lastNodePtr = newNodePtr;
	}
}

