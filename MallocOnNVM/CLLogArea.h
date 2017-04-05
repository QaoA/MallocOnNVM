#ifndef __LOG_AREA_H__
#define __LOG_AREA_H__

class CLLogArea
{
public:
	CLLogArea();
	CLLogArea(int index, void * pNVMAddress, unsigned int size);
	~CLLogArea();

public:
	void Init(int index, void * pNVMAddress, unsigned int size);

public:
	inline int GetIndex();
	inline void * GetStartAddress();
	inline unsigned int GetAreaSize();

private:
	int m_index;
	void * m_pStartAddress;
	unsigned int m_areaSize;
};

inline int CLLogArea::GetIndex()
{
	return m_index;
}

inline void * CLLogArea::GetStartAddress()
{
	return m_pStartAddress;
}

inline unsigned int CLLogArea::GetAreaSize()
{
	return m_areaSize;
}

#endif