#pragma once
template<typename T>
class SingleLinkedList
{
public:
	struct Node
	{
		T data;
		Node* pNext = nullptr;	
	};

	// �����͸� ����ü�� ���Խ��Ѽ� ��ȸ�� �����ش�.
	struct Iterator
	{
		Node* pCurr = nullptr;

		Iterator(Node* p = nullptr)
		{
			pCurr = p;
		}
		Iterator& operator++()
		{
			pCurr = pCurr->pNext;
			return *this;
		}
		T& operator*()
		{
			return pCurr->data;
		}
		bool operator==(const Iterator& ref)
		{
			return  pCurr == ref.pCurr;
		}
		bool operator!=(const Iterator& ref)
		{
			return  pCurr != ref.pCurr;
		}
	};

	Node* m_pHead = nullptr;

	Node* PushFront(T data)
	{
		Node* pNewNode = new Node;
		pNewNode->data = data;
		if (m_pHead == nullptr)
		{
			m_pHead = pNewNode;
		
		}
		else
		{
			m_pHead->pNext = pNewNode;			
			m_pHead = pNewNode;
		}
		return pNewNode;
	}

	void PopFront()
	{
		if(m_pHead == nullptr)
			return;

		Node* pNext = m_pHead->pNext;
	}

	Node* Erase(Node* pNode)
	{
		if (pNode->pPrev != nullptr)	// �ճ�� ������ ó��
		{
			pNode->pPrev->pNext = pNode->pNext;

		}
		if (pNode->pNext != nullptr)	// �޳�� ������ ó��
		{
			pNode->pNext->pPrev = pNode->pPrev;
		}

		// Head,Tail ����
		if (pNode == m_pHead)
		{
			m_pHead = pNode->pNext;
		}
		if (pNode == m_pTail)
		{
			m_pTail = pNode->pPrev;
		}
		Node* pNodeNext = pNode->pNext;	// ������� ����
		delete pNode; // ����
		return pNodeNext;
	}

	void Clear()
	{
		Node* pCurr = m_pHead;
		while (pCurr != nullptr)
		{
			pCurr = Erase(pCurr);
		}
	}

	Iterator Begin()
	{
		return Iterator(m_pHead);
	}
	Iterator End()
	{
		return Iterator(nullptr);
	}
	/*
	RIterator RBegin()
	{
		return RIterator(m_pTail);   // ++��  pCurr = pCurr->pPrev;
	}
	RIterator REnd()
	{
		return RIterator(nullptr);
	}
	*/
};

