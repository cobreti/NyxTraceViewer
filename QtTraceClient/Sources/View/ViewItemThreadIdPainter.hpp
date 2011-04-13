#ifndef __VIEWITEMTHREADIDPAINTER_HPP__
#define __VIEWITEMTHREADIDPAINTER_HPP__

#include "ViewItemTextPainter.hpp"

class CViewItemThreadIdPainter : public CViewItemTextPainter
{
public:

    static CViewItemPainter* Instance();

public:
    CViewItemThreadIdPainter();
    virtual ~CViewItemThreadIdPainter();

    virtual EPainterId Id() const { return ePId_ThreadId; }

    virtual void EvaluateSize(CViewSettings &settings, CViewItem &item);
    virtual void Display(const CViewSettings &settings, CDrawViewItemState &drawstate, CViewItem &item);

private:

    static CViewItemPainterRef      s_refPainter;
};

#endif // __VIEWITEMTHREADIDPAINTER_HPP__
