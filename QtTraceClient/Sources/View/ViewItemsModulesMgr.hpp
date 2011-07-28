#ifndef __VIEWITEMSMODULESMGR_HPP__
#define __VIEWITEMSMODULESMGR_HPP__

#include <Nyx.hpp>

#include <map>
#include <vector>

class CModuleViewItems;
class CViewItem;
class IViewItemsModulesListener;
class CViewItemsWalker;


typedef     std::vector<CModuleViewItems*>          ModulesViewItemsPtrArray;
typedef     std::vector<CViewItemsWalker*>          ViewItemsWalkerArray;


/**
 *
 */
class CViewItemsModulesMgr
{
public:
    CViewItemsModulesMgr(Nyx::CMemoryPool* pPool);
    ~CViewItemsModulesMgr();

    CModuleViewItems* CreateNewModule( const Nyx::CWString& ModuleName );

    CModuleViewItems* operator [] (const Nyx::CWString& ModuleName);

    void GetModules( ModulesViewItemsPtrArray& ModulesArray );

    void Insert( CViewItem* pItem );
    void OnItemWidthChanged( CViewItem* pItem );

    IViewItemsModulesListener*      Listener() const        { return m_pListener; }
    IViewItemsModulesListener*&     Listener()              { return m_pListener; }

    void AttachWalker( CViewItemsWalker* pWalker );
    void DetachWalker( CViewItemsWalker* pWalker );

protected:

    typedef     std::map<Nyx::CWString, CModuleViewItems*>     ModulesViewItemsTable;

protected:

    ModulesViewItemsTable           m_Modules;
    Nyx::CMemoryPool*               m_pPool;
    IViewItemsModulesListener*      m_pListener;
    ViewItemsWalkerArray            m_AttachedWalkers;
};


#endif // VIEWITEMSMODULESMGR_HPP
