#include "self_organizing_list.hpp"
#include <iostream>

int main()
{
	self_organizing_list<int> solist;

	solist.push_back(4);
	solist.push_back(1);
	solist.push_back(7);

	std::cout <<"Get head of list: "<< solist.get_head() << "\n";
	std::cout << "Get tail of list: " << solist.get_tail() << "\n";

	solist.find(7);
	solist.pop_front();

	std::cout << "Get head of list: " << solist.get_head() << "\n";
	std::cout << "Get tail of list: " << solist.get_tail() << "\n";


	self_organizing_list<int> solist2 = solist;
	std::cout << "Get head of list2: " << solist2.get_head() << "\n";

	return 0;
}