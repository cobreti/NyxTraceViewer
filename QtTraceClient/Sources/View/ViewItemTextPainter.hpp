#ifndef __VIEWITEMTEXTPAINTER_HPP__
#define __VIEWITEMTEXTPAINTER_HPP__

#include "ViewItemPainter.hpp"

/**
 *
 */
class CViewItemTextPainter : public CViewItemPainter
{
public:
    CViewItemTextPainter();
    virtual ~CViewItemTextPainter();

protected:
    virtual void EvaluateSize(CViewSettings& settings, CViewItem& item, const QString& text );
    virtual void Display( const CViewSettings& settings, CDrawViewItemState& drawstate, CViewItem& item, const QString& text );
};

#endif // __VIEWITEMTEXTPAINTER_HPP__
