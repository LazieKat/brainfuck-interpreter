#include "brainfuck.h"
#include <iostream>

void execute(char x, array& array, bool *running);
void executeLoop(std::string loop, array& array, bool *running);

// The interpreter

void interpret(char x, array& array, bool *running)
{
	static bool recordingLoop = false;
	static int loopLevel = 0;
	static std::string loopCommands;
	if(recordingLoop)
	{
		if (x == '[')
		{
			loopLevel++;
			loopCommands += x;
		}
		else if(x == ']')
		{
			loopCommands += x;
			loopLevel--;
			if(loopLevel == 0)
			{
				recordingLoop = false;
				std::string foo = loopCommands; //loopCommands is static and must be cleared before execution for nested loops
				loopCommands.clear();
				executeLoop(foo, array, running);
			}
		}
		else
		{
			loopCommands += x;
		}
	}
	else if(x == '['){
		recordingLoop = true;
		loopLevel++;	
	}
	else
	{
		execute(x, array, running);
	}
}

void execute(char x, array& array, bool *running)
{

	if(x == '+')
	{
		array.contents[array.getPointerPos()].incrementValue();
	}
	else if(x == '-')
	{
		array.contents[array.getPointerPos()].decrementValue();
	}
	else if(x == '>')
	{
		array.incrementPointer();
	}
	else if(x == '<')
	{
		array.decrementPointer();
	}
	else if(x == '.')
	{
		std::printf("%c",array.contents[array.getPointerPos()].getValue());
	}
	else if(x == ';')
	{
		std::cout << array.contents[array.getPointerPos()].getValue() << std::endl; 
	}
	else if(x == '&')
	{
		std::cout << array.getPointerPos() << std::endl;
	}
	else if(x == '*')
	{
		*running = false;
	}
	else if(x == ',')
	{
		int val;
		while(true)
		{
			std::printf("Enter value for cell %d: ", array.getPointerPos());
			std::cin >> val;
			if(std::cin.fail())
			{
				std::cerr << "Not Valid \n";
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}
			else if(val > 255 || val < 0)
			{
				std::cout << "Value cannot be negative or larger than one byte.\n";
				std::cin.ignore(10000, '\n');
			}
			else
			{
				std::cin.ignore(10000, '\n');
				break;
			}
		}
		array.contents[array.getPointerPos()].setValue(val);
	}
}

void executeLoop(std::string loop, array& array, bool *running)
{
	if(array.contents[array.getPointerPos()].getValue() == 0)
	{
		return;
	}
	else
	{
		bool stilInLoop = true;
		while(stilInLoop)
		{
			for(int i = 0; i <= loop.length(); i++)
			{
				if(i == loop.length() && array.contents[array.getPointerPos()].getValue() == 0)
					stilInLoop = false;
				else
					interpret(loop[i], array, running);
			}
		}
	}
}
