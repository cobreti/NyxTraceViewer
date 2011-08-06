#ifndef _VIEWITEMSMODULEWALKERNODEPOS_HPP_
#define _VIEWITEMSMODULEWALKERNODEPOS_HPP_

#include <Nyx.hpp>
#include "ViewItemsWalkerNodePos.hpp"
#include "../ViewItem.hpp"



/**
 *
 */
class CViewItemsModuleWalkerNodePos : public CViewItemsWalkerNodePos
{
public:
    CViewItemsModuleWalkerNodePos();
    CViewItemsModuleWalkerNodePos(const CViewItemsModuleWalkerNodePos& pos);
    virtual ~CViewItemsModuleWalkerNodePos();

    ViewItemsNodeId                     SessionNodeId() const           { return m_SessionNodeId; }
    ViewItemsNodeId&                    SessionNodeId()                 { return m_SessionNodeId; }

    const CViewItemsModuleWalkerNodePos& operator = (const CViewItemsModuleWalkerNodePos& pos);

    bool Valid() const;

    ViewItemID                      ItemId() const;

protected:

    ViewItemsNodeId                 m_SessionNodeId;
};

#endif // _VIEWITEMSMODULEWALKERNODEPOS_HPP_
