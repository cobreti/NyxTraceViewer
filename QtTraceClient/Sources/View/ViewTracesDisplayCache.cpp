#include "ViewTracesDisplayCache.h"


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


void CViewTracesDisplayCache::setEntry(const CEntryId &id, const CEntryData &data)
{
    m_Entries[id] = data;
}


CViewTracesDisplayCache::CEntryData::CEntryData() :
    m_pTraceData(NULL)
{

}


CViewTracesDisplayCache::CEntryData::~CEntryData()
{

}


CViewTracesDisplayCache::CEntryData::CEntryData(const CEntryData &entryData) :
    m_ItemArea(entryData.m_ItemArea)
{

}


const CViewTracesDisplayCache::CEntryData& CViewTracesDisplayCache::CEntryData::operator = ( const CViewTracesDisplayCache::CEntryData& entryData )
{
    m_ItemArea = entryData.m_ItemArea;

    return *this;
}



CViewTracesDisplayCache::CEntryId::CEntryId(const TraceClientCore::CTraceData::CIdentifier &traceId, EViewColumnId colId) :
    m_TraceId(traceId),
    m_ColumnId(colId)
{

}


CViewTracesDisplayCache::CEntryId::CEntryId(const CEntryId &entryId) :
    m_TraceId(entryId.m_TraceId),
    m_ColumnId(entryId.m_ColumnId)
{

}


CViewTracesDisplayCache::CEntryId::~CEntryId()
{

}


const CViewTracesDisplayCache::CEntryId& CViewTracesDisplayCache::CEntryId::operator = (const CViewTracesDisplayCache::CEntryId& entryId)
{
    m_TraceId = entryId.m_TraceId;
    m_ColumnId = entryId.m_ColumnId;

    return *this;
}


bool CViewTracesDisplayCache::CEntryId::operator == (const CViewTracesDisplayCache::CEntryId& entryId) const
{
    return  ( m_TraceId == entryId.m_TraceId && m_ColumnId == entryId.m_ColumnId );
}


bool CViewTracesDisplayCache::CEntryId::operator != (const CViewTracesDisplayCache::CEntryId& entryId) const
{
    return ( m_TraceId != entryId.m_TraceId || m_ColumnId != entryId.m_ColumnId );
}


bool CViewTracesDisplayCache::CEntryId::operator < (const CViewTracesDisplayCache::CEntryId& entryId) const
{
    if ( m_TraceId < entryId.m_TraceId )
        return true;

    if ( m_ColumnId < entryId.m_ColumnId )
        return true;

    return false;
}


bool CViewTracesDisplayCache::CEntryId::operator > (const CViewTracesDisplayCache::CEntryId& entryId) const
{
    if ( m_TraceId > entryId.m_TraceId )
        return true;

    if ( m_ColumnId > entryId.m_ColumnId )
        return true;

    return false;
}
