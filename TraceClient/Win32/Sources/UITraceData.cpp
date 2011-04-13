#include "UITraceData.hpp"


/**
 *
 */
CUITraceData::CUITraceData( CTraceData* pTraceData ) :
m_pTraceData(pTraceData)
{
}


/**
 *
 */
CUITraceData::~CUITraceData()
{
}


/**
 *
 */
//CTraceData* CUITraceData::TraceData() const
//{
//	return m_pTraceData;
//}


/**
 *
 */
const wchar_t* CUITraceData::Data() const
{
	return m_pTraceData->Data()->CStr();
}


/**
 *
 */
const wchar_t* CUITraceData::ThreadId() const
{
	return m_pTraceData->ThreadId()->CStr();
}


/**
 *
 */
const wchar_t* CUITraceData::TickCount() const
{
	return m_pTraceData->TickCount()->CStr();
}

