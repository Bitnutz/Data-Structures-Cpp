#ifndef SELF_ORGANIZING_LIST_HPP
#define SELF_ORGANIZING_LIST_HPP

/*
* This self organizing list uses the transpose method to re-arrange its elements.
* In other words, every time an element is searched, it is being moved with one position ahead.
* The more an element is being searched, the further it gets in the list.
* 
* example:
* list:
*	 4 -> 1 -> 7
* search 7
* search 7
* updated list:
*	 7 -> 4 -> 1
*/
template <typename T>
struct list_node
{
	T data;
	list_node<T>* prev;
	list_node<T>* next;

	list_node(T data) :data(data), prev(nullptr), next(nullptr) {}
};

template <typename T>
class self_organizing_list
{
private:
	list_node<T>* head;
	list_node<T>* tail;

	void del();
	void copy(const self_organizing_list& other);
	void swap_adjacent_nodes(list_node<T>* previous, list_node<T>* current);


public:
	self_organizing_list() :head(nullptr), tail(nullptr) {}
	self_organizing_list(const self_organizing_list& other);
	self_organizing_list& operator=(const self_organizing_list& other);
	~self_organizing_list() { del(); }

	bool is_empty()const;
	T& get_head()const;
	T& get_tail()const;

	void push_back(const T& item);
	bool pop_front();
	list_node<T>* find(const T& item);
};

// Definitions
template<typename T>
inline void self_organizing_list<T>::del()
{
	while (!is_empty())
		pop_front();
}

template<typename T>
inline void self_organizing_list<T>::copy(const self_organizing_list& other)
{
	if (!is_empty())
	{
		del();
		head = tail = nullptr;
	}

	list_node<T>* temp = other.head;
	while (temp != nullptr)
	{
		push_back(temp->data);
		temp = temp->next;
	}
}

template<typename T>
inline void self_organizing_list<T>::swap_adjacent_nodes(list_node<T>* previous, list_node<T>* current)
{
	if (previous->prev)
		previous->prev->next = current;

	if (current->next)
		current->next->prev = previous;

	previous->next = current->next;
	current->prev = previous->prev;

	current->next = previous;
	previous->prev = current;
}

template<typename T>
inline self_organizing_list<T>::self_organizing_list(const self_organizing_list& other)
{
	copy(other);
}

template<typename T>
self_organizing_list<T>& self_organizing_list<T>::operator=(const self_organizing_list& other)
{
	if (this != &other)
	{
		del();
		copy(other);
	}
	return *this;
}

template<typename T>
inline bool self_organizing_list<T>::is_empty() const
{
	return head == nullptr && tail == nullptr;
}

template<typename T>
inline T& self_organizing_list<T>::get_head() const
{
	return head->data;
}

template<typename T>
inline T& self_organizing_list<T>::get_tail() const
{
	return tail->data;
}

template<typename T>
inline void self_organizing_list<T>::push_back(const T& item)
{
	if (is_empty())
	{
		list_node<T>* temp = new list_node<T>(item);
		head = tail = temp;
	}
	else
	{
		list_node<T>* temp = new list_node<T>(item);
		tail->next = temp;
		temp->prev = tail;
		tail = tail->next;
	}
}

template<typename T>
inline bool self_organizing_list<T>::pop_front()
{
	if (is_empty())
		return false;
	else if (head == tail)
	{
		list_node<T>* temp = head;
		head = tail = nullptr;
		delete temp;
		return true;
	}
	else
	{
		list_node<T>* temp = head;
		head = head->next;
		head->prev = nullptr;
		delete temp;
		return true;
	}
}

template<typename T>
list_node<T>* self_organizing_list<T>::find(const T& item)
{
	list_node<T>* current = head;

	while (current != nullptr)
	{
		if (current->data == item)
		{
			// no need for re-arrangings.
			if (current == head)
				return current;

			list_node<T>* prev_of_current = current->prev;
			list_node<T>* prev_of_prev = prev_of_current->prev;

			swap_adjacent_nodes(prev_of_current, current);
			// in this case the searched element is on the 2nd place, so we need to swap it with head.
			if (!prev_of_prev)
				head = current;

			// the elements here are already swapped so we update the tail if needed.
			if (tail->data == item)
			{
				tail = current->next;
			}
			return current;
		}
		current = current->next;
	}
	return nullptr;
}

#endif

