#ifndef VIEWITEMSWALKERNODEPOS_HPP
#define VIEWITEMSWALKERNODEPOS_HPP

#include <Nyx.hpp>
#include "../ViewItemPos.hpp"


typedef     size_t                          ViewItemsNodeId;

enum
{
    kInvalidNodeId = -1
};


/**
 *
 */
class CViewItemsWalkerNodePos
{
public:
    CViewItemsWalkerNodePos();
    CViewItemsWalkerNodePos(const CViewItemsWalkerNodePos& pos);
    virtual ~CViewItemsWalkerNodePos();

    const CViewItemsWalkerNodePos& operator = (const CViewItemsWalkerNodePos& pos);
    const CViewItemsWalkerNodePos& operator = (const CViewItemPos& pos);

    bool Valid() const;

    bool MoveToNext();
    bool MoveToPrevious();

    bool IsBefore( const CViewItemsWalkerNodePos& pos ) const;
    bool IsAfter( const CViewItemsWalkerNodePos& pos ) const;
    bool IsConcurrent( const CViewItemsWalkerNodePos& pos) const;

    CViewItem* Item() const         { return m_ItemPos.Item(); }

protected:

    CViewItemPos                m_ItemPos;
};


#endif // VIEWITEMSWALKERNODEPOS_HPP
