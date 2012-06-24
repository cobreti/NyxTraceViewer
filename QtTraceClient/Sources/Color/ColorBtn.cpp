#include "ColorBtn.h"

#include <QtGui>
#include <QColorDialog>


/**
 *
 */
CColorBtn::CColorBtn() : QToolButton(),
    m_Color( Qt::GlobalColor::yellow )
{
    connect(this, SIGNAL(clicked()), this, SLOT(OnChooseColor()));
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
void CColorBtn::OnChooseColor()
{
    QColorDialog        dlg(Color(), parentWidget());
    int                 customColorsCount = QColorDialog::customCount();

    if ( QDialog::Accepted == dlg.exec() )
    {
        Color() = dlg.selectedColor();
        update();

        emit OnColorChanged(this);
    }
}


/**
 *
 */
void CColorBtn::paintEvent(QPaintEvent* pEvent)
{
    QToolButton::paintEvent(pEvent);

    QPainter        painter(this);
    QBrush          bkgnd( Color() );
    QRect           rcClient = this->rect();

    rcClient.adjust(4, 4, -4, -4);

    painter.fillRect( rcClient, bkgnd );
}

