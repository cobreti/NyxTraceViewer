#ifndef _MODULEVIEWITEMS_HPP_
#define _MODULEVIEWITEMS_HPP_



#include "SessionViewItems.hpp"
#include "ViewItemsModulesListeners.hpp"

#include <map>

class CViewItem;
class IViewItemsModulesListener;

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

    const Nyx::CWString&            Name() const            { return m_Name; }
    Nyx::CWString&                  Name()                  { return m_Name; }

    void InsertItem( CViewItem* pItem );

    const CViewItemsModulesListeners&       Listeners() const           { return m_Listeners; }
    CViewItemsModulesListeners&             Listeners()                 { return m_Listeners; }

protected:

    typedef     std::map<SessionViewItemsID, CSessionViewItems*>        SessionsTable;

protected:

    void ClearSessions();

protected:

    SessionsTable                       m_Sessions;
    SessionViewItemsID                  m_NextAvailId;
    CSessionViewItems*                  m_pActiveSession;
    Nyx::CMemoryPool*                   m_pPool;
    Nyx::CWString                       m_Name;
    CViewItemsModulesListeners          m_Listeners;
};

#endif // _MODULEVIEWITEMS_HPP_
