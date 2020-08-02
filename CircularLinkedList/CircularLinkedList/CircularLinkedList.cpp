// CircularLinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
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
		while (first != nullptr)
		{
			node* temp = first;
			popFront();
			delete[] temp;
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
	void pushAfter(node*& current, const T& element)
	{
		assert(!isEmpty(), "Cannot insert after a node that doesn't exist!\n");
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
	bool popAfter(node*& current)
	{
		if (isEmpty())
			return 0;
		else if (size == 1)
		{
			popFront();
			return 1;
		}
		else
		{
			node* toDel = current->next;
			current->next = toDel->next;
			delete[] toDel;
			size--;
			return 1;
		}
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
		assert(!isEmpty());
		node* temp = first ->next;
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
};

int main()
{
	
	//test basic functionalities

	Circular_linked_list<int> ll;
	ll.pushBack(1);
	ll.pushBack(2);
	ll.pushBack(3);
	ll.pushBack(4);
	ll.pushBack(5);

	Circular_linked_list<int>::node* temp = ll.find(2);
	ll.pushAfter(temp, 7);
	ll.popFront();
	std::cout << "Before popAfter()\n";
	ll.print();
	std::cout << "After popAfter()\n";
	ll.popAfter(temp);

	ll.print();
	std::cout << ll.getSize() << std::endl;

	// test copy 
	Circular_linked_list<int> ll2;
	ll2 = ll;

	ll2.print();
	std::cout << ll2.getSize() << std::endl;

	return 0;
}


