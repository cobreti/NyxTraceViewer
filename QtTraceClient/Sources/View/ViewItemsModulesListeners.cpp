#include "ViewItemsModulesListeners.hpp"



/**
 *
 */
CViewItemsModulesListeners::CViewItemsModulesListeners()
{
}


/**
 *
 */
CViewItemsModulesListeners::CViewItemsModulesListeners(const CViewItemsModulesListeners& listeners) :
    m_Listeners(listeners.m_Listeners)
{
}


/**
 *
 */
CViewItemsModulesListeners::~CViewItemsModulesListeners()
{
}


/**
 *
 */
const CViewItemsModulesListeners& CViewItemsModulesListeners::operator = (const CViewItemsModulesListeners& listeners)
{
    m_Listeners = listeners.m_Listeners;

    return *this;
}


/**
 *
 */
void CViewItemsModulesListeners::Insert(IViewItemsModulesListener *pListener)
{
    m_Listeners.insert(pListener);
}


/**
 *
 */
void CViewItemsModulesListeners::Remove(IViewItemsModulesListener *pListener)
{
    m_Listeners.erase(pListener);
}


/**
 *
 */
void CViewItemsModulesListeners::OnNewModuleViewItems(CModuleViewItems *pModule)
{
    TListenersSet::const_iterator       iter = m_Listeners.begin();

    while ( iter != m_Listeners.end() )
    {
        (*iter)->OnNewModuleViewItems(pModule);
        ++ iter;
    }
}


/**
 *
 */
void CViewItemsModulesListeners::OnNewSessionViewItems(CModuleViewItems *pModule, CSessionViewItems *pSession)
{
    TListenersSet::const_iterator       iter = m_Listeners.begin();

    while ( iter != m_Listeners.end() )
    {
        (*iter)->OnNewSessionViewItems(pModule, pSession);
        ++ iter;
    }
}
