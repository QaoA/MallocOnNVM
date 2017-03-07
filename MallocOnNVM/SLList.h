#ifndef __LIST_H__
#define __LIST_H__

struct SLList
{
public:
	SLList();
	~SLList();

public:
	void InitDefault();
	void InitWithKnownNode(SLList * pPrevious);
	void LinkToList(SLList * pPrevious);
	void AppendToList(SLList * pPrevious);
	void Remove();
	SLList * GetNext();
	SLList * GetPrevious();

public:
	SLList * GetNextRecovery();

public:
	SLList * m_pPrevious;
	SLList * m_pNext;
};

#define GetOffset(ContainerType,fieldName) reinterpret_cast<unsigned long>(&(reinterpret_cast<ContainerType *>(0)->fieldName))
#define GetContainer(ContainerType,fieldName,pAddress) reinterpret_cast<ContainerType *>(reinterpret_cast<unsigned long>(pAddress) - GetOffset(ContainerType,fieldName))

#endif