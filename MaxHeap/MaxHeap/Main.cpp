#include "MaxHeap.hpp"
#include <iostream>


int main(int argc, char** argv)
{
	MaxHeap heap;
	std::cout << "inserting...\n";
	heap.insert(100);
	heap.insert(50);
	heap.insert(80);
	heap.insert(140);

	std::cout <<"extract_max(): "<< heap.extract_max() << "\n";
	std::cout <<"get_max()"<< heap.get_max() << "\n";
	return 0;
}