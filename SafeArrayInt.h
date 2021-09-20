#ifndef SAFE_ARRAY_INT_H
#define SAFE_ARRAY_INT_H

#include <cassert>

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
	}

	int getUsedCap() const { return arrayUsedCapacity; }
	int getTotalCap() const { return arrayTotalCapacity; }

	// ReSharper disable once CppInconsistentNaming
	void push_back(const int newValue)
	{
		if (arrayTotalCapacity == arrayUsedCapacity)
			doubleArraySize();
		
		arrayUsedCapacity++;
		intArray[arrayUsedCapacity] = newValue;
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
};

#endif