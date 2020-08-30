// TreeDeserialization.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cassert>
#include <string>
#include <stack>
#include <fstream>
#include <sstream>
#include <iostream>


bool recognizeDigit(char symbol) // used to determine whether a char is a digit or not.
{
	return symbol >= '0' && symbol <= '9';
}

int getMax(int lhs, int rhs)
{
	return lhs > rhs ? lhs : rhs;
}

struct node
{
	int data;
	node* left;
	node* right;

	node(int data) : data(data), left(nullptr), right(nullptr) {}
	node() :data(0), left(nullptr), right(nullptr) {}
};

class BinaryTree
{
private:
	node* root;

	// Private methods #################################################

	void del(node*& node)
	{
		if (node)
		{
			del(node->left);
			del(node->right);
			delete node;
			node = nullptr;
		}
	}

	node* copy(const node* node)
	{
		if (!node)
			return nullptr;
		struct node* temp = new struct node(node->data);
		copy(node->left);
		copy(node->right);
		return temp;
	}

	/*
	* The private overloaded function takes reference to a pointer of the root and reference to the istringstream.
	* The base case and the error handling are happening in one condition.
	* Via recursion, we extract each token from the stream (the tokens are a number or a '#', which stands for empty node).
	*/
	node* deserialize(node*& current, std::istringstream& iss)
	{
		std::string currentNode;
		iss >> currentNode;

		if (currentNode == "#" || currentNode == "") // base case and case when the flag from getInput() is 0, i.e. when the input is incorrect.
			return nullptr;

		current = new node(std::stoi(currentNode));
		deserialize(current->left, iss);
		deserialize(current->right, iss);

		return current;
	}

	/*
	* Transforms the data from the file into a string.
	* Checks if the input is correct.
	*/
	std::string getInput(std::string fileName)
	{
		std::ifstream inFile(fileName);
		assert(inFile && "File could not open!\n");


		std::string currentToken;		 // currentToken can only be a number.
		std::stack<char> bracketStack;   // bracketStack will keep track of the brackets and their order.
		bool flag = 1;					 // whenever flag goes 0, the program will return.
		std::string nums;			 	 // nums will save the numbers in order.
		char prevChar = inFile.peek();   // used to keep track of the null nodes. --> if () occurs it counts as null node.
		while (!inFile.eof())
		{
			currentToken = ""; //re-initialize the string

			if ((char)inFile.peek() == '(')
			{
				bracketStack.push('(');
				prevChar = inFile.peek();
				inFile.ignore();
			}
			else if ((char)inFile.peek() == ')')
			{
				if (bracketStack.empty()) // the input is incorrect if that condition is true.
				{
					std::cerr << "Invalid bracket usage!\n";
					flag = 0;
				}
				else
				{
					bracketStack.pop();
					if (prevChar == '(')
						nums += "# ";
				}
				prevChar = inFile.peek();
				inFile.ignore();
			}
			else if (recognizeDigit((char)inFile.peek()))
			{
				// save the number in currentToken via the function recognizeDigit();
				while (recognizeDigit((char)inFile.peek()))
				{
					currentToken += (char)inFile.peek();
					prevChar = inFile.peek();
					inFile.ignore();
				}
				nums += currentToken;
				nums += " ";
			}
			else if ((char)inFile.peek() == ' ' || inFile.eof())
			{
				prevChar = inFile.peek();
				inFile.ignore();
			}
			else
			{
				std::cerr << "Invalid input!\n";
				flag = 0;
			}
			if (!flag)
				break;
		}

		if (!bracketStack.empty())
		{
			std::cerr << "Invalid bracket usage!\n";
			flag = 0;
		}

		// ##############################################################
		if (!flag) // if flag is 0, empty the string
			return "";

		return nums;
	}

	void serialize(node*& current, std::ostringstream& oss)
	{
		if (!current)
		{
			oss << " ()";
			return;
		}
		oss << " (" << current->data;
		serialize(current->left, oss);
		serialize(current->right, oss);
		oss << ")";
	}

	bool isBST(node* current) const
	{
		if (!current)
			return 1;

		if (current->left && current->data < current->left->data)
			return 0;
		if (current->right && current->data > current->right->data)
			return 0;
		if (!isBST(current->left) || !isBST(current->right))
			return 0;
		return 1;
	}

	int getHeight(node* current)
	{
		if (!current)
			return 0;
		return 1 + getMax(getHeight(current->left), getHeight(current->right));
	}

