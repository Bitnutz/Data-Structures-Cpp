#include "CircularList.h"

// Node Constructor Definition ####################################################
Circular_linked_list::node::node(std::string data): data(data), next(nullptr) { }

// List Constructors Definitions ####################################################
Circular_linked_list::Circular_linked_list() : first(nullptr), last(nullptr), size(0) {}

Circular_linked_list:: Circular_linked_list(const Circular_linked_list& other)
{
	copy(other);
}
Circular_linked_list& Circular_linked_list:: operator=(const Circular_linked_list& other)
{
	if (this != &other)
	{
		del();
		copy(other);
	}
	return *this;
}

Circular_linked_list::~Circular_linked_list()
{
	del();
}


// Private methods Definitions ####################################################
void Circular_linked_list::copy(const Circular_linked_list& other)
{
	first = nullptr;
	node* temp = other.first;
	for (size_t i = 0; i < other.size; i++)
	{
		pushBack(temp->data);
		temp = temp->next;
	}
}

void Circular_linked_list::del()
{
	while (size != 0)
	{
		node* temp = first;
		popFront();
		delete temp;
	}
}

// Saves the data of the passed node in std::string and the data of the next node (the node after the passed one).
// Then it pops the current element and appends its value to the next one.
// This function is called only when a condition is being fullfiled in the doTask() function.
void Circular_linked_list::modify(node*& current)
{
	node* newNode = current->next;
	std::string fstData = current->data;
	std::string sndData = newNode->data;

	popCurrent(current);

	std::string result = fstData + "-" + sndData;
	newNode->data = result;
}


// Add an element ####################################################
void Circular_linked_list::pushFront(std::string element)
{
	node* temp = new node(element);
	if (isEmpty())
	{
		first = temp;
		last = temp;
	}
	else
	{
		temp->next = first;
		first = temp;
		last->next = first;
	}
	size++;
}

void Circular_linked_list::pushBack(std::string element)
{
	node* temp = new node(element);
	if (isEmpty())
	{
		first = temp;
		last = temp;
	}
	else
	{
		last->next = temp;
		last = temp;
		last->next = first;
	}
	size++;
}

void Circular_linked_list::pushAfter(node* current, std::string element)
{
	assert(!isEmpty() && "Cannot insert after a node that doesn't exist!\n");
	node* temp = new node(element);

	if (size == 1)
	{
		current->next = temp;
		temp->next = current;
	}
	else
	{
		temp->next = current->next;
		current->next = temp;
	}
	size++;
}


// Remove an element ####################################################
bool Circular_linked_list::popFront()
{
	if (isEmpty())
		return 0;
	else if (size == 1)
	{
		first = nullptr;
		last = nullptr;
		size--;
		return 1;
	}
	else
	{
		first = first->next;
		last->next = first;
		size--;
		return 1;
	}
}

bool Circular_linked_list::popCurrent(node* current)
{
	if (isEmpty())
		return 0;
	node* temp = first;
	if (temp->data == current->data)
	{
		popFront();
		return 1;
	}

	for (size_t i = 0; i < size; i++)
	{
		if (temp->next == last && last->data == current->data)
		{
			temp->next = last->next;
			last = temp;
		}
		else if (temp->next == current)
		{
			node* toDel = temp->next;
			temp->next = toDel->next;
		}
		temp = temp->next;
	}
	size--;
	return 1;
}


// Checks ####################################################
bool Circular_linked_list::isEmpty() const
{
	return first == nullptr && last == nullptr;
}

size_t Circular_linked_list::getSize() const
{
	return size;
}

void Circular_linked_list::print() const
{
	assert(!isEmpty() && "Cannot print an empty list!\n");
	node* temp = first;
	std::cout << " -> ";
	for (size_t i = 0; i < size; i++)
	{
		std::cout << temp->data << " -> ";
		temp = temp->next;
	}
	std::cout <<"\n\n";
}


// Getters ####################################################

std::string Circular_linked_list::findBiggestNode()
{
	node* traverser;
	size_t biggestNodeLength = first->data.length();
	std::string result = first->data;

	if (size == 1)
		return first->data;

	// If there are only two elements the loop below won't iterate not even once,
	// because traverser->next will point to first and as can be seen below, traverser->next != first.
	if (size == 2)
	{
		if (first->data > last->data)
			return first->data;
		return last->data;
	}

	for (traverser = first->next; traverser->next != first; traverser = traverser->next)
	{
		size_t traverserLength = traverser->data.length();

		if (traverserLength > biggestNodeLength)
		{
			biggestNodeLength = traverserLength;
			result = traverser->data;
		}
	}
	return result;
}


Circular_linked_list::node* Circular_linked_list::getFirst() const
{
	return first;
}

Circular_linked_list::node* Circular_linked_list::getLast() const
{
	return last;
}

// Sort ####################################################

// Sorting the elements lexicographically
void Circular_linked_list::selectionSort()
{
	node* index;
	node* selection;
	std::string temp;

	if (size == 1)
		return;
	// in case there are only two elements
	// This check is made, because in the second loop below selection->next cannot be equal to first.
	if (size == 2)
	{
		if (first->data > last->data)
		{
			temp = first->data;
			first->data = last->data;
			last->data = temp;
		}
	}

	for (index = first; index->next != first; index = index->next)
	{
		for (selection = index->next; selection->next != first; selection = selection->next)
		{
			if (index->data > selection->data)
			{
				temp = index->data;
				index->data = selection->data;
				selection->data = temp;
			}
		}
	}
}


// Task solving function ####################################################

void Circular_linked_list::doTask(node* passedNode)
{
	assert(!isEmpty() && "The list cannot be empty when this function is being applied! \n");

	node* temp = passedNode;
	size_t sizeTemp = size; // we save the size in sizeTemp, because when we execute the modify function,
							// popCurrent() is being called, therefore the size is getting reduced
							// which might lead to partial traversal of the list.

	// if there is only one element, there is nothing that can be modified.
	if (size == 1)
		return;

	for (size_t i = 0; i < sizeTemp; i++) 
	{										  
		size_t tempDataLength = temp->data.length();


		// if the last char of temp->data is equal to the first char of temp->next->data, the program executes modify().
		// For example: Street Taxi => t == T 
		if (temp->data[tempDataLength - 1] == temp->next->data[0] || temp->data[tempDataLength - 1] == temp->next->data[0] + 32) 
		{
			modify(temp);
			temp = temp->next;
		}
		// else we just go to the next node.
		else
			temp = temp->next;
	}
}

