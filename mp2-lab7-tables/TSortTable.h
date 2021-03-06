#pragma once
#include <iostream>
#include "TTable.h"
#include "TScanTable.h"

class TSortTable : public TScanTable
{
public:
	//TSortTable(TScanTable& st) : TScanTable(st.GetSize())
	//{

	//}
	bool Find(TKey key)
	{
		int begin = 0, end = DataCount - 1, mid;
		while (begin <= end)
		{
			eff++;
			mid = (begin + end) / 2;
			if (key < arr[mid].key)
			{
				end = mid - 1;
			}
			else if (key > arr[mid].key)
			{
				begin = mid + 1;
			}
			else
			{
			curr = mid;
			return true;
			}
		}
		curr = begin;
		return false;
	}
	bool Insert(TRecord rec)
	{
		if (IsFull()) return false;
		if (Find(rec.key)) return false;
		for (int i = DataCount - 1; i >= curr; i--)
		{
			arr[i + 1] = arr[i];
			eff++;
		}
		arr[curr] = rec;
		DataCount++;
		return true;
	}
	bool Delete(TKey key)
	{
		if (!Find(key)) return false;
		for (int i = curr; i < DataCount; i++)
		{
			arr[i] = arr[i + 1];
			eff++;
		}
		DataCount--;
		return true;
	}

	void qsort(int first, int last);
};
void TSortTable::qsort(int first, int last)
{
	TKey mid = arr[(first + last) / 2].key;
	int f = first, l = last;
	while (f < l)
	{
		while (arr[f].key < mid)
		{
			f++; eff++;
		}
		while (arr[l].key > mid)
		{
			l--; eff++;
		}
		if (f <= l)
		{
			TRecord tmp = arr[f];
			arr[f] = arr[l];
			arr[l] = tmp;
			f++; l--; eff++;
		}
	}
	if (first < l) qsort(first, l);
	if (f < last) qsort(f, last);
}