#ifndef VIEWTRACESDISPLAYCACHE_H
#define VIEWTRACESDISPLAYCACHE_H

#include "TraceData.hpp"
#include "ViewColumnId.hpp"
#include "ViewItemMargins.hpp"
#include "TraceSectionId.h"


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

        const CViewItemMargins&     margins() const     { return m_Margins; }
        CViewItemMargins&           margins()           { return m_Margins; }

    protected:

        QRectF                              m_ItemArea;
        TraceClientCore::CTraceData*        m_pTraceData;
        qreal                               m_ColumnWidth;
        Nyx::UInt32                         m_LineNumber;
        CViewItemMargins                    m_Margins;
    };



public:
    CViewTracesDisplayCache();
    virtual ~CViewTracesDisplayCache();

    void Clear();

    bool hasEntry(const CTraceSectionId& id) const                             { return m_Entries.count(id) > 0; }
    CEntryData& operator[] ( const CTraceSectionId& id )                       { return m_Entries[id]; }
    void setEntry(const CTraceSectionId& id, const CEntryData& data);

    template <class _FUNCTION>
    void for_each( _FUNCTION fct ) const
    {
        auto cbfct = [&] (std::pair<const CTraceSectionId, const CEntryData> value)
                        {
                            fct(value.first, value.second);
                        };

        std::for_each(m_Entries.begin(), m_Entries.end(), cbfct);
    }

protected:

    typedef     std::map<CTraceSectionId, CEntryData>          TEntriesTable;


protected:

    TEntriesTable           m_Entries;
};


#endif // VIEWTRACESDISPLAYCACHE_H
