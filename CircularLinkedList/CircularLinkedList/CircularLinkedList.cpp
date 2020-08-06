// CircularLinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <assert.h>
#include <iostream>

template <typename T>
class Circular_linked_list
{
public:
struct node
{
	T data;
	node* next;

	node(const T& data) :data(data), next(nullptr) {}
};


private:
	node* first;
	node* last;
	size_t size;

	void copy(const Circular_linked_list& other)
	{
		first = nullptr;
		node* temp = other.first;
		for(size_t i = 0; i < other.size; i++)
		{
			pushBack(temp->data);
			temp = temp->next;
		}
	}
	
	void del()
	{
		while (size != 0)
		{
			node* temp = first;
			popFront();
			delete temp;
		}
	}



public:
	Circular_linked_list() :first(nullptr), last(nullptr), size(0) {}
	Circular_linked_list(const Circular_linked_list& other)
	{
		copy(Circular_linked_list & other);
	}
	Circular_linked_list& operator=(const Circular_linked_list& other)
	{
		if (this != &other)
		{
			del();
			copy(other);
		}
		return *this;
	}
	~Circular_linked_list() { del(); }



	// ################# Add an element
	// O(1)
	void pushFront(const T& element)
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
	// O(1)
	void pushBack(const T& element)
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
	void pushAfter(node* current, const T& element)
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

    // ################# Remove an element
	bool popFront()
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
	bool popCurrent(node* current)
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

	// ################# Checks
	bool isEmpty() const
	{
		return first == nullptr && last == nullptr;
	}
	size_t getSize() const
	{
		return size;
	}
	void print() const
	{
		assert(!isEmpty() && "Cannot print an empty list!\n");
	
		node* temp = first;
		for(size_t i = 0; i < size; i++)
		{
			std::cout << temp->data << "  ";
			temp = temp->next;
		}
		std::cout << std::endl;
	}

	// ################# Find an element
	//todo: better handling of the cases where the element is not found
	node* find(const T& element)
	{
		if (isEmpty())
			return nullptr;
		else
		{
			node* temp = first;
			for (size_t i = 0; i < size; i++)
			{
				if (temp->data == element)
					return temp;
				temp = temp->next;
			}
			return nullptr;
		}
	}

	// Getters
	node* getFirst() const
	{
		return first;
	}
	node* getLast() const
	{
		return last;
	}
	
	//sort
	void sortList()
	{
		node* index;
		node* selection;
		T temp;

		for (index = first; index->next != first; index = index->next)
		{
			for (selection = index->next; selection->next != first->next; selection = selection->next)
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
};

void mainTest()
{
	//test basic functionalities

	// the sorting function works only with number-types variables (int, double, etc.)

	Circular_linked_list<int> ll;
	ll.pushBack(1);
	ll.pushBack(2);
	ll.pushBack(3);
	ll.pushBack(4);
	ll.pushBack(5);

	Circular_linked_list<int>::node* temp = ll.find(2);
	ll.pushAfter(temp, 7);
	ll.popFront();
	std::cout << "Before popCurrent(2)\n";
	ll.print();
	std::cout << "After popCurrent(2)\n";
	ll.popCurrent(temp);
	ll.print();
	std::cout << "Size: "<< ll.getSize() << std::endl;
	std::cout << "Selection sort applied:\n";
	ll.sortList();
	ll.print();

	// test copy 
	std::cout << "Test operator=\n";
	Circular_linked_list<int> ll2;
	ll2 = ll;

	ll2.print();
	std::cout << ll2.getSize() << std::endl;
}


int main()
{
	mainTest();

	return 0;
}


