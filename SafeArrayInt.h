#ifndef SAFE_ARRAY_INT_H
#define SAFE_ARRAY_INT_H

#include <cassert>
#include <iostream>

class SafeArrayInt
{
private:
	int arrayTotalCapacity;
	int arrayUsedCapacity;
	int* intArray;


	void doubleArraySize();
	void halveArraySize();

public:
	SafeArrayInt();

	int size() const { return arrayUsedCapacity; }
	int getTotalCap() const { return arrayTotalCapacity; }

	// ReSharper disable once CppInconsistentNaming
	void push_back(const int newValue);

	// ReSharper disable once CppInconsistentNaming
	int pop_back();

	int& at(const int pos) const;

	int& operator[](const int pos) const { return at(pos); }

	~SafeArrayInt();
	
};



#endif