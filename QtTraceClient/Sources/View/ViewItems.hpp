#ifndef __VIEWITEMS_HPP__
#define __VIEWITEMS_HPP__

#include <QSizeF>
#include <list>
#include <Nyx.hpp>
#include <NyxAssert.hpp>
#include <NyxStdAllocators.hpp>
#include "ViewItemPos.hpp"
#include "ViewItemsNodeObjectsPool.hpp"

class CViewItem;


/**
 *
 */
class CViewItems : public Nyx::CMemPoolObj<>
{
public:
    CViewItems( Nyx::CMemoryPool* pPool );
    virtual ~CViewItems();

    virtual void Add( CViewItem* pItem );
    virtual void RemoveFromClientSize( CViewItem* pItem );
    virtual void AddToClientSize( CViewItem* pItem );
    virtual CViewItemPos begin() const;
    virtual size_t ItemsCount() const;
    virtual const QSizeF& GetSize() const;
    virtual const QSizeF& GetLastLineSize() const;
    virtual const QSizeF& GetMaxLineSize() const;
    virtual void Clear(bool bDeleteItems = true);

    const CViewItems& operator += (CViewItems& items);

protected:

    typedef     std::list<CViewItem*, Nyx::StdListAllocator<CViewItem*, CViewItemsNodeObjectsPool> >       TViewItemsList;

    /**
     *
     */
    class XPosData : public CViewItemPos::XData
    {
    public:
        XPosData(const XPosData& data);
        XPosData(const TViewItemsList& rList, const TViewItemsList::const_iterator& pos, double y );

        virtual bool IsValid() const;
        virtual CViewItemPos::XData* Clone() const;

        virtual void MoveToNext();
        virtual void MoveToPrevious();
        virtual bool IsFirst() const;
        virtual bool IsLast() const;

        virtual bool IsOfType( CViewItemPos::EViewItemPosIdentifier id ) const;

        virtual bool IsEqual(const CViewItemPos::XData &data) const;

        virtual CViewItem* Item() const;
        virtual double Y() const;

    protected:

        TViewItemsList::const_iterator      m_Pos;
        const TViewItemsList*               m_pList;
        double                              m_Y;
    };

    /**
     *
     */
    class XPos : public CViewItemPos
    {
    public:
        XPos( const TViewItemsList& rList, const TViewItemsList::const_iterator& pos, double y );
    };

protected:

    TViewItemsList          m_Items;
    QSizeF                  m_Size;
    QSizeF                  m_LastLineSize;
    QSizeF                  m_MaxLineSize;
};


#endif // __VIEWITEMS_HPP__
