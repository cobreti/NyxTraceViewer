#ifndef _MODULEVIEWITEMS_HPP_
#define _MODULEVIEWITEMS_HPP_



#include "SessionViewItems.hpp"

#include <map>


/**
 *
 */
class CModuleViewItems
{
public:
    CModuleViewItems(Nyx::CMemoryPool* pPool);
    virtual ~CModuleViewItems();

    CSessionViewItems*      ActiveSession() const          { return m_pActiveSession; }
    CSessionViewItems*      Session( const SessionViewItemsID& id);

    SessionViewItemsID CreateNewSession();

    void GetIDs( SessionViewItemsIDSet& IDSet) const;

    const Nyx::CMFString&           Name() const            { return m_Name; }
    Nyx::CMFString&                 Name()                  { return m_Name; }

protected:

    typedef     std::map<SessionViewItemsID, CSessionViewItems*>        SessionsTable;

protected:

    void ClearSessions();

protected:

    SessionsTable           m_Sessions;
    SessionViewItemsID      m_NextAvailId;
    CSessionViewItems*      m_pActiveSession;
    Nyx::CMemoryPool*       m_pPool;
    Nyx::CMFString          m_Name;
};

#endif // _MODULEVIEWITEMS_HPP_