	bool isBalanced(node* current)
	{
		int ll;
		int rl;
		if (!current) // every null node is balanced
			return 1;

		ll = getHeight(current->left);
		rl = getHeight(current->right);

		if (isBalanced(current->left) && isBalanced(current->right) && abs(ll - rl) <= 1)
			return 1;

		return 0;


	}

	int getSize(node* current)
	{
		if (!current)
			return 0;
		return 1 + getSize(current->left) + getSize(current->right);
	}


	/*
	*	Post-order traversal is being used.
	*
	* 1) if the bad node has 0 children, we just remove it.
	* 2) if the bad node has one child ONLY, we delete the bad node
	*    alongside with its child.
	* 3) if the bad node has two children, we delete the bad node
	*    alongside with both children.
	*/
	void trimTree(node*& current)
	{
		if (!current)
			return;

		trimTree(current->left);
		trimTree(current->right);

		int height = getHeight(current);

		if (height >= 2)
		{
			// if the current path is ordered, we continue to the next node.
			if (isBST(current))
				return;

			else if (current->left && current->right)
			{
				// make checks for the children
				if (current->left->data > current->data)
					del(current->left);

				else if (current->right->data < current->data)
					del(current->right);
			}

			else if (!current->right)
				del(current->left);

			else  //if (!current->left)
				del(current->right);
		}
	}

public:
	// Constructors #################################################
	BinaryTree() :root(nullptr) {}
	BinaryTree(const BinaryTree& other)
	{
		root = copy(other.root);
	}
	BinaryTree& operator=(const BinaryTree& other)
	{
		if (this != &other)
		{
			del(root);
			root = copy(other.root);
		}
		return *this;
	}
	~BinaryTree()
	{
		del(root);
	}


	// Public methods #################################################

	/*
	* Calls the function getInput() and takes the data from the file (getInput() can be called only once!).
	* Saves the string into istringstream.
	* Returns the private overloaded function deserialize().
	*/
	node* deserialize(std::string fileName)
	{
		std::string input = getInput(fileName);
		std::istringstream iss(input);
		return deserialize(root,iss);
	}

	void serialize(std::string fileName)
	{
		assert(root && "The root of the tree is empty!\n");

		std::ofstream outFile(fileName);
		assert(outFile && "The outFile could not open!\n");

		std::ostringstream oss;
		serialize(root, oss);

		outFile << oss.str();
	}

	bool isBST() const
	{
		return isBST(root);
	}

	bool isBalanced()
	{
		return isBalanced(root);
	}

	int getSize()
	{
		return getSize(root);
	}

	bool isPerfect()
	{
		int height = getHeight(root);
		int countOfNodes = getSize(root);

		return pow(2, height) - 1 == countOfNodes;
		// 1. A perfect binary tree of height h has 2h + 1 – 1 node.
		// 2. A perfect binary tree of height h has 2h leaf nodes.
	}
	
	void trimTree()
	{
		// if we don't have a root or the tree is already ordered, return.
		if (!root || isBST()) 
			return;
		trimTree(root);
	}
};




/*
* Функция, която получава като аргумент двоично дърво и проверява дали то е двоично
* дърво за търсене.
*/
bool isBinarySearchTree(const BinaryTree& bt)
{
	return bt.isBST();
}

/*
* Функция, която получава като аргумент двоично дърво и проверява дали то е
* балансирано, идеално балансирано или нито едно от двете.
*/
void isBalancedAndPerfectlyBalanced(BinaryTree& bt)
{
	if (bt.isBalanced() && !bt.isPerfect())
		std::cout << "The tree is only balanced!\n";

	else if (!bt.isBalanced() && bt.isPerfect())
		std::cout << "The tree is only perfect!\n";

	else if (bt.isBalanced() && bt.isPerfect())
		std::cout << "The tree is balanced and perfect!\n";
	else
		std::cout << "The tree is neither balanced nor perfect!\n";

}


void testTree()
{
	BinaryTree bt;
	bt.deserialize("tree.txt");
	bt.serialize("outputTree.txt");

	std::cout <<"Is BST: "<< std::boolalpha<<isBinarySearchTree(bt) <<"\n";

	std::cout <<"Is Balanced: "<< std::boolalpha << bt.isBalanced() << "\n";

	std::cout << "\n";
	isBalancedAndPerfectlyBalanced(bt);

	bt.trimTree();

	std::cout << "After trimTree()\nIs BST: " << std::boolalpha << isBinarySearchTree(bt) << "\n\n";
	isBalancedAndPerfectlyBalanced(bt);
}


int main()
{
	testTree();

	return 0;
}

