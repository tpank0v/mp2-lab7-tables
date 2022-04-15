#pragma once
#include <iostream>
#include "TTable.h"
#include "TArrayTable.h"

class TScanTable : public TArrayTable
{
public:
	TScanTable(int s = 100) : TArrayTable() {}
	bool Find(TKey key)
	{
		for (int i = 0; i < DataCount; i++)
		{
			eff++;
			if (arr[i].key == key)
			{
				curr = i;
				return true;
			}
			else return false;
		}
	}
	bool Insert(TRecord rec)
	{
		if (IsFull())
			return false;
		if (Find(rec.key))
				return false;
		arr[DataCount] = rec;
		eff++;
		DataCount++;
	}
	bool Delete(TKey key)
	{
		if (!Find(key)) return false;
		arr[curr] = arr[DataCount - 1];
		DataCount--;
		eff++;
		return true;
	}
};
