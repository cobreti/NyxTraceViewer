#ifndef __VIEWITEM_TRACEDATA_HPP__
#define __VIEWITEM_TRACEDATA_HPP__

#include <Nyx.hpp>
#include <NyxMemPoolObj.hpp>
#include <NyxRange.hpp>
#include "ViewItem.hpp"
#include "TraceData.hpp"

/**
 *
 */
class CViewItem_TraceData : public CViewItemMemPoolObj
{
public:
    CViewItem_TraceData(Nyx::CMemoryPool* pMemPool, const TraceClientCore::CTraceData* pTraceData);
    virtual ~CViewItem_TraceData();

    virtual bool IsOfKind( EViewItemType type ) const { return type == eViewItem_TraceData; }

    virtual void dbgOutputInfo();

    const TraceClientCore::CTraceData* TraceData() const             { return m_pTraceData; }

    virtual const Nyx::CWString& ModuleName() const;
    virtual const Nyx::CWString& TickCount() const;

    const Nyx::CRange&      TextRange() const           { return m_TextRange; }
    Nyx::CRange&            TextRange()                 { return m_TextRange; }

    virtual const QString GetItemString(const EItemIndex& itemIndex) const;

protected:

    void ApproximateHeight();

protected:

    const TraceClientCore::CTraceData*          m_pTraceData;
    Nyx::CRange                                 m_TextRange;
};

#endif // __VIEWITEM_TRACEDATA_HPP__
