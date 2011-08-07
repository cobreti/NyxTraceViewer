#include "TracesView.h"
#include "ui_TracesView.h"
#include "Document/TracesDocument.hpp"
#include "TraceClientApp.hpp"
#include "MainWindow.h"
#include "View/ViewHeader.hpp"

#include <Nyx.hpp>
#include <NyxAnsiFile.hpp>

#include "View/ViewItem_TraceData.hpp"
#include "View/ViewItemDataPainter.hpp"
#include "View/ViewItemTickCountPainter.hpp"
#include "View/ViewItemThreadIdPainter.hpp"
#include "View/ViewItemBackgroundPainter.hpp"
#include "View/ViewItemModuleNamePainter.hpp"
#include "View/DrawViewItemState.hpp"
#include "View/ViewColumnSettings.hpp"
#include "View/ViewItemsModulesMgr.hpp"
#include "View/Walkers/FileWriterViewItemsWalker.hpp"

/**
 *
 */
CTracesView::CTracesView(CTracesDocument& rDoc, QWidget *parent) :
    QWidget(parent),
    m_rDoc(rDoc),
    ui( new Ui::CTracesView() ),
    m_bViewDirty(false),
    m_bKeepAtEnd(true),
    m_pHeader(NULL),
    m_ItemsWalker(rDoc.ViewItemsModulesMgr())
{
    ui->setupUi(this);

    this->setContentsMargins(0, 0, ui->m_VertScrollbar->width(), ui->m_HorzScrollbar->height());

    m_Margins.setLeft(25.0);
    m_Margins.setRight(25.0);

    m_pHeader = new CViewHeader( Settings().ColumnsSettings(), this );

	InitSettings();

    connect( ui->m_VertScrollbar, SIGNAL(sliderMoved(int)), this, SLOT(OnVertSliderPosChanged(int)));
    connect( ui->m_VertScrollbar, SIGNAL(valueChanged(int)), this, SLOT(OnVertSliderPosChanged(int)));
    connect( ui->m_HorzScrollbar, SIGNAL(sliderMoved(int)), this, SLOT(OnHorzSliderPosChanged(int)));
}


CTracesView::~CTracesView()
{
    delete m_pHeader;
}


/**
 *
 */
void CTracesView::InitFromView( const CTracesView& view )
{
    m_Settings = view.m_Settings;
    m_ItemsWalker = view.m_ItemsWalker;
    ui->m_VertScrollbar->setValue( view.ui->m_VertScrollbar->value());
    update();
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
    m_ItemsWalker.InitNewModulesPosition();

    if ( !m_ItemsWalker.ValidPos() )
        m_ItemsWalker.MoveToBegin();

    m_bViewDirty = true;
}


/**
 *
 */
void CTracesView::UpdateVisibleLines(const CViewSettings& settings)
{
    if (m_bViewDirty && this->isVisible() )
    {
//        UpdateVisibleLines();
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
        }

        update();

        m_bViewDirty = false;
    }
}

/**
 *
 */
void CTracesView::OnNewModuleViewItems( CModuleViewItems* pModule )
{
    m_ItemsWalker.OnNewModuleViewItem(pModule);
}


/**
 *
 */
void CTracesView::OnNewSessionViewItems( CModuleViewItems* pModule, CSessionViewItems* pSession )
{
    m_ItemsWalker.OnNewSessionViewItem(pModule, pSession);
}


/**
 *
 */
void CTracesView::Save( const QString& filename )
{
    CFileWriterViewItemsWalker      SaveWalker(m_ItemsWalker);
    Nyx::CAnsiFileRef               refFile = Nyx::CAnsiFile::Alloc();
    Nyx::NyxResult                  res;

    res = refFile->Create(filename.toStdString().c_str());
    if ( Nyx::Succeeded(res) )
    {
        SaveWalker.Write(refFile);
        refFile->Close();
    }
}


/**
 *
 */
