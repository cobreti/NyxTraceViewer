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

    auto    iterFct = [&] (const CTraceSectionId& id, const CViewTracesDisplayCache::CEntryData& data)
                        {
                            ValidatePickEntry(rcArea, id, data, result);
                        };

    m_rDisplayCache.for_each(iterFct);

    NYXTRACE(0x0, L"CViewTracePicker::getTextInRect end");

    return std::move(result);
}


void CViewTracePicker::ValidatePickEntry(   const QRectF& rcArea,
                                            const CTraceSectionId &id,
                                            const CViewTracesDisplayCache::CEntryData &data,
                                            CPickerResult& result)
{
    if (rcArea.intersects(data.itemArea()))
    {
        CViewTracePortal                tracePortal(*data.traceData(), data.lineNumber());
        CViewTraceMetrics               traceMetrics;
        QRectF                          rcIntersect = rcArea.intersected(data.itemArea());
        CViewTraceMetrics::CSubSection  subSection;

        int x = int(data.itemArea().left() + 0.5);
        int y = int(data.itemArea().top() + 0.5);
        CPickerEntry        entry(data, id.columnId());

        subSection = traceMetrics.GetTextInRect(tracePortal, id.columnId(), data.itemArea(), rcIntersect);

        entry.textInSelection() = subSection.text();
        entry.startIndex() = subSection.startIndex();
        entry.length() = subSection.length();
        entry.subRect() = subSection.subRect();

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
    m_ColumnId(columnId),
    m_StartIndex(-1),
    m_Length(0)
{

}


CViewTracePicker::CPickerEntry::CPickerEntry(const CPickerEntry &entry) :
    CViewTracesDisplayCache::CEntryData(entry),
    m_ColumnId(entry.m_ColumnId),
    m_StartIndex(entry.m_StartIndex),
    m_Length(entry.m_Length),
    m_SubRect(entry.m_SubRect)
{

}


CViewTracePicker::CPickerEntry::CPickerEntry(const CViewTracesDisplayCache::CEntryData &entryData, EViewColumnId columnId) :
    CViewTracesDisplayCache::CEntryData(entryData),
    m_ColumnId(columnId),
    m_StartIndex(-1),
    m_Length(0)
{

}


CViewTracePicker::CPickerEntry::~CPickerEntry()
{

}


const CViewTracePicker::CPickerEntry& CViewTracePicker::CPickerEntry::operator = (const CViewTracePicker::CPickerEntry& entry)
{
    CViewTracesDisplayCache::CEntryData::operator = (entry);

    m_ColumnId = entry.m_ColumnId;
    m_StartIndex = entry.m_StartIndex;
    m_Length = entry.m_Length;
    m_SubRect = entry.m_SubRect;

    return *this;
}
