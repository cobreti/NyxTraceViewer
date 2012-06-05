#ifndef __VIEWITEMS_HPP__
#define __VIEWITEMS_HPP__

#include <QSizeF>
#include <list>
#include <Nyx.hpp>
#include <NyxMsg.hpp>
#include <NyxAssert.hpp>
#include "ViewItemPos.hpp"


/**
 *
 */
class CViewItems : public Nyx::CMemPoolObj<>
{
public:
    CViewItems( Nyx::CMemoryPool* pPool, bool bOwnItems );
    virtual ~CViewItems();

    virtual void Add( CViewItem* pItem );
    virtual CViewItemPos begin() const;
    virtual CViewItemPos end() const;
    virtual size_t ItemsCount() const;
    virtual void Clear(bool bDeleteItems = true);

    const CViewItems& operator += (CViewItems& items);

protected:

    TViewItemsList          m_Items;
    bool                    m_bOwnItems;
};


/**
 *
 */
class CViewItemsMsg : public Nyx::CMsg
{
public:
    CViewItemsMsg() {}
    virtual ~CViewItemsMsg() {}

    virtual const Nyx::MsgIdentifier Id() const { return 0; }

    CViewItems*&    ViewItems()         { return m_pViewItems; }
    CViewItems*     ViewItems() const   { return m_pViewItems; }

protected:

    CViewItems*     m_pViewItems;
};


/**
 *
 */
class CClearItemsMsg : public Nyx::CMsg
{
public:
    CClearItemsMsg() {}
    virtual ~CClearItemsMsg() {}

    virtual const Nyx::MsgIdentifier Id() const { return 1; }

    const Nyx::CAString& ModuleName() const { return m_ModuleName; }
    Nyx::CAString& ModuleName()             { return m_ModuleName; }

protected:

    Nyx::CAString       m_ModuleName;
};


#endif // __VIEWITEMS_HPP__
