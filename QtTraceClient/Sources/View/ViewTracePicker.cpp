#include "ViewTracePicker.h"
#include "ViewTracesDisplayCache.h"
#include "ViewTracePortal.h"

#include <Nyx.hpp>

CViewTracePicker::CViewTracePicker(const CViewTracesDisplayCache &rDisplayCache) :
    m_rDisplayCache(rDisplayCache)
{

}


CViewTracePicker::~CViewTracePicker()
{

}



CViewTracePicker::CPickerResult CViewTracePicker::getTextInRect(const QRectF &rcArea)
{
    QString                 text;
    CPickerResult           result;

    NYXTRACE(0x0, L"CViewTracePicker::getTextInRect begin");

    auto    iterFct = [&] (const CViewTracesDisplayCache::CEntryId& id, const CViewTracesDisplayCache::CEntryData& data)
                        {
                            if (rcArea.intersects(data.itemArea()))
                            {
                                CViewTracePortal    tracePortal(*data.traceData(), data.lineNumber());

                                int x = int(data.itemArea().left() + 0.5);
                                int y = int(data.itemArea().top() + 0.5);
                                CPickerEntry        entry(data, id.columnId());

                                (*result.m_pEntries)[y][x] = entry;

                                NYXTRACE(0x0, L"-- "
                                         << Nyx::CTF_AnsiText(tracePortal.GetColumnText(id.columnId()).toStdString().c_str())
                                         << L" : top = "
                                         << Nyx::CTF_Float(data.itemArea().top())
                                         << L" : left = "
                                         << Nyx::CTF_Float(data.itemArea().left()));
                            }
                        };

    m_rDisplayCache.for_each(iterFct);

    NYXTRACE(0x0, L"CViewTracePicker::getTextInRect end");

//    std::for_each( result.m_Entries.begin(), result.m_Entries.end(), [&] (std::pair<int, CPickerResult::TEntriesRow> pair)
//        {
//            std::for_each( pair.second.begin(), pair.second.end(), [&] (std::pair<int, CPickerEntry> values)
//            {
//                CPickerEntry&        entry = values.second;
//                CViewTracePortal    tracePortal(*entry.traceData(), entry.lineNumber());

//                NYXTRACE(0x0, L"==> "
//                         << Nyx::CTF_AnsiText(tracePortal.GetColumnText(entry.columnId()).toStdString().c_str())
//                         << L" : top = "
//                         << Nyx::CTF_Float(pair.first)
//                         << L" : left = "
//                         << Nyx::CTF_Float(values.first) );

//            });
//        });

    return std::move(result);
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
