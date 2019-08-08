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

array::array(int x)
{
	(*this).capacity = x-1; // numbering starts from 0;
	(*this).pointerPos = 0;

	(*this).contents = new cell[x];
	for(int i = 0; i <= (*this).capacity; i++)
		contents[i].setPosition(i);

	std::printf("Array with %d cells created\n", x);
}

void array::incrementPointer()
{
	if((*this).pointerPos + 1 <= (*this).capacity)
		(*this).pointerPos++;
	else
		std::cerr << "Error: array upper limit reached." << std::endl;
}

void array::decrementPointer()
{
	if((*this).pointerPos - 1 >= 0)
		(*this).pointerPos--;
	else
		std::cerr << "Error: array bottom limit reached." << std::endl;
}

int array::getPointerPos()
{
	return (*this).pointerPos;
}