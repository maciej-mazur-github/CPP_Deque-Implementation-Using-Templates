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
	void removeChosenElement();
	void addElement(T& addedElement);
	T& returnChosenElement(int index);
	void setChosenElementIndex(int index);

	//friend ostream& operator<< <T, tab_size> (ostream& out, deck& arg);
	friend ostream& operator<< <T, arraySize> (ostream& out, Deque& arg);

private:
	void gotoNext_node();
	void addLeftWiseNode();
	void addRightWiseNode();
	//void remove_remaining_node();    // remove the one and only node from dequeue (1-node deck)
	void removeLastNode();   // remove the far right node
	void removeFirstNode();
	void shiftElementsRightForInsertion(Node* startNode, int startPosition);
	void shiftElementsLeftForInsertion(Node* startNode, int startPosition);
	void shiftElementsRightForRemoval(Node* startNode, int startPosition);    
	void shiftElementsLeftForRemoval(Node* startNode, int startPosition);
	void printChosenNodeArray();
};



template <class T, int arraySize>
T Deque<T, arraySize>::popBack()
{
	if (!lastNodePtr)
	{
		return nullptr;
	}

	T returnedValue = nullptr;

	if (lastNodePtr->arrayItemsCounter == 1)
	{
		if (lastNodePtr->arrayDirection == leftWiseExpandable)
		{
			returnedValue = lastNodePtr[arraySize - 1];
		}
		else
		{
			returnedValue = lastNodePtr[0];
		}


		if (lastNodePtr == firstNodePtr)   // if Deque contains one node array only, so after popping its last element this only one node should be removed, which actually is a deletion of Deque, hence the destructor will be called
		{
			this->~Deque();
			return returnedValue;
		}
		else
		{
			removeLastNode();
		}
	}
	else
	{
		int position;

		if (lastNodePtr->arrayDirection == rightWiseExpandable)
		{
			position = arraySize - lastNodePtr->arrayItemsCounter;
			returnedValue = lastNodePtr->arrayPtr[position];
			lastNodePtr->arrayPtr[position] = nullptr;
		}
		else     // if the last node is leftwise expandable and has more than 1 element, then after popping the desired element all left hand side elements need to be shifted right to fill in the gap
		{
			position = arraySize - 1;   // in the current 'else' case the popped element will always be the last position in the array
			returnedValue = lastNodePtr->arrayPtr[position];
			shiftElementsRightForRemoval(lastNodePtr, position);
		}
	}

	numberOfElements--;
	return returnedValue;
}



template <class T, int arraySize>
T Deque<T, arraySize>::popFront()
{
	if (!lastNodePtr)
	{
		return nullptr;
	}

	T returnedValue = nullptr;

	if (firstNodePtr->arrayItemsCounter == 1)
	{
		if (lastNodePtr->arrayDirection == leftWiseExpandable)
		{
			returnedValue = lastNodePtr[arraySize - 1];
		}
		else
		{
			returnedValue = lastNodePtr[0];
		}


		if (lastNodePtr == firstNodePtr)   // if Deque contains one node array only, so after popping its last element this only one node should be removed, which actually is a deletion of Deque, hence the destructor will be called
		{
			this->~Deque();
			return returnedValue;
		}
		else
		{
			removeFirstNode();
		}
	}
	else      // if there is more than one elements in the first node array
	{
		int position;

		if (firstNodePtr->arrayDirection == leftWiseExpandable)
		{
			position = arraySize - firstNodePtr->arrayItemsCounter;
			returnedValue = firstNodePtr->arrayPtr[position];
			firstNodePtr->arrayPtr[position] = nullptr;
		}
		else     // if the last node is righttwise expandable and has more than 1 element, then after popping the desired element all right hand side elements need to be shifted left to fill in the gap
		{
			position = 0;   // in the current 'else' case the popped element will always be the last position in the array
			returnedValue = firstNodePtr->arrayPtr[position];
			shiftElementsLeftForRemoval(firstNodePtr, position);
		}
	}

	numberOfElements--;
	return returnedValue;
}





