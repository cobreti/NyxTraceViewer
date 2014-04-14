#include "ViewTracePicker.h"
#include "ViewTracesDisplayCache.h"
#include "ViewTracePortal.h"
#include "ViewTraceMetrics.h"

#include <Nyx.hpp>

CViewTracePicker::CViewTracePicker(const CViewTracesDisplayCache &rDisplayCache) :
    m_rDisplayCache(rDisplayCache)
{

}


CViewTracePicker::~CViewTracePicker()
{

}



CViewTracePicker::CPickerResult CViewTracePicker::pick(const QRectF &rcArea)
{
    QString                 text;
    CPickerResult           result;

    NYXTRACE(0x0, L"CViewTracePicker::getTextInRect begin");

    auto    iterFct = [&] (const CViewTracesDisplayCache::CEntryId& id, const CViewTracesDisplayCache::CEntryData& data)
                        {
                            ValidatePickEntry(rcArea, id, data, result);
                        };

    m_rDisplayCache.for_each(iterFct);

    NYXTRACE(0x0, L"CViewTracePicker::getTextInRect end");

    return std::move(result);
}


void CViewTracePicker::ValidatePickEntry(   const QRectF& rcArea,
                                            const CViewTracesDisplayCache::CEntryId &id,
                                            const CViewTracesDisplayCache::CEntryData &data,
                                            CPickerResult& result)
{
    if (rcArea.intersects(data.itemArea()))
    {
        CViewTracePortal    tracePortal(*data.traceData(), data.lineNumber());
        CViewTraceMetrics   traceMetrics;
        QRectF              rcIntersect = rcArea.intersected(data.itemArea());

        int x = int(data.itemArea().left() + 0.5);
        int y = int(data.itemArea().top() + 0.5);
        CPickerEntry        entry(data, id.columnId());

        entry.textInSelection() = traceMetrics.GetTextInRect(tracePortal, id.columnId(), data.itemArea(), rcIntersect);

        (*result.m_pEntries)[y][x] = entry;

        NYXTRACE(0x0, L"-- "
                 << Nyx::CTF_AnsiText(tracePortal.GetColumnText(id.columnId()).toStdString().c_str())
                 << L" : top = "
                 << Nyx::CTF_Float(data.itemArea().top())
                 << L" : left = "
                 << Nyx::CTF_Float(data.itemArea().left())
                 << L" : textInSelection = "
                 << Nyx::CTF_AnsiText(entry.textInSelection().toStdString().c_str()));
    }
}


CViewTracePicker::CPickerResult::CPickerResult() :
    m_pEntries( new  TEntriesTable() )
{

}


CViewTracePicker::CPickerResult::CPickerResult(CViewTracePicker::CPickerResult&& result) :
    m_pEntries(result.m_pEntries)
{
    result.m_pEntries = NULL;
}


CViewTracePicker::CPickerResult::~CPickerResult()
{
    delete m_pEntries;
}


CViewTracePicker::CPickerEntry::CPickerEntry(EViewColumnId columnId) :
    CViewTracesDisplayCache::CEntryData(),
    m_ColumnId(columnId)
{

}


CViewTracePicker::CPickerEntry::CPickerEntry(const CPickerEntry &entry) :
    CViewTracesDisplayCache::CEntryData(entry),
    m_ColumnId(entry.m_ColumnId)
{

}


CViewTracePicker::CPickerEntry::CPickerEntry(const CViewTracesDisplayCache::CEntryData &entryData, EViewColumnId columnId) :
    CViewTracesDisplayCache::CEntryData(entryData),
    m_ColumnId(columnId)
{

}


CViewTracePicker::CPickerEntry::~CPickerEntry()
{

}


const CViewTracePicker::CPickerEntry& CViewTracePicker::CPickerEntry::operator = (const CViewTracePicker::CPickerEntry& entry)
{
    CViewTracesDisplayCache::CEntryData::operator = (entry);

    m_ColumnId = entry.m_ColumnId;

    return *this;
}
