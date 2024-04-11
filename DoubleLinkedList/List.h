#pragma once
template<typename T>
class List
{
public:
	struct Node
	{
		T data;
		Node* pNext=nullptr;
		Node* pPrev=nullptr;

		
	};

	// 포인터를 구조체에 포함시켜서 순회를 도와준다.
	struct Iterator
	{
		Node* pCurr = nullptr;

		Iterator(Node* p=nullptr)
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
	Node* m_pTail = nullptr;

	Node* PushBack(T data)
	{	
		Node* pNewNode = new Node;
		pNewNode->data = data;
		if (m_pTail == nullptr || m_pHead == nullptr)
		{
			m_pHead = pNewNode;
			m_pTail = pNewNode;
		}
		else
		{
		 	m_pTail->pNext = pNewNode;
			pNewNode->pPrev = m_pTail;
			m_pTail= pNewNode;
		}
		
		return pNewNode;
	}

	void Erase(Node* pNode)
	{
		if (pNode->pPrev != nullptr)
		{
			pNode->pPrev->pNext = pNode->pNext;
		}

		if (pNode->pNext != nullptr)
		{
			pNode->pNext->pPrev = pNode->pPrev;
		}

		delete pNode;
	}

	Iterator Begin()
	{
		return Iterator(m_pHead);
	}
	Iterator End()
	{
		return Iterator(nullptr);
	}
	
};

