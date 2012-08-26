#ifndef __DRAWVIEWITEMSTATE_HPP__
#define __DRAWVIEWITEMSTATE_HPP__

#include <QPainter>
#include "View/Highlight/ViewItemHighlighter.hpp"

/**
 *
 */
class CDrawViewItemState
{
public:
    CDrawViewItemState(QPainter* pPainter);
    ~CDrawViewItemState();

    QPainter&       Painter()               { return *m_pPainter; }

    const QRectF&   ViewRect() const        { return m_ViewRect; }
    QRectF&         ViewRect()              { return m_ViewRect; }

    const QPointF&  TextPos() const         { return m_TextPos; }
    QPointF&        TextPos()               { return m_TextPos; }

    const QSizeF&   LineSize() const        { return m_LineSize; }
    QSizeF&         LineSize()              { return m_LineSize; }

    bool			Marked() const			{ return m_bMarked; }
    bool&			Marked()				{ return m_bMarked; }

    const size_t&   ItemNumber() const      { return m_ItemNumber; }
    size_t&         ItemNumber()            { return m_ItemNumber; }

    CViewItemHighlighterRef     Highlighter() const     { return m_refHighlighter; }
    CViewItemHighlighterRef&    Highlighter()           { return m_refHighlighter; }

protected:

    QPainter*                   m_pPainter;
    QRectF                      m_ViewRect;
    QPointF                     m_TextPos;
    QSizeF                      m_LineSize;
    bool			            m_bMarked;
    size_t                      m_ItemNumber;
    CViewItemHighlighterRef     m_refHighlighter;
};

#endif // __DRAWVIEWITEMSTATE_HPP__
