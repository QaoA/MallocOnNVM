#include "CLBlock.h"
#include "CLBlockArea.h"

NS_BEGIN

CLBlock::CLBlock(SLNVMBlock * pNVMBlock,CLBlockArea * pOwner):
m_pNVMBlock(pNVMBlock),
m_owner(pOwner)
{
}

CLBlock::~CLBlock()
{
}

NS_END