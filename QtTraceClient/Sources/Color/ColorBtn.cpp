#include "TraceClientApp.h"
#include "ColorBtn.h"
#include "View/Highlight/HighlightColorsPopup.h"
#include "View/Highlight/HighlightBrush.hpp"

#include <QtGui>
#include <QColorDialog>


/**
 *
 */
CColorBtn::CColorBtn() : QToolButton(),
    m_Color( Qt::gray )
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
    m_pPopup(NULL),
    m_pBrush(NULL)
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
    connect( m_pPopup, SIGNAL(OnChooseBrush(CHighlightBrush*)), this, SLOT(OnChooseBrush(CHighlightBrush*)));

    m_pPopup->Show(pt, CTraceClientApp::Instance().AppSettings().ViewHighlightSettings().WordHighlights());
}


/**
 *
 */
void CWordHighlightColorBtn::OnChooseBrush(CHighlightBrush *pBrush)
{
    m_pBrush = pBrush;
    Color() = pBrush->Color();
    emit OnWordHighlightChanged(this);
}


//=====================================================================


/**
 *
 */
CHighlightBrushBtn::CHighlightBrushBtn() : CColorBtn(),
    m_pBrush(NULL)
{
}


/**
 *
 */
CHighlightBrushBtn::~CHighlightBrushBtn()
{
}


/**
 *
 */
void CHighlightBrushBtn::SetBrush(CHighlightBrush *pBrush)
{
    m_pBrush = pBrush;
    if ( m_pBrush )
        Color() = pBrush->Color();
}


/**
 *
 */
void CHighlightBrushBtn::OnClicked()
{
    if ( m_pBrush )
        emit OnBrushSelected(this);
}
