#ifndef _MODULEVIEWITEMS_HPP_
#define _MODULEVIEWITEMS_HPP_



#include "SessionViewItems.hpp"
#include "ViewItemsModulesListeners.hpp"

#include <map>

class CViewItem;
class IViewItemsModulesListener;
class CViewItemsModulesMgr;

/**
 *
 */
class CModuleViewItems
{
public:
    CModuleViewItems(CViewItemsModulesMgr& rMgr);
    virtual ~CModuleViewItems();

    CSessionViewItems*      ActiveSession() const          { return m_pActiveSession; }
    CSessionViewItems*      Session( const SessionViewItemsID& id);

    SessionViewItemsID CreateNewSession();

    void GetIDs( SessionViewItemsIDSet& IDSet) const;

    const Nyx::CWString&            Name() const            { return m_Name; }
    Nyx::CWString&                  Name()                  { return m_Name; }

    void InsertItem( CViewItem* pItem );

    const CViewItemsModulesMgr&             Mgr() const                 { return m_rMgr; }
    CViewItemsModulesMgr&                   Mgr()                       { return m_rMgr; }

protected:

    typedef     std::map<SessionViewItemsID, CSessionViewItems*>        SessionsTable;

protected:

    void ClearSessions();

protected:

    SessionsTable                       m_Sessions;
    SessionViewItemsID                  m_NextAvailId;
    CSessionViewItems*                  m_pActiveSession;
    Nyx::CWString                       m_Name;
    CViewItemsModulesMgr&               m_rMgr;
};

#endif // _MODULEVIEWITEMS_HPP_
