#ifndef __VIEWITEMDATAPAINTER_HPP__
#define __VIEWITEMDATAPAINTER_HPP__

#include "ViewItemTextPainter.hpp"


/**
 *
 */
class CViewItemDataPainter : public CViewItemTextPainter
{
public:

    static  CViewItemPainter*   Instance();

public:
    CViewItemDataPainter();
    ~CViewItemDataPainter();

    virtual EPainterId Id() const { return ePId_Data; }

    virtual void EvaluateSize( CViewSettings& settings, CViewItem& item );
    virtual void Display( const CViewSettings& settings, CDrawViewItemState& drawstate, CViewItem& item );

private:

    static CViewItemPainterRef          s_refPainter;
};

#endif // __VIEWITEMDATAPAINTER_HPP__
