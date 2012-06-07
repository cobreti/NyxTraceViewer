#include "ModuleViewItems.hpp"
#include "IViewItemsModulesListener.hpp"
#include "ViewItem.hpp"
#include "ViewItem_TraceData.hpp"
#include "ViewItemsModulesMgr.hpp"


/**
 *
 */
CModuleViewItems::CModuleViewItems(CViewItemsModulesMgr& rMgr) :
    m_NextAvailId(1),
    m_pActiveSession(NULL),
    m_rMgr(rMgr)
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
    CSessionViewItems*      pSession = new CSessionViewItems(Mgr());

    pSession->Id() = m_NextAvailId++;

    m_Sessions[pSession->Id()] = pSession;
    m_pActiveSession = pSession;

    Mgr().Listeners().OnNewSessionViewItems(this, pSession);

    return pSession->Id();
}


/**
 *
 */
void CModuleViewItems::ClearSessions()
{
    SessionsTable::iterator     pos;

    for (pos = m_Sessions.begin(); pos != m_Sessions.end(); ++pos)
        delete pos->second;

    m_Sessions.clear();

    m_pActiveSession = NULL;
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
void CModuleViewItems::InsertItem( CViewItem* pItem )
{
    if ( !m_pActiveSession )
        CreateNewSession();
    else if ( pItem->IsOfKind( CViewItem::eViewItem_TraceData))
    {
        CViewItem_TraceData*    pTraceDataItem = static_cast<CViewItem_TraceData*>(pItem);
        if ( pTraceDataItem->TraceData()->Type() == TraceClientCore::CTraceData::eTT_ConnectionStatus_Connection )
            CreateNewSession();
    }

//    Nyx::CTraceStream(0x0)
//            << Nyx::CTF_Text(L"CModuleViewItems::InsertItem - Module : '")
//            << Nyx::CTF_Text(m_Name.c_str())
//            << Nyx::CTF_Text(L"' - Session Id : '")
//            << Nyx::CTF_Hex(ActiveSession()->Id())
//            << Nyx::CTF_Text(L"'");

//    pItem->dbgOutputInfo();

    ActiveSession()->Add(pItem);
}


/**
 *
 */
float CModuleViewItems::CalculateHeight() const
{
    float                               height = 0.0f;
    SessionsTable::const_iterator       pos = m_Sessions.begin();

    while ( pos != m_Sessions.end() )
    {
        height += pos->second->Height();
        ++ pos;
    }

    return height;
}
