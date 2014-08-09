#ifndef TRACESECTIONID_H
#define TRACESECTIONID_H

#include "TraceData.hpp"
#include "ViewColumnId.hpp"


class CTraceSectionId
{
public:
    CTraceSectionId( const TraceClientCore::CTraceData::CIdentifier& traceId, EViewColumnId colId );
    CTraceSectionId( const CTraceSectionId& sectionId );
    ~CTraceSectionId();

    const TraceClientCore::CTraceData::CIdentifier& traceIdentifier() const     { return m_TraceId; }
    const EViewColumnId& columnId() const                                       { return m_ColumnId; }

    const CTraceSectionId& operator = (const CTraceSectionId& sectionId);
    bool operator == (const CTraceSectionId& sectionId) const;
    bool operator != (const CTraceSectionId& sectionId) const;
    bool operator < (const CTraceSectionId& sectionId) const;
    bool operator <= (const CTraceSectionId& sectionId) const;
    bool operator > (const CTraceSectionId& sectionId) const;
    bool operator >= (const CTraceSectionId& sectionId) const;

protected:

    TraceClientCore::CTraceData::CIdentifier        m_TraceId;
    EViewColumnId                                   m_ColumnId;

};


#endif // TRACESECTIONID_H
