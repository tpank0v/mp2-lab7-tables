#pragma once
#include <iostream>
#include "TTable.h"

using namespace std;

class TArrayTable : public TTable
{
protected:
	TRecord* arr;
	int size, curr;
public:
	TArrayTable(int _size = 10)
	{
		arr = new TRecord[_size];
		size = _size;
		curr = -1;
	}
	void GoNext() 
	{ 
		curr++; 
	}
	void Reset() 
	{
		curr = 0;
	}
	bool IsEnd()
	{
		size == DataCount; 
	}
	bool IsFull()
	{
		return DataCount >= size;
	}
	TKey GetKey(TKey key)
	{
		return GetKey(curr);
	}
	TValue GetVal(TKey key)
	{
		return GetVal(curr);
	}
	};