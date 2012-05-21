#ifndef _SESSIONVIEWITEMS_HPP_
#define _SESSIONVIEWITEMS_HPP_

#include <Nyx.hpp>
#include "ViewItems.hpp"

#include <set>


class CViewItemsModulesMgr;


/**
 *
 */
typedef         Nyx::UInt32                         SessionViewItemsID;


/**
 *
 */
typedef         std::set<SessionViewItemsID>       SessionViewItemsIDSet;


/**
 *
 */
class CSessionViewItems
{
public:
    CSessionViewItems(CViewItemsModulesMgr& rMgr);
    virtual ~CSessionViewItems();

    const CViewItems&           Items() const       { return m_Items; }
    CViewItems&                 Items()             { return m_Items; }

    const SessionViewItemsID&   Id() const          { return m_Id; }
    SessionViewItemsID&         Id()                { return m_Id; }

    const Nyx::CMFString&       Name() const        { return m_Name; }
    Nyx::CMFString&             Name()              { return m_Name; }

    CViewItemsModulesMgr&       Mgr() const         { return m_rMgr; }

protected:

    CViewItems                      m_Items;
    SessionViewItemsID              m_Id;
    Nyx::CMFString                  m_Name;
    CViewItemsModulesMgr&           m_rMgr;
};


#endif // _SESSIONVIEWITEMS_HPP_
