#ifndef DYNAMICFOCUSEDITEMHIGHLIGHT_HPP
#define DYNAMICFOCUSEDITEMHIGHLIGHT_HPP

#include "DynamicHighlight.h"

class CViewTracesContentIterator;


class CDynamicFocusedItemHighlight : public CDynamicHighlight
{
public:
    CDynamicFocusedItemHighlight(CViewTracesContentIterator& rFocusedItem);
    virtual ~CDynamicFocusedItemHighlight();

    virtual void Draw( CViewTracePainter::CPaintContext& context );

protected:
    CViewTracesContentIterator&     m_rFocusedItem;
};

#endif // DYNAMICFOCUSEDITEMHIGHLIGHT_HPP
