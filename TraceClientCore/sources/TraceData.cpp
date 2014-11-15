#include "TraceData.hpp"

namespace TraceClientCore
{

    /**
     *
     */
    CTraceData::CTraceData() :
    m_eType(eTT_User),
    m_Flags(),
    m_RepositoryId(0),
    m_TraceId(0),
    m_Level(0),
    m_pOwnerTraceChannel(NULL)
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

    CTraceData::CIdentifier::CIdentifier(quint32 repositoryId, quint32 traceId, quint32 level) :
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
        else if ( m_RepositoryId == identifier.m_RepositoryId )
        {
            if ( m_TraceId < identifier.m_TraceId )
                return true;
            else if ( m_TraceId == identifier.m_TraceId )
            {
                if ( m_Level < identifier.m_Level )
                    return true;
            }
        }

        return false;
    }


    bool CTraceData::CIdentifier::operator <= (const CTraceData::CIdentifier& identifier) const
    {
        if ( m_RepositoryId < identifier.m_RepositoryId )
            return true;
        else if ( m_RepositoryId == identifier.m_RepositoryId )
        {
            if ( m_TraceId < identifier.m_TraceId )
                return true;
            else if ( m_TraceId == identifier.m_TraceId )
            {
                if ( m_Level <= identifier.m_Level )
                    return true;
            }
        }

        return false;
    }


    bool CTraceData::CIdentifier::operator > (const CTraceData::CIdentifier& identifier) const
    {
        if ( m_RepositoryId > identifier.m_RepositoryId )
            return true;
        else if ( m_RepositoryId == identifier.m_RepositoryId )
        {
            if ( m_TraceId > identifier.m_TraceId )
                return true;
            else if ( m_TraceId == identifier.m_TraceId )
            {
                if ( m_Level > identifier.m_Level )
                    return true;
            }
        }

        return false;
    }

    bool CTraceData::CIdentifier::operator >= (const CTraceData::CIdentifier& identifier) const
    {
        if ( m_RepositoryId > identifier.m_RepositoryId )
            return true;
        else if ( m_RepositoryId == identifier.m_RepositoryId )
        {
            if ( m_TraceId > identifier.m_TraceId )
                return true;
            else if ( m_TraceId == identifier.m_TraceId )
            {
                if ( m_Level >= identifier.m_Level )
                    return true;
            }
        }

        return false;
    }
}
