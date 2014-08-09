#include "ViewTracesDisplayCache.h"

#include <algorithm>


CViewTracesDisplayCache::CViewTracesDisplayCache()
{

}


CViewTracesDisplayCache::~CViewTracesDisplayCache()
{

}


void CViewTracesDisplayCache::Clear()
{
    m_Entries.clear();
}


void CViewTracesDisplayCache::setEntry(const CTraceSectionId &id, const CEntryData &data)
{
    m_Entries[id] = data;
}



CViewTracesDisplayCache::CEntryData::CEntryData() :
    m_pTraceData(NULL),
    m_ColumnWidth(0),
    m_LineNumber(0)
{

}


CViewTracesDisplayCache::CEntryData::~CEntryData()
{

}


CViewTracesDisplayCache::CEntryData::CEntryData(const CEntryData &entryData) :
    m_ItemArea(entryData.m_ItemArea),
    m_pTraceData(entryData.m_pTraceData),
    m_ColumnWidth(entryData.m_ColumnWidth),
    m_LineNumber(entryData.m_LineNumber),
    m_Margins(entryData.m_Margins)
{

}


const CViewTracesDisplayCache::CEntryData& CViewTracesDisplayCache::CEntryData::operator = ( const CViewTracesDisplayCache::CEntryData& entryData )
{
    m_ItemArea = entryData.m_ItemArea;
    m_pTraceData = entryData.m_pTraceData;
    m_ColumnWidth = entryData.m_ColumnWidth;
    m_LineNumber = entryData.m_LineNumber;
    m_Margins = entryData.m_Margins;

    return *this;
}