void CTracesView::OnVertSliderPosChanged(int value)
{
//    if ( !m_ItemsWalker.MoveTo(value) )
//        m_ItemsWalker.MoveToBegin();

    if ( m_ItemsWalker.MoveTo(value) )
    {
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

    m_pHeader->move( this->ClientRect().left(), this->ClientRect().top());
    m_pHeader->resize( event->size().width()-nWidth, m_pHeader->size().height() );

    UpdateScrollbarRange( ClientRect(rcWnd) );

    update();
}


void CTracesView::paintEvent(QPaintEvent*)
{
    QPainter                            painter(this);
    CDrawViewItemState                  drawstate(&painter);
    qreal                               ViewHeight = (qreal) ClientRect().height() + HeaderSize().height();
    CViewItem*                          pItem = NULL;
    bool                                bContinue = true;

    drawstate.TextPos() = QPointF(0.0, HeaderSize().height());

    m_ItemsWalker.PushState();

	painter.setClipping(true);
    painter.setClipRect(0, HeaderSize().height(), ClientRect().width(), ViewHeight);

    drawstate.TextPos().ry() = m_ItemsWalker.ItemYPos() - ui->m_VertScrollbar->value() + HeaderSize().height();

    drawstate.ViewRect() = QRectF(  ui->m_HorzScrollbar->value(), 
                                    ui->m_VertScrollbar->value(),
                                    ClientRect().width()+ui->m_HorzScrollbar->value(), 
                                    ClientRect().height()+ui->m_VertScrollbar->value());

    while ( bContinue && m_ItemsWalker.ValidPos() && drawstate.TextPos().y() < ViewHeight )
    {
        drawstate.TextPos().rx() = -ui->m_HorzScrollbar->value();

        pItem = m_ItemsWalker.Item();

        drawstate.LineNumber() = m_ItemsWalker.LineNumber();
        pItem->Display(Settings(), drawstate);

        bContinue = m_ItemsWalker.MoveToNext();
    }

    m_ItemsWalker.PopState();
}


void CTracesView::closeEvent(QCloseEvent* event)
{
	event->accept();
}


void CTracesView::UpdateScrollbarRange(const QRect& rcClient)
{
    int nScrollHeight = Nyx::Max((int)(m_ItemsWalker.Height()) - rcClient.height() + ui->m_HorzScrollbar->height(), 0);
    int nScrollWidth = Nyx::Max((int)(m_Settings.ColumnsSettings().GetTotalWidth()) - rcClient.width() + ui->m_VertScrollbar->width() + 20,  0);


    ui->m_VertScrollbar->setMaximum( nScrollHeight );
    ui->m_HorzScrollbar->setMaximum( nScrollWidth );

    ui->m_VertScrollbar->setSingleStep( m_Settings.DrawSettings()->SingleLineHeight() );
	ui->m_VertScrollbar->setPageStep( rcClient.height() );
    ui->m_HorzScrollbar->setSingleStep(20);
    ui->m_HorzScrollbar->setPageStep( rcClient.width()/2 );

    if ( m_ItemsWalker.ValidPos() && isVisible() && m_ItemsWalker.ItemYPos() != ui->m_VertScrollbar->value())
    {
        m_ItemsWalker.MoveTo(ui->m_VertScrollbar->value());
    }
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
    if ( Qt::ControlModifier == event->modifiers() && event->pos().y() > m_pHeader->size().height() )
	{
        float       y = m_ItemsWalker.ItemYPos() - ui->m_VertScrollbar->value() + HeaderSize().height();
        bool        bContinue = true;
        qreal       ViewHeight = (qreal) ClientRect().height() + HeaderSize().height();

        m_ItemsWalker.PushState();

        while ( bContinue && m_ItemsWalker.ValidPos() && y < ViewHeight )
        {
            CViewItem*      pItem = m_ItemsWalker.Item();

            if ( event->pos().y() >= y && event->pos().y() <= y + pItem->GetSize().height() )
                pItem->SetFlag(CViewItem::eVIF_Marked, !pItem->HasFlag(CViewItem::eVIF_Marked));

            y += pItem->GetSize().height();

            bContinue = m_ItemsWalker.MoveToNext();
        }

        m_ItemsWalker.PopState();

        update();
	}
}


/**
 *
 */
void CTracesView::wheelEvent(QWheelEvent* event)
{
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;

	int	value = Nyx::Max(0, ui->m_VertScrollbar->value() - (ui->m_VertScrollbar->singleStep()*numSteps));
	ui->m_VertScrollbar->setValue( value );
}


/**
 *
 */
void CTracesView::showEvent( QShowEvent* )
{
}


void CTracesView::InitSettings()
{
	CViewColumnSettings*		pColSettings = NULL;

    m_Settings = Doc().DefaultViewSettings();

    Settings().DrawSettings() = &CTraceClientApp::Instance().AppSettings().DefaultDrawSettings();

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
    QSize       size;

    if ( m_pHeader )
        size += m_pHeader->size();

    return size;
}


/**
 *
 */
bool CTracesView::UpdateVisibleLines()
{
    CDrawViewItemState                  drawstate(NULL);
    qreal                               ViewHeight = (qreal) this->rect().height();
    CViewItem*                          pItem = NULL;
    bool                                bContinue = true;

    m_ItemsWalker.PushState();

    drawstate.TextPos() = QPointF(0.0, 0.0);

    drawstate.TextPos().ry() = m_ItemsWalker.ItemYPos() - ui->m_VertScrollbar->value();

    while ( bContinue && m_ItemsWalker.ValidPos() && !(drawstate.TextPos().y() > ViewHeight+20) )
    {
        drawstate.TextPos().rx() = -ui->m_HorzScrollbar->value();

        pItem = m_ItemsWalker.Item();

        if ( pItem->HasFlag(CViewItem::eVIF_ApproxSize) )
        {
            pItem->EvaluateSize(Settings());

            Doc().ViewItemsModulesMgr().OnItemWidthChanged(pItem);

            pItem->RemoveFlag(CViewItem::eVIF_ApproxSize);
        }

        bContinue = m_ItemsWalker.MoveToNext();
    }

    m_ItemsWalker.PopState();

    return true;
}
