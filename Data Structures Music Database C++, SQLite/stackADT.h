// Author: Lane Murray
// Date: 12/13/2021
#ifndef STACK_H
#define STACK_H
template <typename T>
class stackADT
{
public:

	virtual void initializeStack() = 0;
	virtual bool isEmpty() const = 0;
	virtual bool isFullStack() const = 0;
	virtual void push(const T& element) = 0;
	virtual T top() const = 0;
	virtual void pop() = 0;
	virtual void purge() = 0;
};


#endif