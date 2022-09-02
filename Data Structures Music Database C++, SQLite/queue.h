// Author: Lane Murray
// Date: 12/13/2021
#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include "queueADT.h"
#include <stdexcept>

template <class Type>
struct node {
	Type info;
	node<Type>* link;
	node(const Type& info)
	{
		this->info = info;
	}
};

template <class Type>
class linkedQueue : queueADT<Type> {
public:
	bool isEmptyQueue() const;
	bool isFullQueue() const;
	void initializeQueue();
	Type front() const;
	Type back() const;
	void enqueue(const Type& queueElement);
	void dequeue();
	const linkedQueue<Type>& operator= (const linkedQueue<Type>& otherQueue);
	linkedQueue();
	linkedQueue(const linkedQueue<Type>& otherQueue);
	~linkedQueue();

private:
	node<Type>* queueFront;
	node<Type>* queueRear;

	void copyQueue(const linkedQueue<Type>& otherQueue);
};

template <class Type>
bool linkedQueue<Type>::isEmptyQueue() const {
	return (this->queueFront == nullptr);
}

template <class Type>
bool linkedQueue<Type>::isFullQueue() const {
	return false;
}

template <class Type>
void linkedQueue<Type>::initializeQueue() {
	node<Type>* temp;
	while (this->queueFront != nullptr) {
		temp = this->queueFront;
		this->queueFront = queueFront->link;
		delete temp;
	}

	this->queueRear = nullptr;
}

template <class Type>
Type linkedQueue<Type>::front() const {
	if (this->queueFront == nullptr)
		throw std::out_of_range("You can not get an item from an empty queue");

	return this->queueFront->info;
}

template <class Type>
Type linkedQueue<Type>::back() const {
	if (this->queueRear == nullptr)
		throw std::out_of_range("You can not get an item from an empty queue");

	return this->queueRear->info;
}

template <class Type>
void linkedQueue<Type>::enqueue(const Type& newElement) {
	node<Type>* newNode;
	newNode = new node<Type>(newElement);
	newNode->link = nullptr;

	if (this->queueFront == nullptr) {
		this->queueFront = newNode;
		this->queueRear = newNode;
	}
	else {
		queueRear->link = newNode;
		queueRear = queueRear->link;
	}
}

template <class Type>
void linkedQueue<Type>::dequeue() {
	node<Type>* temp;
	if (!isEmptyQueue()) {
		temp = queueFront;
		queueFront = queueFront->link;
		delete temp;
		if (queueFront == nullptr)
			queueRear = nullptr;
	}
	else
		throw std::out_of_range("Cannot remove from an empty queue");
}

template <class Type>
linkedQueue<Type>::~linkedQueue() {
	initializeQueue();
}

template <class Type>
void linkedQueue<Type>::copyQueue(const linkedQueue<Type>& otherQueue) {
	node<Type>* newNode;
	node<Type>* current;

	if (this->queueFront != nullptr)
		this->initializeQueue();

	if (otherQueue.queueFront == nullptr) {
		this->queueFront = nullptr;
		this->queueRear = nullptr;
	}
	else {
		current = otherQueue.queueFront;
		this->queueFront = new node<Type>(current->info);
		this->queueFront->link = nullptr;

		this->queueRear = queueFront;
		current = current->link;
		while (current != nullptr) {
			newNode = new node<Type>(current->info);
			newNode->link = nullptr;
			this->queueRear->link = newNode;
			queueRear = newNode;
			current = current->link;
		}
	}
}

template <class Type>
const linkedQueue<Type>& linkedQueue<Type>::operator= (const linkedQueue<Type>& otherQueue) {
	copyQueue(otherQueue);
	return *this;
}

template<class Type>
linkedQueue<Type>::linkedQueue() {
	this->queueFront = nullptr;
	this->queueRear = nullptr;
}

template <class Type>
linkedQueue<Type>::linkedQueue(const linkedQueue<Type>& otherQueue) {
	copyQueue(otherQueue);
}



#endif