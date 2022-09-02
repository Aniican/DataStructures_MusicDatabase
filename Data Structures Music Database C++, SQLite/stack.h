// Author: Lane Murray
// Date: 12/13/2021
#pragma once
#include <stdexcept>
#include "stackADT.h"

using namespace std;

template<typename T> // I prefer typename over class because class can get confusing when reading the code.
class stack // This entire class is pretty much exactly what was written in class.
{
private:

	T *list;
	int stackTop;
	int maxStackSize;

public:
	// Constructor 
	stack(int size = 100);
	// Destructor
	~stack();

	void initializeStack();

	void pop();

	void push(const T& element);

	T top() const;

	bool isEmpty() const;

	bool isFullStack() const;

	void purge();
};

template <typename T>
stack<T>::stack(int size) // Constructor
{
	if (size <= 0)
	{
		maxStackSize = 100;
		stackTop = 0;
		list = new T[maxStackSize];
		throw out_of_range("Size of the array to hold the stack must be positive.");
	}
	else
	{
		maxStackSize = size;
		stackTop = 0;
		list = new T[maxStackSize];
	}
}

template <typename T>
stack<T>::~stack() // Destructor
{
	delete[] list;
}

template <typename T>
void stack<T>::initializeStack() // initalizes the stack
{
	stackTop = 0;
}

template <typename T>
void stack<T>::pop() // Removes the top element from the stack
{
	if (isEmpty())
		throw out_of_range("Cannot remove from an empty stack.");

	stackTop--;
}

template <typename T>
void stack<T>::push(const T& element) // Adds a new element to the stack
{
	if (!isFullStack())
	{
		list[stackTop] = element;
		stackTop++;
	}
	else
		throw out_of_range("Cannot add to a full stack.");
}

template <typename T>
T stack<T>::top() const // Returns the top element of the stack
{
	if (isEmpty())
		throw out_of_range("Cannot use top with an empty stack.");

	return list[stackTop - 1];
}

template <typename T>
bool stack<T>::isEmpty() const // Returns true if stack is Empty, else false
{
	return stackTop == 0;
}

template <typename T>
bool stack<T>::isFullStack() const // Returns true if stack is Full, else false
{
	return stackTop == maxStackSize;
}

template<typename T>
void stack<T>::purge()
{

}
