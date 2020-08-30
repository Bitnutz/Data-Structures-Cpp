#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

#include <sstream>
#include <cassert>
#include <iostream>


class Circular_linked_list
{
public:
	struct node
	{
		std::string data;
		node* next;

		node(std::string data);
	};
private:
	node* first;
	node* last;
	size_t size;

	void copy(const Circular_linked_list& other);
	void del();

	//Helper Function for task1
	void modify(node*& current);

public:
	Circular_linked_list();
	Circular_linked_list(const Circular_linked_list& other);
	Circular_linked_list& operator=(const Circular_linked_list& other);
	~Circular_linked_list();

	// Add an element
	void pushFront(std::string element);
	void pushBack(std::string element);
	void pushAfter(node* current, std::string element);

	// Remove an element
	bool popFront();
	bool popCurrent(node* current);

	// Checks
	bool isEmpty() const;
	size_t getSize() const;
	void print() const;

	// Getters
	node* getFirst() const;
	node* getLast() const;
	std::string findBiggestNode();

	//sort
	void selectionSort();

	// Task1
	void doTask(node* passedNode);
};

#endif