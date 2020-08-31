#ifndef MAXHEAP_HPP
#define MAXHEAP_HPP

#include <vector>
#include <cassert>

class MaxHeap
{
private:
	size_t size;
	std::vector<int> vect;

	size_t get_parent_index(size_t index_of_a_child)
	{
		return index_of_a_child >> 1; // i / 2
	}
	size_t get_left_child_index(size_t index_of_parent)
	{
		return index_of_parent << 1; // i * 2
	}

	size_t get_right_child_index(size_t index_of_parent)
	{
		return (index_of_parent << 1) + 1; // i * 2 + 1
	}


public:
	MaxHeap()
	{
		size = 0;
		vect = { -1 };
	}

	bool is_empty()const { return size == 0; }
	int get_max() const { return vect[1]; }

	void shift_down(size_t index);
	void shift_up(size_t index);

	// O(logN)
	void insert(int value);
	// O(logN)
	int extract_max();
};


// pushes the big elements in the higher levels, after we add an element.
inline void MaxHeap::shift_up(size_t index)
{
	// index can't be greater than the size of the heap.
	// index == 1 is a base case.
	if (index > size || index == 1)
		return;

	if (vect[index] > vect[get_parent_index(index)])
		std::swap(vect[index], vect[get_parent_index(index)]);

	shift_up(get_parent_index(index));
}
inline void MaxHeap::insert(int value)
{
	if (size > vect.size())
		return;
	else
	{
		vect.push_back(value);
		size++;
		shift_up(size);
	}
}


//pushes the small elements down, after we pop the maximum element.
inline void MaxHeap::shift_down(size_t index)
{
	// the index can't be bigger than the size of the heap.
	if (index > size)
		return;

	size_t bigger_child_index = index;

	if (get_left_child_index(index) <= size && vect[index] < vect[get_left_child_index(index)])
		bigger_child_index = get_left_child_index(index);

	// here, vect[bigger_child_index] can be either index or the index of the left child.
	if (get_right_child_index(index) <= size && vect[bigger_child_index] < vect[get_right_child_index(index)])
		bigger_child_index = get_right_child_index(index);


	// here we end up with the bigger child index or the parent itself.
	// if we end up with the parent index, then there is no need to shift_down.
	if (bigger_child_index != index)
	{
		std::swap(vect[index], vect[bigger_child_index]);
		shift_down(bigger_child_index);
	}
}

inline int MaxHeap::extract_max()
{
	assert(size != 0 && "Cannot extract_max() from empty heap!\n");

	int to_return = get_max();
	std::swap(vect[1], vect[size]);
	size--;

	shift_down(1);
	return to_return;
}

#endif // !MAXHEAP_HPP
