// FilesSummer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <assert.h>
#include <iostream>
#include <fstream>

void test1()
{
	std::ofstream out("outFile.txt");
	out.write("four dif words ye", sizeof("four dif words ye"));

	std::cout << out.end;
	out.close();
	
}



/// copies the information from the first file and pastes it in the second one.
void copyPasteFile(const char* inputFileName, const char* outputFileName)
{
	// copy the content of inFile and paste it to outFile
	std::ifstream inFile(inputFileName, std::ios::in);
	std::ofstream outFile(outputFileName, std::ios::out);
	assert(inFile, "Input file failed to open.\n");
	assert(outFile, "Output file failed to open.\n");

	// take the length of the information from the input file
	inFile.seekg(0, std::ios::end);
	unsigned int inFileLength = inFile.tellg();

	inFile.seekg(0);

	char* buffer = new char[inFileLength];
	inFile.read(buffer, inFileLength);
	std::cout << "Currently the buffer is filled with: \n" << buffer << std::endl;
	outFile.write(buffer, inFileLength);
	delete []buffer;

	inFile.close();
	outFile.close();
	
}

int main()
{

	copyPasteFile("inFile.txt","outFile.txt");
	return 0;
}


