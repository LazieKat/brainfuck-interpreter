#include "brainfuck.h"
#include <iostream>

int main()
{
	int arrayLength = 0;

	while(arrayLength == 0)
	{
		std::cout << "Enter array length needed: ";
		std::cin >> arrayLength;
		if(std::cin.fail())
		{
			std::cerr << "Not Valid \n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	}

	array mainArray(arrayLength);
	std::cin.ignore(10000, '\n');

	bool running = true;
	while(running)
	{
		std::cout << ">> ";
		std::string input;
		std::getline(std::cin, input);
		
		for(int i = 0; i < input.length(); i++)
		{
			interpret(input[i], mainArray, &running);
		}
	}
}