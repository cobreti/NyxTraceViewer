#include "TraceData.hpp"


namespace TraceClientCore
{

    /**
     *
     */
    CTraceData::CTraceData(Nyx::CMemoryPool* pMemPool) :
    CTraceData::BaseType(pMemPool),
    m_TimeReference(pMemPool),
    m_TickCountReference(pMemPool),
    m_ThreadId(pMemPool),
    m_TickCount(pMemPool),
    m_Data(pMemPool),
    m_pOwnerPool(NULL),
    m_eType(eTT_User),
    m_Flags(),
    m_RepositoryId(0),
    m_TraceId(0),
    m_Level(0)
    {
    }


    /**
     *
     */
    CTraceData::~CTraceData()
    {
    }



    CTraceData::CIdentifier::CIdentifier() :
        m_RepositoryId(0),
        m_TraceId(0),
        m_Level(0)
    {

    }

    CTraceData::CIdentifier::CIdentifier(const int& repositoryId, const int& traceId, const int& level) :
        m_RepositoryId(repositoryId),
        m_TraceId(traceId),
        m_Level(level)
    {

    }


    CTraceData::CIdentifier::CIdentifier(const CIdentifier &identifier) :
        m_RepositoryId(identifier.m_RepositoryId),
        m_TraceId(identifier.m_TraceId),
        m_Level(identifier.m_Level)
    {

    }


    CTraceData::CIdentifier::~CIdentifier()
    {

    }


    const CTraceData::CIdentifier& CTraceData::CIdentifier::operator = (const CTraceData::CIdentifier& identifier)
    {
        m_RepositoryId = identifier.m_RepositoryId;
        m_TraceId = identifier.m_TraceId;
        m_Level = identifier.m_Level;

        return *this;
    }


    bool CTraceData::CIdentifier::operator == (const CTraceData::CIdentifier& identifier) const
    {
        return (    m_RepositoryId == identifier.m_RepositoryId &&
                    m_TraceId == identifier.m_TraceId &&
                    m_Level == identifier.m_Level );
    }


    bool CTraceData::CIdentifier::operator != (const CTraceData::CIdentifier& identifier) const
    {
        return !(   m_RepositoryId == identifier.m_RepositoryId &&
                    m_TraceId == identifier.m_TraceId &&
                    m_Level == identifier.m_Level );
    }


    bool CTraceData::CIdentifier::operator < (const CTraceData::CIdentifier& identifier) const
    {
        if ( m_RepositoryId < identifier.m_RepositoryId )
            return true;

        if ( m_TraceId < identifier.m_TraceId )
            return true;

        if ( m_Level < identifier.m_Level )
            return true;

        return false;
    }

    bool CTraceData::CIdentifier::operator > (const CTraceData::CIdentifier& identifier) const
    {
        if ( m_RepositoryId > identifier.m_RepositoryId )
            return true;

        if ( m_TraceId > identifier.m_TraceId )
            return true;

        if ( m_Level > identifier.m_Level )
            return true;

        return false;
    }
}