template <class T, int arraySize>
void Deque<T, arraySize>::shiftElementsLeftForRemoval(Node* startNode, int startPosition)
{
	chosenNodePtr = startNode;
	int destinationPosition = startPosition;
	int sourcePositionLimit = arraySize - chosenNodePtr->arrayItemsCounter;

	if (sourcePositionLimit == destinationPosition && !chosenNodePtr->nextNodePtr)   // if the startPosition is actually the last element in Deque
	{
		chosenNodePtr->arrayPtr[destinationPosition] = nullptr;
		return;
	}

	while (chosenNodePtr)
	{
		if (chosenNodePtr->arrayItemsCounter == 1)
		{
			removeLastNode();
			return;
		}

		int sourcePosition = destinationPosition + 1;

		for (; sourcePosition <= sourcePositionLimit; sourcePosition++)
		{
			chosenNodePtr->arrayPtr[destinationPosition] = chosenNodePtr->arrayPtr[sourcePosition];
			destinationPosition++;
		}

		if (chosenNodePtr->nextNodePtr)
		{
			if (chosenNodePtr->nextNodePtr->arrayItemsCounter > 0)
			{
				sourcePosition = 0;
				destinationPosition = arraySize - 1;
				chosenNodePtr->arrayPtr[destinationPosition] = chosenNodePtr->nextNodePtr->arrayPtr[sourcePosition];
			}
		}
		else
		{
			chosenNodePtr->arrayPtr[sourcePosition] = nullptr;   // nullification of the far left element to complete the shifting
		}

		chosenNodePtr = chosenNodePtr->nextNodePtr;
		destinationPosition = 0;

		if (chosenNodePtr)    // to avoid memory access violation when calling arrayItemsCounter of a non-existent NULL chosenNodePtr
		{
			sourcePositionLimit = arraySize - chosenNodePtr->arrayItemsCounter;
		}
	}
}


template <class T, int arraySize>
void Deque<T, arraySize>::printChosenNodeArray()
{
	int underscoresNumber = arraySize - chosenNodePtr->arrayItemsCounter;
	int elementNumber = chosenNodePtr->arrayItemsCounter;
	int bias = 0;     // to call proper array elements depending on whether the array is left or rightwise expandable

	if (chosenNodePtr->arrayDirection == leftWiseExpandable && underscoresNumber > 0)
	{
		for (int i = 0; i < underscoresNumber; i++)
		{
			cout << "_\t";
		}

		bias = arraySize - chosenNodePtr->arrayItemsCounter;
	}

	for (int i = 0; i < elementNumber; i++)
	{
		cout << chosenNodePtr->arrayPtr[i + bias] + "\t";
	}

	if (chosenNodePtr->arrayDirection == rightWiseExpandable && underscoresNumber > 0)
	{
		for (int i = 0; i < underscoresNumber; i++)
		{
			cout << "_\t";
		}
	}
}


template <class T, int arraySize>
ostream& operator<<(ostream& out, Deque<T, arraySize>& arg)
{
	if (!arg.firstNodePtr)
	{
		out << "\n\nThe list is empty..." << endl;
		return out;
	}

	typename Deque<T, arraySize>::Node* tempNode = arg.chosenNodePtr;    // to restore the original position of chosenNodePtr at the end
	arg.chosenNodePtr = arg.firstNodePtr;

	cout << "Current Deque content is:\n";

	while (arg.chosenNodePtr)
	{
		arg.printChosenNodeArray();
		arg.gotoNext_node();
	}

	arg.chosenNodePtr = tempNode;  // restoring the original chosenNodePtr position
	return out;
}




template <class T, int arraySize>
void Deque<T, arraySize>::gotoNext_node()
{
	if (!chosenNodePtr)
	{
		return;
	}

	chosenNodePtr = chosenNodePtr->nextNodePtr;
}


template <class T, int arraySize>
Deque<T, arraySize>::~Deque()
{
	if (!firstNodePtr)     // if Deque is empty
		return;

	while (lastNodePtr)
	{
		removeLastNode();
	}

	firstNodePtr = nullptr;
	chosenNodePtr = nullptr;
	numberOfNodes = 0;
	numberOfElements = 0;
}


