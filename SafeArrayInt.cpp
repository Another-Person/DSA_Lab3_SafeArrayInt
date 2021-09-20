#include "SafeArrayInt.h"

void SafeArrayInt::doubleArraySize()
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

void SafeArrayInt::halveArraySize()
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

SafeArrayInt::SafeArrayInt()  : arrayTotalCapacity(10), arrayUsedCapacity(0), intArray(new int[arrayTotalCapacity])
{
	intArray[0] = 0;
}


// ReSharper disable once CppInconsistentNaming
void SafeArrayInt::push_back(const int newValue)
{
	if (arrayTotalCapacity == arrayUsedCapacity)
		doubleArraySize();

	intArray[arrayUsedCapacity] = newValue;
	arrayUsedCapacity++;
}

// ReSharper disable once CppInconsistentNaming
int SafeArrayInt::pop_back()
{
	const int retVal = intArray[arrayUsedCapacity];
	intArray[arrayUsedCapacity] = 0;
	arrayUsedCapacity--;

	if ((arrayUsedCapacity <= (arrayTotalCapacity / 4)) && (arrayTotalCapacity > 10))
		halveArraySize();
		
	return retVal;
}


int& SafeArrayInt::at(const int pos) const
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

SafeArrayInt::~SafeArrayInt()
{
	delete [] intArray;
	std::cout << "Deleted intArray from the SafeArrayInt!\n";
}