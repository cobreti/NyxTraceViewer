#ifndef VIEWITEMSQUEUE_HPP
#define VIEWITEMSQUEUE_HPP

#include "View/ViewItemInserter.hpp"


class CViewItems;


/**
 *
 */
class CViewItemsQueue : public CViewItemInserter
{
public:
    CViewItemsQueue();

    void SetViewItems( CViewItems* pViewItems );

    CViewItems* Top() const      { return m_pTop; }

    CViewItems* Detach();

    virtual void InsertViewItem( const TraceClientCore::CTraceData* pTraceData );

protected:

    CViewItems*     m_pTop;
};



#endif // VIEWITEMSQUEUE_HPP
