#include "ColorBtn.h"

#include <QtGui>

/**
 *
 */
CColorBtn::CColorBtn() : QToolButton(),
    m_Color( Qt::GlobalColor::yellow )
{
}


/**
 *
 */
CColorBtn::~CColorBtn()
{
}


/**
 *
 */
void CColorBtn::paintEvent(QPaintEvent* pEvent)
{
    QToolButton::paintEvent(pEvent);

    QPainter        painter(this);
    QBrush          bkgnd( Color() );

    painter.fillRect( QRect(2, 2, width()-4, height()-4), bkgnd );
}

