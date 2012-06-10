#ifndef __DRAWVIEWITEMSTATE_HPP__
#define __DRAWVIEWITEMSTATE_HPP__

#include <QPainter>
#include "View/highlight/ViewItemHighlighter.hpp"

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

    const size_t&   LineNumber() const      { return m_LineNumber; }
    size_t&         LineNumber()            { return m_LineNumber; }

    CViewItemHighlighterRef     Highlighter() const     { return m_refHighlighter; }
    CViewItemHighlighterRef&    Highlighter()           { return m_refHighlighter; }

protected:

    QPainter*                   m_pPainter;
    QRectF                      m_ViewRect;
    QPointF                     m_TextPos;
    QSizeF                      m_LineSize;
    bool			            m_bMarked;
    size_t                      m_LineNumber;
    CViewItemHighlighterRef     m_refHighlighter;
};

#endif // __DRAWVIEWITEMSTATE_HPP__
