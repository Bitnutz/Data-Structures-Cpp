#include "CircularList.h"
#include <cstring>
#include <iostream>

//this function is used in the task() function to get the input.
std::istringstream getInput()
{
	std::string curWord;
	std::string strContainer;

	std::cout << "Enter the words you wish to add into the list \n(entering new line without content exits the loop):\n";

	while (std::getline(std::cin,curWord) && curWord.length() != 0)
	{
		strContainer += curWord;
		strContainer += " ";
	}
	
	std::istringstream result(strContainer);
	return result;
}
void task()
{
	Circular_linked_list ll;

	std::istringstream iss = getInput();
	std::string curWord;

	while (iss >> curWord)
		ll.pushBack(curWord.c_str());

	ll.print();
	std::cout << "The size of the list is currently: " << ll.getSize() << "\n\n";

	std::cout << "doTask() called.\n";
	ll.doTask(ll.getFirst());
	std::cout << "The size of the list is currently: " << ll.getSize() << "\n\n";


	std::cout << "sort function called.\n";
	ll.selectionSort();
	ll.print();

	std::cout << "Longest string: " << ll.findBiggestNode() << "\n\n";
}


// made for lazy testing.
void task_with_example()
{
	Circular_linked_list ll;

	ll.pushBack("Street");
	ll.pushBack("Taxi");
	ll.pushBack("Ink");
	ll.pushBack("Dog");
	ll.pushBack("Smile");
	ll.pushBack("Eat");
	ll.pushBack("Tall");
	ll.pushBack("Pass");

	ll.print();
	std::cout << "The size of the list is currently: " << ll.getSize() << "\n\n";

	std::cout << "doTask() called.\n";
	ll.doTask(ll.getFirst());
	std::cout << "The size of the list is currently: " << ll.getSize() << "\n\n";


	std::cout << "sort function called.\n";
	ll.selectionSort();
	ll.print();

	std::cout << "Longest string: " << ll.findBiggestNode() << "\n\n";
}



int main(int argc, char**argv)
{
	task();

	//task_with_example();

	return 0;
}
