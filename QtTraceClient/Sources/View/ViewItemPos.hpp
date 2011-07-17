#ifndef __VIEWITEMPOS_HPP__
#define __VIEWITEMPOS_HPP__

#include <Nyx.hpp>
#include <NyxStdAllocators.hpp>
#include "ViewItemsNodeObjectsPool.hpp"



class CViewItem;


/**
 *
 */
typedef     std::list<CViewItem*, Nyx::StdListAllocator<CViewItem*, CViewItemsNodeObjectsPool> >        TViewItemsList;
typedef     TViewItemsList::const_iterator                                                              TViewItemsPos;


/**
 *
 */
class CViewItemPos
{
public: // public methods
    CViewItemPos();
    CViewItemPos( const TViewItemsList& rList, const TViewItemsList::const_iterator& pos);
    CViewItemPos(const CViewItemPos& rPos);
    virtual ~CViewItemPos();

    void operator ++ () { MoveToNext(); }
    void operator -- () { MoveToPrevious(); }

    bool MoveToNext();
    bool MoveToPrevious();

    bool IsFirst() const;
    bool IsLast() const;
    bool IsValid() const;

    bool operator == (const CViewItemPos& pos) const        { return IsEqual(pos); }
    bool operator != (const CViewItemPos& pos) const        { return !IsEqual(pos); }

    const CViewItemPos& operator = (const CViewItemPos& pos);

    CViewItem* Item() const
    {
        if ( IsValid() )
            return *m_Pos;

        return NULL;
    }

protected:

    bool IsEqual(const CViewItemPos& pos) const     { return m_Pos == pos.m_Pos; }

protected:

    TViewItemsList::const_iterator      m_Pos;
    const TViewItemsList*               m_pList;
};


#endif // __VIEWITEMPOS_HPP__
