#include <iostream>

class cell
{
	public:
		cell()
		{
			(*this).value = 0;
		}

		int getValue()
		{
			return (*this).value;
		}

		void setValue(int x)
		{
			(*this).value = x;
		}

		void incrementValue()
		{
			if((*this).value == 255)
				(*this).value = 0;
			else
				(*this).value++;
		}

		void decrementValue()
		{
			if((*this).value == 0)
				(*this).value = 255;
			else
				(*this).value--;
		}


		int getPosition()
		{
			return (*this).position;
		}


	private:
		int value;
		int position;

		void setPosition(int x)
		{
			(*this).position = x;
		}

		friend class array;
};

class array
{
	public:
		array()
		{
			std::cerr << "Error: You must specify array length." << std::endl;
		}

		array(int x)
		{
			(*this).capacity = x-1; // numbering starts from 0;
			(*this).pointerPos = 0;

			(*this).contents = new cell[x];
			for(int i = 0; i <= (*this).capacity; i++)
				contents[i].setPosition(i);

			std::printf("Array with %d cells created\n", x);
		}

		void incrementPointer()
		{
			if((*this).pointerPos + 1 <= (*this).capacity)
				(*this).pointerPos++;
			else
				std::cerr << "Error: array upper limit reached." << std::endl;
		}

		void decrementPointer()
		{
			if((*this).pointerPos - 1 >= 0)
				(*this).pointerPos--;
			else
				std::cerr << "Error: array bottom limit reached." << std::endl;
		}

		int getPointerPos()
		{
			return (*this).pointerPos;
		}
		
		cell *contents;


	private:
		int capacity;
		int pointerPos;
};

void interpret(char x, array& array, bool *running);
void executeLoop(std::string loop, array& array, bool *running);

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
				std::string foo = loopCommands; //because loopCommands is static and should be cleared before execution just incase of nested loops
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