#include "brainfuck.h"
#include <iostream>
#include <fstream>

/**
 * @brief interpreter starting point
 * @param argc is the count of passed arguments
 * @param argv an array of passed arguments
 */
int main(int argc, char *argv[])
{
	int arrayLength = 1000000;  // initilize array to 1 MegaCells

	array mainArray(arrayLength);  // create mainArray instance of array class
	bool running = true;

	if(argv[1] != NULL)  // if the user passed a file as an argument to the interpreter
	{
		std::fstream file;
		file.open(argv[1]);  // open the file
		if(file.is_open())
		{
			std::string line;
			while(std::getline(file, line) && running)  // read one line at a time
			{
				for(int i = 0; i <= line.length(); i++) // execute one char at a time
				{
					interpret(line[i], mainArray, &running);
				}
			}
			std::cout << "\n\nExecution completed, press Enter to exit...";
			std::getchar();
		}
		else
		{
			std::cout << "File does not exist\n";
		}
	}
	else  // if no file was passed just start the interpreter shell
	{
		while(running)
		{
			std::cout << ">> ";
			std::string input;
			std::getline(std::cin, input);
			
			for(int i = 0; i < input.length(); i++)  // interpret one char at a time
			{
				interpret(input[i], mainArray, &running);
			}
		}
	}
}