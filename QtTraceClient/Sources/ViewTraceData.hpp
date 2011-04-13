#ifndef VIEWTRACEDATA_HPP
#define VIEWTRACEDATA_HPP

#include <QSizeF>

#include <Nyx.hpp>
#include <NyxMemPoolObj.hpp>
#include "DocTraceData.hpp"

class CViewTraceData : public Nyx::CMemPoolObj<>
{
    typedef     Nyx::CMemPoolObj<>      BaseType;

public:
    CViewTraceData( Nyx::CMemoryPool* pMemPool );
    CViewTraceData( Nyx::CMemoryPool* pMemPool, const CDocTraceData* pDocTraceData, const QSizeF& lineSize );
    virtual ~CViewTraceData();

    const QSizeF&   Size() const    { return m_Size; }
    QSizeF&         Size()          { return m_Size; }

	bool			Marked() const	{ return m_bMarked; }
	bool&			Marked()		{ return m_bMarked; }

    const CDocTraceData*       DocTraceData() const        { return m_pDocTraceData; }

protected:

    const CDocTraceData*        m_pDocTraceData;
    QSizeF                      m_Size;
    bool						  m_bMarked;
};

#endif // VIEWTRACEDATA_HPP
