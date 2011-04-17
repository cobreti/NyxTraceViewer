#include <QtGui>


#include "TracesView.h"
#include "ui_TracesView.h"
#include "TracesDocument.hpp"

#include <Nyx.hpp>

#include "View/ViewItem_TraceData.hpp"
#include "View/ViewItemDataPainter.hpp"
#include "View/ViewItemTickCountPainter.hpp"
#include "View/ViewItemThreadIdPainter.hpp"
#include "View/ViewItemBackgroundPainter.hpp"
#include "View/ViewItemModuleNamePainter.hpp"
#include "View/DrawViewItemState.hpp"
#include "View/ViewColumnSettings.hpp"
#include "View/ViewHeader.hpp"

/**
 *
 */
CTracesView::CTracesView(CTracesDocument& rDoc, QWidget *parent) :
    QWidget(parent),
    m_rDoc(rDoc),
    m_MaxLineSize(1.0, 1.0),
    ui( new Ui::CTracesView() ),
    m_bViewDirty(false),
    m_bKeepAtEnd(true),
    m_pHeader(NULL)
{
    ui->setupUi(this);

    this->setContentsMargins(0, 0, ui->m_VertScrollbar->width(), ui->m_HorzScrollbar->height());
    //this->setMinimumSize(500, 500);

    connect( ui->m_VertScrollbar, SIGNAL(sliderMoved(int)), this, SLOT(OnVertSliderPosChanged(int)));
    connect( ui->m_VertScrollbar, SIGNAL(valueChanged(int)), this, SLOT(OnVertSliderPosChanged(int)));
    connect( ui->m_HorzScrollbar, SIGNAL(sliderMoved(int)), this, SLOT(OnHorzSliderPosChanged(int)));

	m_Margins.setLeft(25.0);
	m_Margins.setRight(25.0);

    m_pHeader = new CViewHeader( Settings().ColumnsSettings(), this );

	InitSettings();

    if ( Doc().ViewItems().ItemsCount() > 0 )
        m_TopPos = Doc().ViewItems().begin();
}


CTracesView::~CTracesView()
{
    delete m_pHeader;
}


/**
 *
 */
void CTracesView::SetName(const QString& name)
{
	m_Name = name;
	window()->setWindowTitle(name);
}



/**
 *
 */
void CTracesView::OnNewTraces()
{
    if ( !m_TopPos.IsValid() )
        m_TopPos = Doc().ViewItems().begin();

    m_bViewDirty = true;
}


/**
 *
 */
void CTracesView::UpdateVisibleLines(const CViewSettings& settings)
{
    m_Settings.UpdateFrom(settings);

    if (m_bViewDirty && this->isVisible() )
    {
        UpdateVisibleLines();
    }
}


/**
 *
 */
void CTracesView::RefreshDisplay()
{
    if (m_bViewDirty && this->isVisible() )
    {
        UpdateScrollbarRange(ClientRect());

        if ( m_bKeepAtEnd )
        {
            ui->m_VertScrollbar->setValue( ui->m_VertScrollbar->maximum() );
            m_TopPos.MoveTo( ui->m_VertScrollbar->value() );
        }

        update();

        m_bViewDirty = false;
    }
}


void CTracesView::OnVertSliderPosChanged(int value)
{
    if ( Doc().ViewItems().ItemsCount() > 0 )
    {
        m_TopPos.MoveTo(value);
        m_bKeepAtEnd = value == ui->m_VertScrollbar->maximum();
        update();
    }
}


void CTracesView::OnHorzSliderPosChanged(int value)
{
    m_pHeader->SetHorzOffset(value);

    update();
}


void CTracesView::resizeEvent(QResizeEvent *event)
{
    int     nHeight = ui->m_HorzScrollbar->height();
    int     nWidth = ui->m_VertScrollbar->width();
    QRect   rcWnd(  QPoint(0,0), event->size() );

    ui->m_HorzScrollbar->resize( event->size().width()-nHeight, nHeight );
    ui->m_HorzScrollbar->move(0, event->size().height()-nHeight);

    ui->m_VertScrollbar->resize( nWidth, event->size().height()-nWidth );
    ui->m_VertScrollbar->move(event->size().width()-nWidth, 0);

    m_pHeader->move(0,0);
    m_pHeader->resize( event->size().width()-nWidth, m_pHeader->size().height() );

    UpdateScrollbarRange( ClientRect(rcWnd) );

    update();
}


