#ifndef __VIEWITEM_TRACEDATA_HPP__
#define __VIEWITEM_TRACEDATA_HPP__

#include <Nyx.hpp>
#include <NyxMemPoolObj.hpp>
#include "ViewItem.hpp"
#include "TraceData.hpp"

/**
 *
 */
class CViewItem_TraceData : public Nyx::CMemPoolObj<CViewItem>
{
    typedef     Nyx::CMemPoolObj<CViewItem>     BaseType;

public:
    CViewItem_TraceData(Nyx::CMemoryPool* pMemPool, const TraceClientCore::CTraceData* pTraceData);
    virtual ~CViewItem_TraceData();

    virtual bool IsOfKind( EViewItemType type ) const { return type == eViewItem_TraceData; }

    virtual void dbgOutputInfo();

//    const CDocTraceData* DocTraceData() const      { return m_pDocTraceData; }
    const TraceClientCore::CTraceData* TraceData() const             { return m_pTraceData; }

protected:

    //const CDocTraceData*       m_pDocTraceData;
    const TraceClientCore::CTraceData*           m_pTraceData;
};

#endif // __VIEWITEM_TRACEDATA_HPP__
