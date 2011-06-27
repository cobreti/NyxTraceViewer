#include "ViewItemsModulesMgr.hpp"
#include "ModuleViewItems.hpp"
#include "ViewItem.hpp"
#include "IViewItemsModulesListener.hpp"


/**
 *
 */
CViewItemsModulesMgr::CViewItemsModulesMgr(Nyx::CMemoryPool* pPool) :
m_pPool(pPool),
m_pListener(NULL)
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

    CModuleViewItems*       pModule = new CModuleViewItems(m_pPool);
    pModule->Name() = ModuleName;
    pModule->Listener() = m_pListener;
    m_Modules[ModuleName] = pModule;

    if ( m_pListener )
        m_pListener->OnNewModuleViewItems(pModule);

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
}

