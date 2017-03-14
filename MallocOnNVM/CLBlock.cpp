#include "CLBlock.h"
#include "CLBlockArea.h"

CLBlock::CLBlock(SLNVMBlock * pNVMBlock,CLBlockArea * pOwner):
m_pNVMBlock(pNVMBlock),
m_owner(pOwner)
{
}

CLBlock::~CLBlock()
{
}
