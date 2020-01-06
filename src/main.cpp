#include "brainfuck.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
	int arrayLength = 1000000;

	array mainArray(arrayLength);
	bool running = true;

	if(argv[1] != NULL)
	{
		std::fstream file;
		file.open(argv[1]);
		if(file.is_open())
		{
			std::string line;
			while(std::getline(file, line) && running)
			{
				for(int i = 0; i <= line.length(); i++)
				{
					interpret(line[i], mainArray, &running);
				}
			}
			std::cout << "\nExecution completed, press Enter to exit...";
			std::getchar();
		}
		else
		{
			std::cout << "File does not exist\n";
		}
	}
	else
	{
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
}