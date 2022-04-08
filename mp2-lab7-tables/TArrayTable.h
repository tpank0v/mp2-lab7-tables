#pragma once
#include <iostream>
#include "TTable.h"

using namespace std;

class TArrayTable : TTable
{
protected:
	TRecord* mas;
	int size, curr;
public:
	TArrayTable(int _size = 10)
	{
		mas = new TRecord[_size];
		size = _size;
		curr = -1;
	}
	virtual bool IsFull()
	{
		return DataCount >= size;
	}
	virtual TKey GetKey(TKey key)
	{
		return GetKey(curr);
	}
	virtual TValue GetVal(TValue val)
	{
		//return GetVal(curr);
	}
	};