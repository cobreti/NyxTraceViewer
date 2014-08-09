#include "TraceSectionId.h"


CTraceSectionId::CTraceSectionId(const TraceClientCore::CTraceData::CIdentifier &traceId, EViewColumnId colId) :
    m_TraceId(traceId),
    m_ColumnId(colId)
{

}


CTraceSectionId::CTraceSectionId(const CTraceSectionId &sectionId) :
    m_TraceId(sectionId.m_TraceId),
    m_ColumnId(sectionId.m_ColumnId)
{

}


CTraceSectionId::~CTraceSectionId()
{

}


const CTraceSectionId& CTraceSectionId::operator = (const CTraceSectionId& sectionId)
{
    m_TraceId = sectionId.m_TraceId;
    m_ColumnId = sectionId.m_ColumnId;

    return *this;
}


bool CTraceSectionId::operator == (const CTraceSectionId& sectionId) const
{
    return  ( m_TraceId == sectionId.m_TraceId && m_ColumnId == sectionId.m_ColumnId );
}


bool CTraceSectionId::operator != (const CTraceSectionId& sectionId) const
{
    return ( m_TraceId != sectionId.m_TraceId || m_ColumnId != sectionId.m_ColumnId );
}


bool CTraceSectionId::operator < (const CTraceSectionId& sectionId) const
{
    if ( m_TraceId < sectionId.m_TraceId )
        return true;
    else if ( m_TraceId == sectionId.m_TraceId )
    {
        return m_ColumnId < sectionId.m_ColumnId;
    }

    return false;
}


bool CTraceSectionId::operator <= (const CTraceSectionId& sectionId) const
{
    if ( m_TraceId < sectionId.m_TraceId )
        return true;
    else if ( m_TraceId == sectionId.m_TraceId )
    {
        return m_ColumnId <= sectionId.m_ColumnId;
    }

    return false;
}


bool CTraceSectionId::operator > (const CTraceSectionId& sectionId) const
{
    if ( m_TraceId > sectionId.m_TraceId )
        return true;
    else if ( m_TraceId == sectionId.m_TraceId )
    {
        return m_ColumnId > sectionId.m_ColumnId;
    }


    return false;
}


bool CTraceSectionId::operator >= (const CTraceSectionId& sectionId) const
{
    if ( m_TraceId > sectionId.m_TraceId )
        return true;
    else if ( m_TraceId == sectionId.m_TraceId )
    {
        return m_ColumnId >= sectionId.m_ColumnId;
    }

    return false;
}