void CTracesView::paintEvent(QPaintEvent*)
{
    if ( Doc().ViewItems().ItemsCount() == 0 )
        return;

    QPainter                            painter(this);
    CDrawViewItemState                  drawstate(painter);
    qreal                               ViewHeight = (qreal) ClientRect().height() + HeaderSize().height();
    CViewItemPos                        pos = m_TopPos;
    CViewItem*                          pItem = NULL;

    drawstate.TextPos() = QPointF(0.0, HeaderSize().height());

	painter.setClipping(true);
    painter.setClipRect(0, HeaderSize().height(), ClientRect().width(), ViewHeight);

    drawstate.TextPos().ry() = pos.Y() - ui->m_VertScrollbar->value() + HeaderSize().height();

    drawstate.ViewRect() = QRectF(  ui->m_HorzScrollbar->value(), 
                                    ui->m_VertScrollbar->value(),
                                    ClientRect().width()+ui->m_HorzScrollbar->value(), 
                                    ClientRect().height()+ui->m_VertScrollbar->value());


    while ( pos.IsValid() && drawstate.TextPos().y() < ViewHeight )
    {
        drawstate.TextPos().rx() = -ui->m_HorzScrollbar->value();

        pItem = pos.Item();

        pItem->Display(Settings(), drawstate);

        ++pos;
    }
}


void CTracesView::closeEvent(QCloseEvent* event)
{
	event->accept();
}


void CTracesView::UpdateScrollbarRange(const QRect& rcClient)
{
    int nScrollHeight = Nyx::Max((int)(Doc().ViewItems().GetSize().height()) - rcClient.height() + (int)Doc().ViewItems().GetLastLineSize().height() + ui->m_HorzScrollbar->height(), 0);
    int nScrollWidth = Nyx::Max((int)(m_Settings.ColumnsSettings().GetTotalWidth()) - rcClient.width() + ui->m_VertScrollbar->width() + 20,  0);


    ui->m_VertScrollbar->setMaximum( nScrollHeight );
    ui->m_HorzScrollbar->setMaximum( nScrollWidth );

    ui->m_VertScrollbar->setSingleStep( Doc().ViewItems().GetLastLineSize().height() );
	ui->m_VertScrollbar->setPageStep( rcClient.height() );
    ui->m_HorzScrollbar->setSingleStep(20);
    ui->m_HorzScrollbar->setPageStep( rcClient.width()/2 );

    if ( m_TopPos.IsValid() )
        m_TopPos.MoveTo(ui->m_VertScrollbar->value());
}


void CTracesView::keyPressEvent( QKeyEvent* event )
{
	switch ( event->key() )
	{
		case Qt::Key_Up:
			{
				int	value = Nyx::Max(0, ui->m_VertScrollbar->value() - ui->m_VertScrollbar->singleStep());
				ui->m_VertScrollbar->setValue( value );
			}
			break;
		case Qt::Key_Down:
			{
				int	value = Nyx::Min(ui->m_VertScrollbar->maximum(), ui->m_VertScrollbar->value() + ui->m_VertScrollbar->singleStep());
				ui->m_VertScrollbar->setValue( value );
			}
			break;
		case Qt::Key_PageUp:
			{
				int	value = Nyx::Max(0, ui->m_VertScrollbar->value() - ui->m_VertScrollbar->pageStep());
				ui->m_VertScrollbar->setValue( value );
			}
			break;
		case Qt::Key_PageDown:
			{
				int	value = Nyx::Min(ui->m_VertScrollbar->maximum(), ui->m_VertScrollbar->value() + ui->m_VertScrollbar->pageStep());
				ui->m_VertScrollbar->setValue( value );
			}
			break;
		case Qt::Key_Home:
			{
				ui->m_VertScrollbar->setValue(0);
			}
			break;
		case Qt::Key_End:
			{
				ui->m_VertScrollbar->setValue(ui->m_VertScrollbar->maximum());
			}
			break;
	};
}


void CTracesView::mousePressEvent( QMouseEvent* event )
{
    if ( Qt::ControlModifier == event->modifiers() && Doc().ViewItems().ItemsCount() > 0 && event->pos().y() > m_pHeader->size().height() )
	{
        CViewItemPos        pos = Doc().ViewItems().begin();
        pos.MoveTo( event->pos().y() + ui->m_VertScrollbar->value() - HeaderSize().height() );

        CViewItem*  pItem = pos.Item();

        pItem->SetFlag(CViewItem::eVIF_Marked, !pItem->HasFlag(CViewItem::eVIF_Marked));

		this->update();
	}
}


