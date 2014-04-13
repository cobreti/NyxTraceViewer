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
        virtual ~CEntryData();


        const CEntryData& operator = (const CEntryData& entryData);


        const QRectF&       itemArea() const            { return m_ItemArea; }
        QRectF&             itemArea()                  { return m_ItemArea; }

        TraceClientCore::CTraceData*        traceData() const       { return m_pTraceData; }
        TraceClientCore::CTraceData*&       traceData()             { return m_pTraceData; }

        const qreal&        columnWidth() const         { return m_ColumnWidth; }
        qreal&              columnWidth()               { return m_ColumnWidth; }

        const Nyx::UInt32&  lineNumber() const          { return m_LineNumber; }
        Nyx::UInt32&        lineNumber()                { return m_LineNumber; }

    protected:

        QRectF                              m_ItemArea;
        TraceClientCore::CTraceData*        m_pTraceData;
        qreal                               m_ColumnWidth;
        Nyx::UInt32                         m_LineNumber;
    };


    class CEntryId
    {
    public:
        CEntryId( const TraceClientCore::CTraceData::CIdentifier& traceId, EViewColumnId colId );
        CEntryId( const CEntryId& entryId );
        ~CEntryId();

        const TraceClientCore::CTraceData::CIdentifier& traceIdentifier() const     { return m_TraceId; }
        const EViewColumnId& columnId() const                                       { return m_ColumnId; }

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

    template <class _FUNCTION>
    void for_each( _FUNCTION fct ) const
    {
        auto cbfct = [&] (std::pair<const CEntryId, const CEntryData> value)
                        {
                            fct(value.first, value.second);
                        };

        std::for_each(m_Entries.begin(), m_Entries.end(), cbfct);
    }

protected:

    typedef     std::map<CEntryId, CEntryData>          TEntriesTable;


protected:

    TEntriesTable           m_Entries;
};


#endif // VIEWTRACESDISPLAYCACHE_H
