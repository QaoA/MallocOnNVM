#include "CLRadixTreeNode.h"
#include "CLCriticalSection.h"
#include <cassert>

CLRadixTreeNode::CLRadixTreeNode(const unsigned int height) :
m_slots(SLOT_COUNT),
m_height(height),
m_count(0)
{
}

CLRadixTreeNode::~CLRadixTreeNode()
{
	//for (int i = 0; i < SLOT_COUNT; ++i)
	//{
	//	delete m_slots[i].m_pNextLayerNode;
	//}
}

void CLRadixTreeNode::Insert(unsigned long key, void * pLeaf, unsigned long mask)
{
	unsigned long index = ((key & mask) >> (m_height*SLOT_COUNT_BIT));
	if (m_height != 0)
	{
		{
			CLCriticalSection cs(&m_lock);
			if (m_slots[index].m_pNextLayerNode == nullptr)
			{
				m_slots[index].m_pNextLayerNode = new CLRadixTreeNode(m_height - 1);
				++m_count;
			}
		}
		m_slots[index].m_pNextLayerNode->Insert(key, pLeaf, mask >> SLOT_COUNT_BIT);
	}
	else
	{
		CLCriticalSection cs(&m_lock);
		assert(m_slots[index].m_leaf == nullptr);
		m_slots[index].m_leaf = pLeaf;
		++m_count;
	}
}

void * CLRadixTreeNode::Remove(unsigned long key, unsigned long mask)
{
	unsigned long index = ((key & mask) >> (m_height*SLOT_COUNT_BIT));
	if (m_height != 0)
	{
		assert(m_slots[index].m_pNextLayerNode != nullptr);
		void * pLeaf = m_slots[index].m_pNextLayerNode->Remove(key, mask >> SLOT_COUNT_BIT);
		{
			CLCriticalSection cs(&m_lock);
			if (m_slots[index].m_pNextLayerNode->m_count == 0)
			{
				delete m_slots[index].m_pNextLayerNode;
				m_slots[index].m_pNextLayerNode = nullptr;
				--m_count;
			}
		}
		return pLeaf;
	}
	else
	{
		CLCriticalSection cs(&m_lock);
		void * pLeaf = m_slots[index].m_leaf;
		m_slots[index].m_leaf = nullptr;
		--m_count;
		return pLeaf;
	}
}

void * CLRadixTreeNode::Get(unsigned long key, unsigned long mask)
{
	unsigned long index = ((key & mask) >> (m_height*SLOT_COUNT_BIT));
	if (m_height != 0)
	{
		assert(m_slots[index].m_pNextLayerNode != nullptr);
		void * pLeaf = m_slots[index].m_pNextLayerNode->Get(key, mask >> SLOT_COUNT_BIT);
		return pLeaf;
	}
	else
	{
		return m_slots[index].m_leaf;
	}
}