#include <Nyx.hpp>
#include <NyxAnsiFile.hpp>

#include "TracesView.h"
#include "ui_TracesView.h"
#include "TraceClientApp.h"
#include "View/ViewHeader.hpp"


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
#include "View/Walkers/ViewItemsWalker.hpp"
#include "View/Highlight/ViewItemPattern_Text.hpp"


/**
 *
 */
CTracesView::CTracesView(QWidget* pParent, CTracesView* pBase) :
    QWidget(pParent),
    ui( new Ui::CTracesView() ),
    m_bViewDirty(false),
    m_bKeepAtEnd(true),
    m_pHeader(NULL),
    m_pItemsWalker(NULL)
{
    Init(pBase);
}


CTracesView::~CTracesView()
{
    delete m_pHeader;
    delete m_pItemsWalker;
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
    CViewItemsWalker::MethodsInterfaceRef   refMethods(m_pItemsWalker);

    refMethods->InitNewModulesPosition();

    if ( !refMethods->ValidPos() )
        refMethods->MoveToBegin();

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
    CViewItemsWalker::MethodsInterfaceRef   refMethods(m_pItemsWalker);

    refMethods->OnNewModuleViewItem(pModule);
}


/**
 *
 */
void CTracesView::OnNewSessionViewItems( CModuleViewItems* pModule, CSessionViewItems* pSession )
{
    CViewItemsWalker::MethodsInterfaceRef   refMethods(m_pItemsWalker);

    refMethods->OnNewSessionViewItem(pModule, pSession);
}


/**
 *
 */
void CTracesView::OnModuleRemoved( const Nyx::CAString& ModuleName )
{
    delete m_pItemsWalker;
    m_pItemsWalker = new CViewItemsWalker(m_refViewCore->ViewItemsModulesMgr());

    m_bViewDirty = true;
    RefreshDisplay();
}


/**
 *
 */
