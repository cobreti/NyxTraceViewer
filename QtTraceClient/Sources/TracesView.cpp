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
#include "View/Walkers/FileWriterViewItemsWalker.hpp"

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
    {
        if ( m_ItemsWalker.MoveToBegin() )
        {
            Nyx::CTraceStream(0x0)
                    << Nyx::CTF_Text(L"OnNewTraces - Walker  MoveToBegin");
            m_ItemsWalker.ItemPos().Item()->dbgOutputInfo();
        }
    }

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
    Nyx::CTraceStream(0x0).Write("CTracesView::OnNewModuleViewItems : %X", pModule);

    m_ItemsWalker.OnNewModuleViewItem(pModule);
}


/**
 *
 */
void CTracesView::OnNewSessionViewItems( CModuleViewItems* pModule, CSessionViewItems* pSession )
{
    Nyx::CTraceStream(0x0).Write("CTracesView::OnNewSessionViewItems : %X : %X", pModule, pSession);

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
    if ( Doc().ViewItems().ItemsCount() > 0 )
    {
        m_ItemsWalker.MoveTo(value);

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
    if ( Doc().ViewItems().ItemsCount() == 0 )
        return;

    QPainter                            painter(this);
    CDrawViewItemState                  drawstate(&painter);
    qreal                               ViewHeight = (qreal) ClientRect().height() + HeaderSize().height();
    CViewItem*                          pItem = NULL;
    bool                                bContinue = true;

    drawstate.TextPos() = QPointF(0.0, HeaderSize().height());

    m_ItemsWalker.PushState();

	painter.setClipping(true);
    painter.setClipRect(0, HeaderSize().height(), ClientRect().width(), ViewHeight);

    drawstate.TextPos().ry() = m_ItemsWalker.ItemYPos()/*pos.Y()*/ - ui->m_VertScrollbar->value() + HeaderSize().height();

    drawstate.ViewRect() = QRectF(  ui->m_HorzScrollbar->value(), 
                                    ui->m_VertScrollbar->value(),
                                    ClientRect().width()+ui->m_HorzScrollbar->value(), 
                                    ClientRect().height()+ui->m_VertScrollbar->value());

    while ( bContinue && m_ItemsWalker.ValidPos() && drawstate.TextPos().y() < ViewHeight )
    {
        drawstate.TextPos().rx() = -ui->m_HorzScrollbar->value();

        pItem = m_ItemsWalker.ItemPos().Item();

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
    int nScrollHeight = Nyx::Max((int)(Doc().ViewItems().GetSize().height()) - rcClient.height() + (int)Doc().ViewItems().GetLastLineSize().height() + ui->m_HorzScrollbar->height(), 0);
    int nScrollWidth = Nyx::Max((int)(m_Settings.ColumnsSettings().GetTotalWidth()) - rcClient.width() + ui->m_VertScrollbar->width() + 20,  0);


    ui->m_VertScrollbar->setMaximum( nScrollHeight );
    ui->m_HorzScrollbar->setMaximum( nScrollWidth );

    ui->m_VertScrollbar->setSingleStep( Doc().ViewItems().GetMaxLineSize().height() );
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
    if ( Qt::ControlModifier == event->modifiers() && Doc().ViewItems().ItemsCount() > 0 && event->pos().y() > m_pHeader->size().height() )
	{
        bool        bItemStateChanged = false;

        m_ItemsWalker.PushState();
        if ( m_ItemsWalker.MoveTo( event->pos().y() + ui->m_VertScrollbar->value() - HeaderSize().height() ) )
        {
            CViewItem*  pItem = m_ItemsWalker.ItemPos().Item(); /*pos.Item();*/

            pItem->SetFlag(CViewItem::eVIF_Marked, !pItem->HasFlag(CViewItem::eVIF_Marked));

            bItemStateChanged = true;
        }
        m_ItemsWalker.PopState();


        if ( bItemStateChanged )
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

	// Line number
	pColSettings = new CViewColumnSettings();
	pColSettings->SetWidth(0);
    pColSettings->Margins() = CViewItemMargins(10, 0, 10, 0);
    pColSettings->AutoWidth() = true;
    pColSettings->SetPainterId( CViewItemPainter::ePId_LineNumber );
    pColSettings->SetTitle("Line #");
	Settings().ColumnsSettings().Set( eVCI_LineNumber, pColSettings );

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
    if ( Doc().ViewItems().ItemsCount() == 0 )
        return false;

    CDrawViewItemState                  drawstate(NULL);
    qreal                               ViewHeight = (qreal) this->rect().height();
    CViewItem*                          pItem = NULL;
    bool                                bSizeUpdate = false;
    bool                                bContinue = true;

    m_ItemsWalker.PushState();

    drawstate.TextPos() = QPointF(0.0, 0.0);

    drawstate.TextPos().ry() = m_ItemsWalker.ItemYPos() /*pos.Y()*/ - ui->m_VertScrollbar->value();

    while ( bContinue && m_ItemsWalker.ValidPos() && !(drawstate.TextPos().y() > ViewHeight+20) )
    {
        drawstate.TextPos().rx() = -ui->m_HorzScrollbar->value();

        pItem = m_ItemsWalker.ItemPos().Item();

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

        bContinue = m_ItemsWalker.MoveToNext();
    }

    m_ItemsWalker.PopState();

    return bSizeUpdate;
}
