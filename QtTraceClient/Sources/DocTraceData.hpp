#ifndef DOCTRACEDATA_HPP
#define DOCTRACEDATA_HPP

#include "TraceData.hpp"
#include <NyxMemPoolObj.hpp>

DECLARE_OBJECTREF(CDocTraceData)


/**
 *
 */
class CDocTraceData : public Nyx::CMemPoolObj<>
{
    typedef     Nyx::CMemPoolObj<>      BaseType;

public:
    CDocTraceData(Nyx::CMemoryPool* pMemPool);
    CDocTraceData( Nyx::CMemoryPool* pMemPool, const TraceClientCore::CTraceData* pData );
    virtual ~CDocTraceData();

    const TraceClientCore::CTraceData* TraceData() const        { return m_pTraceData; }

protected:

    const TraceClientCore::CTraceData*      m_pTraceData;
};

#endif // DOCTRACEDATA_HPP
