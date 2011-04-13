#ifndef __VIEWITEMTICKCOUNTPAINTER_HPP__
#define __VIEWITEMTICKCOUNTPAINTER_HPP__

#include "ViewItemTextPainter.hpp"


/**
 *
 */
class CViewItemTickCountPainter : public CViewItemTextPainter
{
public:

    static CViewItemPainter* Instance();

public:
    CViewItemTickCountPainter();
    virtual ~CViewItemTickCountPainter();

    virtual EPainterId Id() const { return ePId_TickCount; }

    virtual void EvaluateSize(CViewSettings& settings, CViewItem& item );
    virtual void Display( const CViewSettings& settings, CDrawViewItemState& drawstate, CViewItem& item );

private:

    static CViewItemPainterRef      s_refPainter;
};


#endif // __VIEWITEMTICKCOUNTPAINTER_HPP__
