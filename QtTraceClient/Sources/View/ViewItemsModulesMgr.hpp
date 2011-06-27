#ifndef __VIEWITEMSMODULESMGR_HPP__
#define __VIEWITEMSMODULESMGR_HPP__

#include <Nyx.hpp>

#include <map>
#include <vector>

class CModuleViewItems;
class CViewItem;
class IViewItemsModulesListener;


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

    CModuleViewItems* operator [] (const Nyx::CWString& ModuleName);

    void GetModules( ModulesViewItemsPtrArray& ModulesArray );

    void Insert( CViewItem* pItem );

    IViewItemsModulesListener*      Listener() const        { return m_pListener; }
    IViewItemsModulesListener*&     Listener()              { return m_pListener; }

protected:

    typedef     std::map<Nyx::CWString, CModuleViewItems*>     ModulesViewItemsTable;

protected:

    ModulesViewItemsTable           m_Modules;
    Nyx::CMemoryPool*               m_pPool;
    IViewItemsModulesListener*      m_pListener;
};


#endif // VIEWITEMSMODULESMGR_HPP