void CTracesView::Save( const QString& filename )
{
    CFileWriterViewItemsWalker      SaveWalker(*m_pItemsWalker);
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
void CTracesView::SetHighlightText( const QString& text )
{
    m_refSearchPattern->TextToMatch() = text;
    m_bViewDirty = true;
}



/**
 *
 */
void CTracesView::OnVertSliderPosChanged(int value)
{
    CViewItemsWalker::MethodsInterfaceRef   refMethods(m_pItemsWalker);

    if ( refMethods->MoveTo(value) )
    {
        m_bKeepAtEnd = value == ui->m_VertScrollbar->maximum();
        //update();
    }


    update();
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
    QPainter                                painter(this);
    CDrawViewItemState                      drawstate(&painter);
    qreal                                   ViewHeight = (qreal) ClientRect().height() + HeaderSize().height();
    CViewItem*                              pItem = NULL;
    bool                                    bContinue = true;
    CViewItemsWalker::MethodsInterfaceRef   refMethods(m_pItemsWalker);

    drawstate.TextPos() = QPointF(0.0, HeaderSize().height());

    refMethods->PushState();

	painter.setClipping(true);
    painter.setClipRect(0, HeaderSize().height(), ClientRect().width(), ViewHeight);

    drawstate.TextPos().ry() = refMethods->ItemYPos() - ui->m_VertScrollbar->value() + HeaderSize().height();

    drawstate.ViewRect() = QRectF(  ui->m_HorzScrollbar->value(), 
                                    ui->m_VertScrollbar->value(),
                                    ClientRect().width()+ui->m_HorzScrollbar->value(), 
                                    ClientRect().height()+ui->m_VertScrollbar->value());

    drawstate.Highlighter() = (CViewItemHighlighter*)Highlighters();

    while ( bContinue && refMethods->ValidPos() && drawstate.TextPos().y() < ViewHeight )
    {
        drawstate.TextPos().rx() = -ui->m_HorzScrollbar->value();

        pItem = refMethods->Item();

        drawstate.LineNumber() = refMethods->LineNumber();
        pItem->Display(Settings(), drawstate);

        bContinue = refMethods->MoveToNext();
    }

    refMethods->PopState();
}


void CTracesView::closeEvent(QCloseEvent* event)
{
    m_refViewCore->ViewItemsModulesMgr().Listeners().Remove( static_cast<IViewItemsModulesListener*>(this) );
    m_refViewCore->RemoveView(this);
	event->accept();
}


void CTracesView::UpdateScrollbarRange(const QRect& rcClient)
{
    CViewItemsWalker::MethodsInterfaceRef   refMethods(m_pItemsWalker);
    CViewSettings&                          rSettings = ViewCore()->ViewSettings();

    int nScrollHeight = Nyx::Max((int)(refMethods->Height()) - rcClient.height() + ui->m_HorzScrollbar->height(), 0);
    int nScrollWidth = Nyx::Max((int)(rSettings.ColumnsSettings().GetTotalWidth()) - rcClient.width() + ui->m_VertScrollbar->width() + 20,  0);

    ui->m_VertScrollbar->setMaximum( nScrollHeight );
    ui->m_HorzScrollbar->setMaximum( nScrollWidth );

    ui->m_VertScrollbar->setSingleStep( rSettings.DrawSettings()->SingleLineHeight() );
	ui->m_VertScrollbar->setPageStep( rcClient.height() );
    ui->m_HorzScrollbar->setSingleStep(20);
    ui->m_HorzScrollbar->setPageStep( rcClient.width()/2 );
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
    CViewItemsWalker::MethodsInterfaceRef   refMethods(m_pItemsWalker);

    if ( Qt::ControlModifier == event->modifiers() && event->pos().y() > m_pHeader->size().height() )
	{
        float       y = refMethods->ItemYPos() - ui->m_VertScrollbar->value() + HeaderSize().height();
        bool        bContinue = true;
        qreal       ViewHeight = (qreal) ClientRect().height() + HeaderSize().height();

        refMethods->PushState();

        while ( bContinue && refMethods->ValidPos() && y < ViewHeight )
        {
            CViewItem*      pItem = refMethods->Item();

            if ( event->pos().y() >= y && event->pos().y() <= y + pItem->GetSize().height() )
                pItem->SetFlag(CViewItem::eVIF_Marked, !pItem->HasFlag(CViewItem::eVIF_Marked));

            y += pItem->GetSize().height();

            bContinue = refMethods->MoveToNext();
        }

        refMethods->PopState();

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


/**
 *
 */
void CTracesView::Init(CTracesView* pBase)
{
    ui->setupUi(this);

    this->setContentsMargins(0, 0, ui->m_VertScrollbar->width(), ui->m_HorzScrollbar->height());

    m_Margins.setLeft(25.0);
    m_Margins.setRight(25.0);

    if ( pBase )
    {
        m_refViewCore = pBase->ViewCore();

        m_pItemsWalker = new CViewItemsWalker(m_refViewCore->ViewItemsModulesMgr());
        m_pItemsWalker->Clone(*pBase->m_pItemsWalker);

        ui->m_VertScrollbar->setValue( pBase->ui->m_VertScrollbar->value());
    }
    else
    {
        m_refViewCore = new CTracesViewCore();
        m_pItemsWalker = new CViewItemsWalker(m_refViewCore->ViewItemsModulesMgr());

        Settings().DrawSettings() = &CTraceClientApp::Instance().AppSettings().DefaultDrawSettings();
    }

    m_refHighlighters = new CViewItemHighlightersSet();
    m_refSearchPattern = new CViewItemPattern_Text();
    
    CViewItemHighlighterRef     refSearchHighlighter = new CViewItemHighlighter();
    refSearchHighlighter->Pattern() = (CViewItemPattern*)m_refSearchPattern;
    //m_refSearchPattern->TextToMatch() = "st";
    m_refHighlighters->Add( refSearchHighlighter );

    m_pHeader = new CViewHeader( Settings().ColumnsSettings(), this );
    m_pHeader->InitDefaultWidth();

    m_refViewCore->AddView(this);
    m_refViewCore->ViewItemsModulesMgr().Listeners().Insert( static_cast<IViewItemsModulesListener*>(this) );

    connect( ui->m_VertScrollbar, SIGNAL(sliderMoved(int)), this, SLOT(OnVertSliderPosChanged(int)));
    connect( ui->m_VertScrollbar, SIGNAL(valueChanged(int)), this, SLOT(OnVertSliderPosChanged(int)));
    connect( ui->m_HorzScrollbar, SIGNAL(sliderMoved(int)), this, SLOT(OnHorzSliderPosChanged(int)));
    connect( &m_RefreshTimer, SIGNAL(timeout()), this, SLOT(RefreshDisplay()));

    m_RefreshTimer.start(250);

    if ( pBase )
        update();
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
    CDrawViewItemState                      drawstate(NULL);
    qreal                                   ViewHeight = (qreal) this->rect().height();
    CViewItem*                              pItem = NULL;
    bool                                    bContinue = true;
    CViewItemsWalker::MethodsInterfaceRef   refMethods(*m_pItemsWalker);

    refMethods->PushState();

    drawstate.TextPos() = QPointF(0.0, 0.0);

    drawstate.TextPos().ry() = refMethods->ItemYPos() - ui->m_VertScrollbar->value();

    while ( bContinue && refMethods->ValidPos() && !(drawstate.TextPos().y() > ViewHeight+20) )
    {
        drawstate.TextPos().rx() = -ui->m_HorzScrollbar->value();

        pItem = refMethods->Item();

        if ( pItem->HasFlag(CViewItem::eVIF_ApproxSize) )
        {
            pItem->EvaluateSize(Settings());

            m_refViewCore->ViewItemsModulesMgr().OnItemWidthChanged(pItem);

            pItem->RemoveFlag(CViewItem::eVIF_ApproxSize);
        }

        bContinue = refMethods->MoveToNext();
    }

    refMethods->PopState();

    return true;
}
