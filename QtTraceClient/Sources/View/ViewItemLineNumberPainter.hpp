#ifndef _VIEWITEMLINENUMBERPAINTER_HPP_
#define _VIEWITEMLINENUMBERPAINTER_HPP_

#include "ViewItemTextPainter.hpp"

/**
 *
 */
class CViewItemLineNumberPainter : public CViewItemTextPainter
{
public:

    static  CViewItemPainter*   Instance();

public:
    CViewItemLineNumberPainter();
    virtual ~CViewItemLineNumberPainter();

    virtual EPainterId Id() const { return ePId_LineNumber; }

    virtual void EvaluateSize( CViewSettings& settings, CViewItem& item );
    virtual void Display( const CViewSettings& settings, CDrawViewItemState& drawstate, CViewItem& item );

private:

    static CViewItemPainterRef          s_refPainter;
};



#endif // _VIEWITEMLINENUMBERPAINTER_HPP_
