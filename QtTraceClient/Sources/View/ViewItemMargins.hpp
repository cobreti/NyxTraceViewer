#ifndef __VIEWITEMMARGINS_HPP__
#define __VIEWITEMMARGINS_HPP__

#include <QtGlobal>


/**
 *
 */
class CViewItemMargins
{
public:
    CViewItemMargins();
    CViewItemMargins(const CViewItemMargins& margins);
    CViewItemMargins(const qreal& left, const qreal& top, const qreal& right, const qreal& bottom);
    ~CViewItemMargins();

    qreal&          top()               { return m_Top; }
    const qreal&    top() const         { return m_Top; }

    qreal&          bottom()            { return m_Bottom; }
    const qreal&    bottom() const      { return m_Bottom; }

    qreal&          left()              { return m_Left; }
    const qreal&    left() const        { return m_Left; }

    qreal&          right()             { return m_Right; }
    const qreal&    right() const       { return m_Right; }

    qreal           width() const       { return m_Left + m_Right; }
    qreal           height() const      { return m_Top + m_Bottom; }

    const CViewItemMargins& operator = (const CViewItemMargins& margins);

protected:

    qreal       m_Top;
    qreal       m_Left;
    qreal       m_Bottom;
    qreal       m_Right;
};

#endif // __VIEWITEMMARGINS_HPP__
