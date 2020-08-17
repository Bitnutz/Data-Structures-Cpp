// SSL+Iterator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cassert>
#include <cstring>
#include <iostream>

/*
* Helper code for the Interpreter
*	The following code is written, in order to depict how the linked list in the Tokenizer will be implemented.
*	Only the needed methods are implemented.
*
*	We have:
*		- enum class TokenType --> depicts the different types of tokens.
*		- struct Token --> token has string representation and token type.
*		- struct node --> used as listNode in the linked list.
*		- class list:
*			- private members:
*							 - node* first, *last; int size;
*							 - del(), copy();
*			-public functions:
*							 - push_back(Token)
*							 - pop_front(Token);
*							 - find(Token)
*							 - getFirst() const
*							 - getLast() const
*							 - begin() const --> iterator
*							 - end() const --> iterator
*			- class iterator:
*							 - operator*();
*							 - operator++();
*							 - operator !=();
*
*/

enum class TokenType
{
	Type1, Type2, Type3
};

struct Token
{
	TokenType type;
	std::string tokenValue;

	Token(TokenType type, const std::string& tokenValue) :type(type), tokenValue(tokenValue) {}
};

struct node
{
	Token data;
	node* next;

	node(const Token& data) :data(data), next(nullptr) {}
};

class list
{
private:

	// member variables
	node* first;
	node* last;
	size_t size;

	// delete function used in the destructor
	void del()
	{
		while (!is_empty())
		{
			node* temp = first;
			pop_front();
			delete temp;
		}
	}

	void copy(const list& other)
	{
		first = nullptr;
		node* temp = other.first;
		while (temp != nullptr)
		{
			push_back(temp->data);
			temp = temp->next;
		}
	}

public:


	struct iterator
	{
	private:
		node* current;
	public:
		friend class list;
		iterator(node* n) : current(n) {}
		iterator() : current(nullptr) {}

		// incrementation
		iterator& operator++()
		{
			current = current->next;
			return *this;
		}

		// condition in the loop
		bool operator !=(const iterator& it)
		{
			return current != it.current;
		}

		// dereferencing
		Token& operator*()
		{
			return current->data;
		}

	};


	iterator begin() const
	{
		return iterator(first);
	}
	iterator end() const
	{
		return iterator();
	}

	list() :first(nullptr), last(nullptr), size(0) { }
	list(const list& other) { copy(other); }
	list& operator=(const list& other)
	{
		if (this != &other)
		{
			del();
			copy(other);
		}
		return *this;
	}

	~list() { del(); }

	bool is_empty()const
	{
		return first == nullptr && last == nullptr;
	}

	void push_front(const Token& data)
	{
		node* temp = new node(data);
		if (is_empty())
		{
			first = temp;
			last = temp;
		}
		else
		{
			temp->next = first;
			first = temp;
		}
		size++;
	}

	void push_back(const Token& data)
	{
		node* temp = new node(data);
		if (is_empty())
		{
			first = temp;
			last = temp;
		}
		else
		{
			last->next = temp;
			last = temp;
		}
		size++;
	}

	bool pop_front()
	{
		if (is_empty())
			return 0;
		else if (size == 1)
		{
			first = nullptr;
			last = nullptr;
		}
		else
		{
			first = first->next;
		}
		size--;
		return 1;
	}

	Token& getFirst()const
	{
		return first->data;
	}

	Token& getLast() const
	{
		return last->data;
	}

	bool find(const Token& element)
	{
		node* temp = first;
		while (temp != nullptr)
		{
			if (temp->data.tokenValue == element.tokenValue)
				return 1;
			temp = temp->next;
		}
		return 0;
	}

};



int main()
{

	Token t1(TokenType::Type1, "some token, idk");
	Token t2(TokenType::Type2, "some token2, idk");
	Token t3(TokenType::Type3, "some token3, idk");

	list list;
	list.push_back(t1);
	list.push_back(t2);
	list.push_back(t3);

	for (list::iterator it = list.begin(); it != list.end(); ++it)
	{
		Token newToken = *it;
		std::cout << newToken.tokenValue << "\n";
	}

    return 0;
}

