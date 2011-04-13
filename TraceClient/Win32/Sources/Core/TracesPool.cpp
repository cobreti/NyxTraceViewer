#include "TracesPool.hpp"


/**
 *
 */
CTracesPool::CTracesPool(const wchar_t* wszName)
{
	m_refName = Nyx::CString::Alloc(wszName);
}


/**
 *
 */
CTracesPool::~CTracesPool()
{
}


/**
 *
 */
const Nyx::CStringRef CTracesPool::Name() const
{
	return m_refName;
}
