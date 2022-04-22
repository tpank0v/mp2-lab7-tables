#pragma once
#include <iostream>
#include "TTable.h"

using namespace std;

class THashTable : public TTable
{
protected:
	virtual int HashFunc(TKey key)
	{
		return key;
	}
};