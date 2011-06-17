#include "ModuleViewItems.hpp"


/**
 *
 */
CModuleViewItems::CModuleViewItems(Nyx::CMemoryPool* pPool) :
m_NextAvailId(1),
m_pActiveSession(NULL),
m_pPool(pPool)
{
}


/**
 *
 */
CModuleViewItems::~CModuleViewItems()
{
    ClearSessions();
}


/**
 *
 */
CSessionViewItems* CModuleViewItems::Session( const SessionViewItemsID& id)
{
    if ( m_Sessions.count(id) > 0 )
        return m_Sessions[id];

    return NULL;
}


/**
 *
 */
SessionViewItemsID CModuleViewItems::CreateNewSession()
{
    CSessionViewItems*      pSession = new CSessionViewItems(m_pPool);

    pSession->Id() = m_NextAvailId++;

    m_Sessions[pSession->Id()] = pSession;
    m_pActiveSession = pSession;

    return pSession->Id();
}


/**
 *
 */
void CModuleViewItems::GetIDs( SessionViewItemsIDSet& IDSet) const
{
    SessionsTable::const_iterator       pos;

    for (pos = m_Sessions.begin(); pos != m_Sessions.end(); ++pos )
        IDSet.insert( pos->first );
}


/**
 *
 */
void CModuleViewItems::ClearSessions()
{
    SessionsTable::iterator     pos;

    for (pos = m_Sessions.begin(); pos != m_Sessions.end(); ++pos)
    {
        delete pos->second;
    }

    m_pActiveSession = NULL;
}


