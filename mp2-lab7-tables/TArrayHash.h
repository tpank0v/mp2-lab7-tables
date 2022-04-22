#pragma once
#include <iostream>
#include "THashTable.h"

using namespace std;
class TArrayHash : public THashTable
{
protected: 
	TRecord free, del;
	TRecord* mas;
	int tsize;
	int step;
public:
	TArrayHash(int _size = 10, int _step = 1)
	{
		mas = new TRecord[_size];
		tsize = _size;
		step = _step;
		free.key = -1;
		for (int i = 0; i < tsize; i++)
		{
			mas[i] = free;
		}
	}
};