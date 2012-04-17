#ifndef _IVIEWITEMSWALKERMETHODS_HPP_
#define _IVIEWITEMSWALKERMETHODS_HPP_

#include <Nyx.hpp>

class CModuleViewItems;
class CViewItem;
class CSessionViewItems;


/**
 *
 */
class IViewItemsWalkerMethods
{
public:
    virtual void OnNewModuleViewItem( CModuleViewItems* pModule ) = 0;
    virtual void OnNewSessionViewItem( CModuleViewItems* pModule, CSessionViewItems* pSession ) = 0;
    virtual void OnNewViewItem( CViewItem* pViewItem ) = 0;
    virtual void OnItemWidthChanged( CViewItem* pViewItem ) = 0;

    virtual bool InitNewModulesPosition() = 0;

    virtual bool MoveToBegin() = 0;
    virtual bool MoveToNext() = 0;
    virtual bool MoveToPrevious() = 0;
    virtual bool MoveTo(const float& y) = 0;

    virtual bool ValidPos() const = 0;
    virtual CViewItem* Item() const = 0;
    virtual const float& ItemYPos() const = 0;
    virtual const size_t LineNumber() const = 0;

    virtual void PushState() = 0;
    virtual void PopState() = 0;

    virtual const float& Height() const = 0;
    virtual const float& Width() const = 0;
};


#endif // _IVIEWITEMSWALKERMETHODS_HPP_