//template <class T, int arraySize>
//T Deque<T, arraySize>::popBack()
//{
//	if (!lastNodePtr)
//	{
//		return nullptr;
//	}
//
//	T returnedValue = nullptr;
//
//	if (lastNodePtr->arrayItemsCounter == 1)    
//	{
//		if (lastNodePtr->arrayDirection == leftWiseExpandable)
//		{
//			returnedValue = lastNodePtr[arraySize - 1];
//		}
//		else
//		{
//			returnedValue = lastNodePtr[0];
//		}
//
//
//		if (lastNodePtr == firstNodePtr)   // if Deque contains one node array only, so after popping its last element this only one node should be removed, which actually is a deletion of Deque, hence the destructor will be called
//		{
//			this->~Deque();
//			return returnedValue;
//		}
//		else
//		{
//			removeLastNode();
//		}
//	}
//	else
//	{
//		int position;
//
//		if (lastNodePtr->arrayDirection == rightWiseExpandable)
//		{
//			position = arraySize - lastNodePtr->arrayItemsCounter;
//			returnedValue = lastNodePtr->arrayPtr[position];
//			lastNodePtr->arrayPtr[position] = nullptr;
//		}
//		else     // if the last node is leftwise expandable and has more than 1 element, then after popping the desired element all left hand side elements need to be shifted right to fill in the gap
//		{
//			position = arraySize - 1;   // in the current 'else' case the popped element will always be the last position in the array
//			returnedValue = lastNodePtr->arrayPtr[position];
//			shiftElementsRightForRemoval(lastNodePtr, position);
//		}
//	}
//
//	numberOfElements--;
//	return returnedValue;
//}




template <class T, int arraySize>
void Deque<T, arraySize>::shiftElementsRightForRemoval(Node* startNode, int startPosition)
{
	int destinationPosition = startPosition;
	int sourcePositionLimit = arraySize - chosenNodePtr->arrayItemsCounter;

	if (sourcePositionLimit == destinationPosition && !chosenNodePtr->previousNodePtr)   // if the startPosition is actually the first element in Deque
	{
		chosenNodePtr->arrayPtr[destinationPosition] = nullptr;
		return;
	}

	while (chosenNodePtr)
	{
		if (chosenNodePtr->arrayItemsCounter == 1)
		{
			removeFirstNode();
			return;
		}

		int sourcePosition = destinationPosition - 1;

		for (; sourcePosition >= sourcePositionLimit; sourcePosition--)
		{
			chosenNodePtr->arrayPtr[destinationPosition] = chosenNodePtr->arrayPtr[sourcePosition];
			destinationPosition--;
		}

		if (chosenNodePtr->previousNodePtr)
		{
			if (chosenNodePtr->previousNodePtr->arrayItemsCounter > 0)
			{
				sourcePosition = arraySize - 1;
				destinationPosition = 0;  
				chosenNodePtr->arrayPtr[destinationPosition] = chosenNodePtr->previousNodePtr->arrayPtr[sourcePosition];
			}
		}
		else
		{
			chosenNodePtr->arrayPtr[sourcePosition] = nullptr;   // nullification of the far left element to complete the shifting
		}

		chosenNodePtr = chosenNodePtr->previousNodePtr;
		destinationPosition = arraySize - 1;

		if(chosenNodePtr)    // to avoid memory access violation when calling arrayItemsCounter of a non-existent NULL chosenNodePtr
		{
			sourcePositionLimit = arraySize - chosenNodePtr->arrayItemsCounter;
		}
	}
}





template <class T, int arraySize>
void Deque<T, arraySize>::removeFirstNode()
{
	if (firstNodePtr == lastNodePtr)    // if there is only one remaining node left in Deque
	{
		this->~Deque();
		return;
	}

	Node* secondNode = firstNodePtr->nextNodePtr;
	delete[] firstNodePtr->arrayPtr;
	delete firstNodePtr;
	secondNode->previousNodePtr = nullptr;
	firstNodePtr = secondNode;
	chosenNodePtr = firstNodePtr;
	numberOfNodes--;
}



template <class T, int arraySize>
void Deque<T, arraySize>::removeLastNode()
{
	if (firstNodePtr == lastNodePtr)     // if there is only one remaining node left in Deque
	{
		this->~Deque();
		return;
	}

	Node* penultimateNode = lastNodePtr->previousNodePtr;
	delete[] lastNodePtr->arrayPtr;
	delete lastNodePtr;
	penultimateNode->nextNodePtr = nullptr;
	lastNodePtr = penultimateNode;
	chosenNodePtr = lastNodePtr;
	numberOfNodes--;
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

	numberOfElements++;
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

	numberOfElements++;
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

	numberOfNodes++;
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

	numberOfNodes++;
}

