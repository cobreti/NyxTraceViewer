#ifndef __VIEWITEMS_HPP__
#define __VIEWITEMS_HPP__

#include <QSizeF>
#include <list>
#include <Nyx.hpp>
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
    virtual void RemoveFromClientSize( CViewItem* pItem );
    virtual void AddToClientSize( CViewItem* pItem );
    virtual CViewItemPos begin() const;
    virtual CViewItemPos end() const;
    virtual size_t ItemsCount() const;
    virtual const QSizeF& GetSize() const;
    virtual const QSizeF& GetLastLineSize() const;
    virtual const QSizeF& GetMaxLineSize() const;
    virtual void Clear(bool bDeleteItems = true);

    const CViewItems& operator += (CViewItems& items);

protected:

    TViewItemsList          m_Items;
    QSizeF                  m_Size;
    QSizeF                  m_LastLineSize;
    QSizeF                  m_MaxLineSize;
    bool                    m_bOwnItems;
};


#endif // __VIEWITEMS_HPP__
