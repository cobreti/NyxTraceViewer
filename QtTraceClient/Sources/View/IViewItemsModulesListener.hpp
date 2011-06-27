#ifndef __IVIEWITEMSMODULESLISTENER_HPP__
#define __IVIEWITEMSMODULESLISTENER_HPP__


class CModuleViewItems;
class CSessionViewItems;


/**
 *
 */
class IViewItemsModulesListener
{
public:
    virtual void OnNewModuleViewItems( CModuleViewItems* pModule ) = 0;
    virtual void OnNewSessionViewItems( CModuleViewItems* pModule, CSessionViewItems* pSession ) = 0;

};


#endif // IVIEWITEMSMODULESLISTENER_HPP
