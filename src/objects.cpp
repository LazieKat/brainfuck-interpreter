#include "brainfuck.h"
#include <iostream>

// The cell class

/**
 * @brief cell constructor, initilizes value of cell to zero
 */
cell::cell()
{
	(*this).value = 0;
}

/**
 * @brief returns value of the cell
 */
int cell::getValue()
{
	return (*this).value;
}

/**
 * @brief sets cell value
 * @param x and integer to store in the cell
 */
void cell::setValue(int x)
{
	(*this).value = x;
}

/**
 * @brief incremets cell value by 1
 */
void cell::incrementValue()
{
	if((*this).value == 255)  // 8 bit cellls
		(*this).value = 0;
	else
		(*this).value++;
}

/**
 * @brief decrements cell value by 1
 */
void cell::decrementValue()
{
	if((*this).value == 0)
		(*this).value = 255; // 8 bit cells
	else
		(*this).value--;
}

/**
 * @brief set cell position in the cell array
 */
void cell::setPosition(int x)
{
	(*this).position = x;
}

/**
 * @brief get the position of the cell in the cell array
 */
int cell::getPosition()
{
	return (*this).position;
}

// The array class

/**
 * @brief array constructor
 * @param x the number of cells in the array
 * @param verbose is a boolean to print an message of the numberof created cells
 */
array::array()
{
	std::cerr << "Error: You must specify array length." << std::endl;
}

array::array(int x, bool verbose)
{
	(*this).capacity = x-1; // 0 indexed;
	(*this).pointerPos = 0; // set position to beginning

	(*this).contents = new cell[x];  //creat cell array
	for(int i = 0; i <= (*this).capacity; i++)
	{
		(*this).contents[i].setPosition(i);  // set cells positions
	}

	if(verbose)
	{
		std::printf("Array initilized ith %d cells\n", x);
	}	
}

/**
 * @brief move the pointer one cell to the right
 */
void array::incrementPointer()
{
	if((*this).pointerPos + 1 <= (*this).capacity)  // check for remaining capacity
	{
		(*this).pointerPos++;
	}
	else
	{
		int newSize = ((*this).capacity + 1)*2;  //  get twice as current array capacity
		cell *temp = new cell[newSize];  //  new cell array of the new size
		for(int i = 0; i < newSize; i++)  //  initilize new cells
		{
			if(i <= (*this).capacity)  // if still in the range of old array copy cells data
			{
				temp[i].setValue((*this).contents[i].getValue());
			}
			temp[i].setPosition(i);  // set the positions of the cells
		}
		delete (*this).contents;  // free old memory
		(*this).contents = temp;  // move new data to the right variable
		(*this).capacity = newSize - 1;  // set new capacity
		(*this).pointerPos++;  // incremet the pointer 
	}
}

/**
 * @brief move the pointer one cell to the left
 */
void array::decrementPointer()
{
	if((*this).pointerPos - 1 >= 0)  // check if reached the bottom
	{
		(*this).pointerPos--;
	}
	else
	{
		std::cerr << "Error: array underflow." << std::endl;
	}
}

/**
 * @brief get current pointer position
 */
int array::getPointerPos()
{
	return (*this).pointerPos;
}