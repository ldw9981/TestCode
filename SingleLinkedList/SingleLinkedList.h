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

	// 포인터를 구조체에 포함시켜서 순회를 도와준다.
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
		Erase(m_pHead);
	}
		

	Node* Erase(Node* pNode)
	{
		Node* pCurr = m_pHead;
		Node* pNext = nullptr;
		while (pCurr != nullptr)
		{	
			//다음노드가 삭제할 노드인지 확인
			pNext = pCurr->pNext;
			if(pNext != pNode)
			{
				pCurr = pNext;
				continue;
			}

			if (pCurr == m_pHead)
			{
				m_pHead = pCurr->pNext;
			}
			else
			{
				pCurr->pNext = pNext->pNext;
			}
			delete pNode;
			break;
		}
		return pNext;
	}

	void Clear()
	{
		Node* pCurr = m_pHead;
		while (pCurr != nullptr)
		{
			Node* pNext = pCurr->pNext;
			delete pCurr;
			pCurr = pNext;
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
};

