#ifndef VIEWTRACESDISPLAYCACHE_H
#define VIEWTRACESDISPLAYCACHE_H

#include "TraceData.hpp"
#include "ViewColumnId.hpp"

#include <QRectF>
#include <map>


class CViewTracesDisplayCache
{
public:

    class CEntryData
    {
    public:
        CEntryData();
        CEntryData(const CEntryData& entryData);
        ~CEntryData();


        const CEntryData& operator = (const CEntryData& entryData);


        const QRectF&       itemArea() const            { return m_ItemArea; }
        QRectF&             itemArea()                  { return m_ItemArea; }

        TraceClientCore::CTraceData*        traceData() const       { return m_pTraceData; }
        TraceClientCore::CTraceData*&       traceData()             { return m_pTraceData; }

    protected:

        QRectF                              m_ItemArea;
        TraceClientCore::CTraceData*        m_pTraceData;
    };


    class CEntryId
    {
    public:
        CEntryId( const TraceClientCore::CTraceData::CIdentifier& traceId, EViewColumnId colId );
        CEntryId( const CEntryId& entryId );
        ~CEntryId();

        const CEntryId& operator = (const CEntryId& entryId);
        bool operator == (const CEntryId& entryId) const;
        bool operator != (const CEntryId& entryId) const;
        bool operator < (const CEntryId& entryId) const;
        bool operator > (const CEntryId& entryId) const;

    protected:

        TraceClientCore::CTraceData::CIdentifier        m_TraceId;
        EViewColumnId                                   m_ColumnId;

    };


public:
    CViewTracesDisplayCache();
    virtual ~CViewTracesDisplayCache();

    void Clear();

    bool hasEntry(const CEntryId& id) const                             { return m_Entries.count(id) > 0; }
    CEntryData& operator[] ( const CEntryId& id )                       { return m_Entries[id]; }
    void setEntry(const CEntryId& id, const CEntryData& data);


protected:

    typedef     std::map<CEntryId, CEntryData>          TEntriesTable;


protected:

    TEntriesTable           m_Entries;
};


#endif // VIEWTRACESDISPLAYCACHE_H
