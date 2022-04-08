#pragma once
#include <iostream>
#include <string.h>
using namespace std;
typedef int TKey;
typedef string TValue;

struct TRecord
{
	TKey key;
	TValue val;
};
class TTable
{
protected:
	int DataCount;
	int eff;
public:
	TTable()
	{
		DataCount = 0;
		eff = 0;
	}
	virtual ~TTable()
	{}
	int GetDataCount() const
	{
		return DataCount;
	}
	int GetEff() const
	{
		return eff;
	}
	void ClearEff()
	{
		eff = 0;
	}
	bool IsEmpty()
	{
		return DataCount == 0;
	}
	virtual bool IsFull() const = 0;
	virtual bool Find(TKey key) = 0;
	virtual bool Insert(TRecord rec) = 0;
	virtual bool Delete(TKey key) = 0;

	virtual void Reser() = 0;
	virtual void GoNext() = 0;
	virtual bool IsEnd() = 0;

	virtual TKey GetKey() const = 0;
	virtual TValue GetValue() = 0;

	friend ostream& operator<<(ostream& os, TTable& t)
	{
		for (t.Reser(); !t.IsEnd(); t.GoNext())
		{
			cout << t.GetKey();
		}
		return os;
	}
};