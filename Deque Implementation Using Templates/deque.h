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
	void setChosenNode(int nodeNumber);
	void printChosenNodeArray();
	T popBack();
	T popFront();
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