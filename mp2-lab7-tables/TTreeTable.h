#pragma once
#pragma once
#include "TTable.h"
#include "Stack.h"
#include <iostream>

struct TTreeNode
{
	TRecord rec;
	TTreeNode* pLeft, * pRight;

	TTreeNode(TRecord rec)
	{
		this->rec = rec;
		pLeft = nullptr;
		pRight = nullptr;
	}
	TTreeNode()
	{
		pLeft = nullptr;
		pRight = nullptr;
	}
};


class TTreeTable : public TTable
{
protected:
	TTreeNode* pRoot, * pCurr, * pPrev;
	TStack<TTreeNode> st;
	int countPos;

	void DeleteRec(TTreeNode* node)
	{
		if (node->pLeft != nullptr) DeleteRec(node->pLeft);
		if (node->pRight != nullptr) DeleteRec(node->pRight);
		delete node;
	}

	void PrintRec(TTreeNode* node, std::ostream& os, int level)
	{
		if (node == nullptr) return;
		for (int i = 0; i < level; i++) os << " ";
		os << node->rec.key;
		level++;
		PrintRec(node->pRight, os, level);
		PrintRec(node->pLeft, os, level);
		level--;
	}

public:
	TTreeTable();
	~TTreeTable() { Clear(); }

	bool IsFull() const;

	bool Find(TKey key);
	bool Insert(TRecord rec);
	bool Delete(TKey key);

	void Reset();
	void GoNext();
	bool IsEnd();

	TRecord GetCurrentRecord(){ return pCurr->rec; }
	void SetCurrentRecord(TValue value){ pCurr->rec.val = value; }

	void Clear() { DeleteRec(pRoot); }
	void Print(std::ostream stream) { PrintRec(pRoot, stream, 0); }

};

TTreeTable::TTreeTable() : TTable()
{
	pRoot = nullptr;
	pCurr = nullptr;
	pPrev = nullptr;
	countPos = 0;
}


bool TTreeTable::IsFull() const
{
	try { new TTreeNode(); }
	catch (...) { return true; }
	return false;
}

bool TTreeTable::Find(TKey key)
{
	pCurr = pRoot;
	pPrev = nullptr;
	while (pCurr != nullptr)
	{
		eff++;
		if (pCurr->rec.key == key) return true;
		else if (pCurr->rec.key < key)
		{
			pPrev = pCurr;
			pCurr = pCurr->pRight;
		}
		else
		{
			pPrev = pCurr;
			pCurr = pCurr->pLeft;
		}
	}
	pCurr = pPrev;
	return false;
}

bool TTreeTable::Insert(TRecord rec)
{
	if (IsFull() || Find(rec.key)) return false;
	TTreeNode* newNode = new TTreeNode(rec);
	if (rec.key > pCurr->rec.key) pCurr->pRight = newNode;
	else pCurr->pLeft = newNode;
	return true;
}

bool TTreeTable::Delete(TKey key)
{
	if (!Find(key)) return false;
	TTreeNode* pDel = pCurr;
	if (pCurr->pRight == nullptr)
	{
		if (pPrev == nullptr) pRoot = pRoot->pLeft; 
		else
		{
			if (pCurr->rec.key > pPrev->rec.key) pPrev->pRight = pCurr->pLeft;
			else pPrev->pLeft = pCurr->pLeft;
		}
	}
	else if (pCurr->pLeft == nullptr)
	{
		if (pPrev == nullptr) pRoot = pRoot->pRight;
		else
		{
			if (pCurr->rec.key > pPrev->rec.key) pPrev->pRight = pCurr->pRight;
			else pPrev->pLeft = pCurr->pRight;
		}
	}
	else
	{
		TTreeNode* temp = pCurr->pLeft;
		pPrev = pCurr;
		while (temp->pRight != nullptr)
		{
			eff++;
			pPrev = temp;
			temp = temp->pRight;
		}
		pCurr->rec = temp->rec;
		if (pPrev != pCurr) pPrev->pRight = temp->pLeft;
		else pPrev->pLeft = temp->pLeft;
		pDel = temp;
	}
	eff++;
	delete pDel;
	DataCount--;
	return true;
}

inline void TTreeTable::Reset()
{
	while (!st.IsEmpty()) st.Pop();
	pCurr = pRoot;
	while (pCurr != nullptr) st.Push(pCurr);
	pCurr = st.Top();
	countPos = 0;
}

inline void TTreeTable::GoNext()
{
	st.Pop();
	if (pCurr->pRight != nullptr)
	{
		pCurr = pCurr->pRight;
		while (pCurr != nullptr)
		{
			st.Push(pCurr);
			pCurr = pCurr->pLeft;
		}
		pCurr = st.Top();
	}
	else pCurr = st.Top();
}

inline bool TTreeTable::IsEnd()
{
	return countPos == DataCount;
}