void CTracesView::wheelEvent(QWheelEvent* event)
{
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;

	int	value = Nyx::Max(0, ui->m_VertScrollbar->value() - (ui->m_VertScrollbar->singleStep()*numSteps));
	ui->m_VertScrollbar->setValue( value );
}


void CTracesView::InitSettings()
{
	CViewColumnSettings*		pColSettings = NULL;

	// Module name
	pColSettings = new CViewColumnSettings();
	pColSettings->SetWidth(0);
    pColSettings->Margins() = CViewItemMargins(10, 0, 10, 0);
    pColSettings->AutoWidth() = true;
    pColSettings->SetPainterId( CViewItemPainter::ePId_ModuleName );
    pColSettings->SetTitle("Module Name");
	Settings().ColumnsSettings().Set( eVCI_ModuleName, pColSettings );

	// TickCount
	pColSettings = new CViewColumnSettings();
    pColSettings->SetWidth(0);
    pColSettings->Margins() = CViewItemMargins(10, 0, 10, 0);
    pColSettings->AutoWidth() = true;
    pColSettings->SetPainterId( CViewItemPainter::ePId_TickCount );
    pColSettings->SetTitle("TickCount");
    Settings().ColumnsSettings().Set( eVCI_TickCount, pColSettings );

	// ThreadId
	pColSettings = new CViewColumnSettings();
	pColSettings->SetWidth(0);
    pColSettings->Margins() = CViewItemMargins(10, 0, 10, 0);
    pColSettings->AutoWidth() = true;
    pColSettings->SetPainterId( CViewItemPainter::ePId_ThreadId );
    pColSettings->SetTitle("Thread Id");
    Settings().ColumnsSettings().Set( eVCI_ThreadId, pColSettings );

	// data
	pColSettings = new CViewColumnSettings();
	pColSettings->SetWidth(0);
    pColSettings->Margins() = CViewItemMargins(10, 0, 20, 0);
    pColSettings->AutoWidth() = true;
    pColSettings->SetPainterId( CViewItemPainter::ePId_Data );
    pColSettings->SetTitle("Data");
	Settings().ColumnsSettings().Set( eVCI_Data, pColSettings );

    m_pHeader->InitDefaultWidth();
}


/**
 *
 */
QRect CTracesView::ClientRect( const QRect& rcWnd ) const
{
    return QRect(   0, 0,
                    rcWnd.width() - ui->m_VertScrollbar->width(),
                    rcWnd.height() - ui->m_HorzScrollbar->height() - HeaderSize().height() );
}


/**
 *
 */
QSize CTracesView::HeaderSize() const
{
    if ( m_pHeader )
        return m_pHeader->size();

    return QSize();
}


/**
 *
 */
bool CTracesView::UpdateVisibleLines()
{
    if ( Doc().ViewItems().ItemsCount() == 0 )
        return false;

    QPainter                            painter(this);
    CDrawViewItemState                  drawstate(painter);
    qreal                               ViewHeight = (qreal) this->rect().height();
    CViewItemPos                        pos = m_TopPos;
    CViewItem*                          pItem = NULL;
    bool                                bSizeUpdate = false;

    drawstate.TextPos() = QPointF(0.0, 0.0);

    drawstate.TextPos().ry() = pos.Y() - ui->m_VertScrollbar->value();

    while ( pos.IsValid() && !(drawstate.TextPos().y() > ViewHeight+20) )
    {
        drawstate.TextPos().rx() = -ui->m_HorzScrollbar->value();

        pItem = pos.Item();

        if ( pItem->HasFlag(CViewItem::eVIF_ApproxSize) )
        {
            Doc().ViewItems().RemoveFromClientSize(pItem);

            pItem->EvaluateSize(Doc().DefaultViewSettings());

            if (pItem->GetSize().width() > m_MaxLineSize.width() )
                m_MaxLineSize.setWidth(pItem->GetSize().width());
            if (pItem->GetSize().height() > m_MaxLineSize.height() )
                m_MaxLineSize.setHeight(pItem->GetSize().height());

            Doc().ViewItems().AddToClientSize(pItem);

            pItem->RemoveFlag(CViewItem::eVIF_ApproxSize);
            bSizeUpdate = true;
        }

        ++pos;
    }

    return bSizeUpdate;
}
