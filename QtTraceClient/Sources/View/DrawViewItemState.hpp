#ifndef __DRAWVIEWITEMSTATE_HPP__
#define __DRAWVIEWITEMSTATE_HPP__

#include <QPainter>


/**
 *
 */
class CDrawViewItemState
{
public:
    CDrawViewItemState(QPainter& rPainter);
    ~CDrawViewItemState();

    QPainter&       Painter()               { return m_rPainter; }

    const QRectF&   ViewRect() const        { return m_ViewRect; }
    QRectF&         ViewRect()              { return m_ViewRect; }

    const QPointF&  TextPos() const         { return m_TextPos; }
    QPointF&        TextPos()               { return m_TextPos; }

    const QSizeF&   LineSize() const        { return m_LineSize; }
    QSizeF&         LineSize()              { return m_LineSize; }

    bool			Marked() const			{ return m_bMarked; }
    bool&			Marked()				{ return m_bMarked; }

protected:

    QPainter&       m_rPainter;
    QRectF          m_ViewRect;
    QPointF         m_TextPos;
    QSizeF          m_LineSize;
    bool			m_bMarked;
};

#endif // __DRAWVIEWITEMSTATE_HPP__
