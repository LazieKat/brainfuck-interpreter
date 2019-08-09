#ifndef BRAINFUCK_OBJECTS_HPP
#define BRAINFUCK_OBJECTS_HPP

#include <string>

class cell
{
	public:
		cell();
		int getValue();
		void setValue(int x);
		void incrementValue();
		void decrementValue();
		int getPosition();

	private:
		int value;
		int position;
		void setPosition(int x);

		friend class array;
};

class array
{
	public:
		array();
		array(int x, bool verbose = false);
		void incrementPointer();
		void decrementPointer();
		int getPointerPos();
		cell *contents;

	private:
		int capacity;
		int pointerPos;
};

void interpret(char x, array& array, bool *running);

#endif