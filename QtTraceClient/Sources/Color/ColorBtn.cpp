#include "ColorBtn.h"
#include "View/Highlight/HighlightColorsPopup.h"
#include "TraceClientApp.h"

#include <QtGui>
#include <QColorDialog>


/**
 *
 */
CColorBtn::CColorBtn() : QToolButton(),
    m_Color( Qt::GlobalColor::yellow )
{
    connect(this, SIGNAL(clicked()), this, SLOT(OnClicked()));
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
void CColorBtn::OnClicked()
{
    emit OnColorSelected(this);
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



//=====================================================================


/**
 *
 */
CChooseColorBtn::CChooseColorBtn() : CColorBtn()
{
    //connect(this, SIGNAL(clicked()), this, SLOT(OnClicked()));
}


/**
 *
 */
CChooseColorBtn::~CChooseColorBtn()
{
}


/**
 *
 */
void CChooseColorBtn::OnClicked()
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


//=====================================================================


/**
 *
 */
CWordHighlightColorBtn::CWordHighlightColorBtn() : CColorBtn(),
    m_pPopup(NULL)
{
    //connect(this, SIGNAL(clicked()), this, SLOT(OnClicked()));
}


/**
 *
 */
CWordHighlightColorBtn::~CWordHighlightColorBtn()
{
    if ( m_pPopup != NULL )
        delete m_pPopup;
}


/**
 *
 */
void CWordHighlightColorBtn::OnClicked()
{
    QPoint              pt( frameGeometry().right() + 1, frameGeometry().top() );

    pt = mapToGlobal(pt);
    pt.setY( QCursor::pos().y() );

    if ( m_pPopup != NULL )
        delete m_pPopup;
    
    m_pPopup = new CHighlightColorsPopup();
    connect( m_pPopup, SIGNAL(OnChooseColor(const QColor&)), this, SLOT(OnChooseColor(const QColor&)));

    m_pPopup->Show(pt, CTraceClientApp::Instance().AppSettings().ViewHighlightSettings().WordHighlights());
}


/**
 *
 */
void CWordHighlightColorBtn::OnChooseColor(const QColor &color)
{
    Color() = color;
    emit OnColorChanged(this);
}
