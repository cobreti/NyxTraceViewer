#ifndef _VIEWITEMSMODULESLISTENERS_HPP_
#define _VIEWITEMSMODULESLISTENERS_HPP_


#include "IViewItemsModulesListener.hpp"

#include <set>



/**
 *
 */
class CViewItemsModulesListeners : public IViewItemsModulesListener
{
public:
    CViewItemsModulesListeners();
    CViewItemsModulesListeners(const CViewItemsModulesListeners& listeners);
    ~CViewItemsModulesListeners();

    const CViewItemsModulesListeners& operator = (const CViewItemsModulesListeners& listener);

    void Insert( IViewItemsModulesListener* pListener );
    void Remove( IViewItemsModulesListener* pListener );

public: // IViewItemsModulesListener methods

    virtual void OnNewModuleViewItems( CModuleViewItems* pModule );
    virtual void OnNewSessionViewItems( CModuleViewItems* pModule, CSessionViewItems* pSession );

protected:

    typedef     std::set<IViewItemsModulesListener*>       TListenersSet;

protected:
    TListenersSet           m_Listeners;

};



#endif // _VIEWITEMSMODULESLISTENERS_HPP_
