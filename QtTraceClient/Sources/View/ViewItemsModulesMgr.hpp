#ifndef __VIEWITEMSMODULESMGR_HPP__
#define __VIEWITEMSMODULESMGR_HPP__

#include <Nyx.hpp>
#include "ViewItemsModulesListeners.hpp"

#include <map>
#include <vector>

class CModuleViewItems;
class CViewItem;
class IViewItemsModulesListener;
class CViewItemsWalkerCore;


typedef     std::vector<CModuleViewItems*>          ModulesViewItemsPtrArray;


/**
 *
 */
class CViewItemsModulesMgr
{
public:
    CViewItemsModulesMgr(Nyx::CMemoryPool* pPool);
    ~CViewItemsModulesMgr();

    CModuleViewItems* CreateNewModule( const Nyx::CWString& ModuleName );
    void ClearModule( const Nyx::CWString& ModuleName );

    CModuleViewItems* operator [] (const Nyx::CWString& ModuleName);

    void GetModules( ModulesViewItemsPtrArray& ModulesArray );

    void Insert( CViewItem* pItem );
    void OnItemWidthChanged( CViewItem* pItem );

    const CViewItemsModulesListeners&   Listeners() const   { return m_Listeners; }
    CViewItemsModulesListeners&         Listeners()         { return m_Listeners; }

    void AttachWalker( CViewItemsWalkerCore* pWalker );
    void DetachWalker( CViewItemsWalkerCore* pWalker );

    Nyx::CMemoryPool*                   MemoryPool() const  { return m_pPool; }

    float CalculateHeight() const;
    size_t LinesCount() const;

protected:

    typedef     std::vector<CViewItemsWalkerCore*>              ViewItemsWalkerArray;
    typedef     std::map<Nyx::CWString, CModuleViewItems*>      ModulesViewItemsTable;

protected:

    ModulesViewItemsTable           m_Modules;
    Nyx::CMemoryPool*               m_pPool;
    CViewItemsModulesListeners      m_Listeners;
    ViewItemsWalkerArray            m_AttachedWalkers;
};


#endif // VIEWITEMSMODULESMGR_HPP
