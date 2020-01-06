#include "brainfuck.h"
#include <iostream>

// The cell class

cell::cell()
{
	(*this).value = 0;
}

int cell::getValue()
{
	return (*this).value;
}

void cell::setValue(int x)
{
	(*this).value = x;
}

void cell::incrementValue()
{
	if((*this).value == 255)
		(*this).value = 0;
	else
		(*this).value++;
}

void cell::decrementValue()
{
	if((*this).value == 0)
		(*this).value = 255;
	else
		(*this).value--;
}

void cell::setPosition(int x)
{
	(*this).position = x;
}

int cell::getPosition()
{
	return (*this).position;
}

// The array class

array::array()
{
	std::cerr << "Error: You must specify array length." << std::endl;
}

array::array(int x, bool verbose)
{
	(*this).capacity = x-1; // numbering starts from 0;
	(*this).pointerPos = 0;

	(*this).contents = new cell[x];
	for(int i = 0; i <= (*this).capacity; i++)
	{
		(*this).contents[i].setPosition(i);
	}

	if(verbose)
	{
		std::printf("Array initilized ith %d cells\n", x);
	}	
}

void array::incrementPointer()
{
	if((*this).pointerPos + 1 <= (*this).capacity)
	{
		(*this).pointerPos++;
	}
	else
	{
		int newSize = ((*this).capacity + 1)*2;
		cell *temp = new cell[newSize];
		for(int i = 0; i < newSize; i++)
		{
			if(i <= (*this).capacity)
			{
				temp[i].setValue((*this).contents[i].getValue());
			}
			temp[i].setPosition(i);
		}
		delete (*this).contents;
		(*this).contents = temp;
		(*this).capacity = newSize - 1;
		(*this).pointerPos++;
	}
}

void array::decrementPointer()
{
	if((*this).pointerPos - 1 >= 0)
	{
		(*this).pointerPos--;
	}
	else
	{
		std::cerr << "Error: array bottom limit reached." << std::endl;
	}
}

int array::getPointerPos()
{
	return (*this).pointerPos;
}