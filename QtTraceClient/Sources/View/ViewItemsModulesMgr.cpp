#include "ViewItemsModulesMgr.hpp"
#include "ModuleViewItems.hpp"
#include "ViewItem.hpp"
#include "IViewItemsModulesListener.hpp"
#include "Walkers/ViewItemsWalker.hpp"


/**
 *
 */
CViewItemsModulesMgr::CViewItemsModulesMgr(Nyx::CMemoryPool* pPool) :
m_pPool(pPool)
{
}


/**
 *
 */
CViewItemsModulesMgr::~CViewItemsModulesMgr()
{
}


/**
 *
 */
CModuleViewItems* CViewItemsModulesMgr::CreateNewModule(const Nyx::CWString& ModuleName)
{
    if ( m_Modules.count(ModuleName) > 0 )
        return m_Modules[ModuleName];

    CModuleViewItems*       pModule = new CModuleViewItems(*this);
    pModule->Name() = ModuleName;
    m_Modules[ModuleName] = pModule;

    m_Listeners.OnNewModuleViewItems(pModule);

    return pModule;
}


/**
 *
 */
CModuleViewItems* CViewItemsModulesMgr::operator [] (const Nyx::CWString& ModuleName)
{
    if ( m_Modules.count(ModuleName) > 0 )
        return m_Modules[ModuleName];

    return NULL;
}


/**
 *
 */
void CViewItemsModulesMgr::GetModules( ModulesViewItemsPtrArray& ModulesArray )
{
    ModulesArray.resize( m_Modules.size());

    size_t                                      index = 0;
    ModulesViewItemsTable::const_iterator       pos = m_Modules.begin();

    while ( pos != m_Modules.end() )
    {
        ModulesArray[index] = pos->second;
        ++index;
    }
}


/**
 *
 */
void CViewItemsModulesMgr::Insert( CViewItem* pItem )
{
    CModuleViewItems*           pModule = NULL;

    if ( m_Modules.count(pItem->ModuleName()) == 0 )
        pModule = CreateNewModule(pItem->ModuleName());
    else
        pModule = m_Modules[pItem->ModuleName()];

    pModule->InsertItem(pItem);

    for (size_t index = 0; index < m_AttachedWalkers.size(); ++index)
        if ( m_AttachedWalkers[index] )
             m_AttachedWalkers[index]->OnNewViewItem(pItem);
}



/**
 *
 */
void CViewItemsModulesMgr::OnItemWidthChanged(CViewItem *pItem)
{
    for (size_t index = 0; index < m_AttachedWalkers.size(); ++index)
        if ( m_AttachedWalkers[index] )
             m_AttachedWalkers[index]->OnItemWidthChanged(pItem);
}


/**
 *
 */
void CViewItemsModulesMgr::AttachWalker( CViewItemsWalkerCore* pWalker )
{
    if ( pWalker == NULL )
        return;

    // first look if already there
    for (size_t index = 0; index < m_AttachedWalkers.size(); ++index)
        if ( m_AttachedWalkers[index] == pWalker )
            return;

    // find an empty spot to add it
    for (size_t index = 0; index < m_AttachedWalkers.size(); ++index)
        if ( m_AttachedWalkers[index] == NULL )
        {
            m_AttachedWalkers[index] = pWalker;
            return;
        }

    // couldn't find a spot, push at the back
    m_AttachedWalkers.push_back(pWalker);
}


/**
 *
 */
void CViewItemsModulesMgr::DetachWalker( CViewItemsWalkerCore* pWalker )
{
    if ( pWalker == NULL )
        return;

    for (size_t index = 0; index < m_AttachedWalkers.size(); ++index)
        if ( m_AttachedWalkers[index] == pWalker )
        {
            m_AttachedWalkers[index] = NULL;
            return;
        }
}


