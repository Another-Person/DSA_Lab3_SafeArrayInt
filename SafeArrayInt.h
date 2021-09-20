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


	void doubleArraySize()
	{
		const int newCap = arrayTotalCapacity * 2;
		int* newArray = new int[newCap];

		for (int i = 0; i < arrayUsedCapacity; ++i)
		{
			newArray[i] = intArray[i];
		}
		
		delete [] intArray;
		intArray = newArray;
		arrayTotalCapacity = newCap;
	}

	void halveArraySize()
	{
		const int newCap = arrayTotalCapacity / 2;
		int* newArray = new int[newCap];

		assert(arrayUsedCapacity <= (newCap / 2) && "Trying to halve array when more than half of the new array would be used!");
		
		for (int i = 0; i < arrayUsedCapacity; ++i)
		{
			newArray[i] = intArray[i];
		}

		delete [] intArray;
		intArray = newArray;
		arrayTotalCapacity = newCap;
	}

public:
	SafeArrayInt() : arrayTotalCapacity(10), arrayUsedCapacity(0), intArray(new int[arrayTotalCapacity])
	{
		intArray[0] = 0;
	}

	int size() const { return (arrayUsedCapacity - 1); }
	int getTotalCap() const { return arrayTotalCapacity; }

	// ReSharper disable once CppInconsistentNaming
	void push_back(const int newValue)
	{
		if (arrayTotalCapacity == arrayUsedCapacity)
			doubleArraySize();

		intArray[arrayUsedCapacity] = newValue;
		arrayUsedCapacity++;
	}

	// ReSharper disable once CppInconsistentNaming
	int pop_back()
	{
		const int retVal = intArray[arrayUsedCapacity];
		intArray[arrayUsedCapacity] = 0;
		arrayUsedCapacity--;

		if ((arrayUsedCapacity <= (arrayTotalCapacity / 4)) && (arrayTotalCapacity > 10))
			halveArraySize();
		
		return retVal;
	}

	int& at(const int pos) const
	{
		if (pos >= 0 && pos <= (arrayUsedCapacity - 1))
		{
			return intArray[pos];
		}
		else
		{
			std::cerr << "Error! Tried to access element " << pos << " which is outside the array bounds.\n";
			exit(1);
		}
	}

	int& operator[](const int pos) const
	{
		return at(pos);
	}

	~SafeArrayInt()
	{
		delete [] intArray;
		std::cout << "Deleted intArray from the SafeArrayInt!\n";
	}
	
};



#endif