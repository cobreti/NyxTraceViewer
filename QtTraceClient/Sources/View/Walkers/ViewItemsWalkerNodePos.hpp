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

    virtual bool MoveToNext();
    virtual bool MoveToPrevious();

protected:

    CViewItemPos                m_ItemPos;
};


#endif // VIEWITEMSWALKERNODEPOS_HPP
