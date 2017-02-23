#include "CLSpinLock.h"
#include <cassert>

CLSpinLock::CLSpinLock():
m_lock(false)
{
}

CLSpinLock::~CLSpinLock()
{
}

bool CLSpinLock::TryLock()
{
	return __sync_bool_compare_and_swap(&m_lock, false, true);
}

void CLSpinLock::Lock()
{
	while (!TryLock());
}

void CLSpinLock::Unlock()
{
	assert(m_lock);
	__sync_bool_compare_and_swap(&m_lock, true, false);
}