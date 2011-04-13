#ifndef _UITRACEDATA_HPP_
#define _UITRACEDATA_HPP_

#include "NyxRefCount_Impl.hpp"
#include "NyxRef.hpp"
#include "TraceData.hpp"


DECLARE_OBJECTREF(CUITraceData)

class CUITraceData : public Nyx::CRefCount_Impl<>
{
public: // public methods
	CUITraceData( CTraceData* pTraceData );
	virtual ~CUITraceData();

	//CTraceData* TraceData() const;

	const wchar_t* Data() const;
	const wchar_t* ThreadId() const;
	const wchar_t* TickCount() const;

protected: // protected members

	CTraceData*		m_pTraceData;
};


#endif // _UITRACEDATA_HPP_
