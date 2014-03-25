#include <Nyx.hpp>
#include <NyxAnsiFile.hpp>

#include "TracesView.h"
#include "TracesView.hpp"
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
#include "View/Highlight/HighlightColorsPopup.h"
#include "TracesGroup.hpp"
#include "View/ViewTracesIterator.hpp"
#include "View/ViewTracePainter.h"

/**
 *
 */
CTracesView::CTracesView(QWidget* pParent, CTracesView* pBase) :
    QWidget(pParent),
    ui( new Ui::CTracesView() ),
    m_bViewDirty(false),
    m_bKeepAtEnd(true),
    m_pHeader(NULL),
    m_pItemsWalker(NULL),
    m_pLastSelectedItem(NULL),
    m_pHighlightColorsPopup(NULL),
    m_pCurrentTracesGroup(NULL)
{
    Init(pBase);
}


CTracesView::~CTracesView()
{
    delete m_pHeader;
    delete m_pItemsWalker;
    delete m_pHighlightColorsPopup;
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
//    CViewItemsWalker::MethodsInterfaceRef   refMethods(m_pItemsWalker);

//    refMethods->InitNewModulesPosition();

//    if ( !refMethods->ValidPos() )
//        refMethods->MoveToBegin();

//    m_bViewDirty = true;
}


/**
 *
 */
void CTracesView::RefreshDisplay()
{
//    if (m_bViewDirty && this->isVisible() )
//    {
//        UpdateScrollbarRange(ClientRect());

//        if ( m_bKeepAtEnd )
//        {
//            ui->m_VertScrollbar->setValue( ui->m_VertScrollbar->maximum() );
//        }

//        update();

//        m_bViewDirty = false;
//    }
}


/**
 *
 */
void CTracesView::OnChooseHighlightBrush( CHighlightBrush* pBrush )
{
    if ( m_pLastSelectedItem )
        m_pLastSelectedItem->HighlightBrush() = pBrush;

    m_pLastSelectedBrush = pBrush;
    m_pLastSelectedItem = NULL;

    update();
}


/**
 * @brief CTracesView::OnViewBeginUpdate
 * @param pGroup
 * @param pView
 */
void CTracesView::OnViewBeginUpdate( TraceClientCore::CTracesGroup* pGroup, TraceClientCore::CTracesView* pView )
{

}


/**
 * @brief CTracesView::OnViewEndUpdate
 * @param pGroup
 * @param pView
 */
void CTracesView::OnViewEndUpdate( TraceClientCore::CTracesGroup* pGroup, TraceClientCore::CTracesView* pView )
{
    if ( pView->Dirty() )
    {
        UpdateScrollbarRange(ClientRect());
        update();

        int linesCount = pView->LinesCount();

        NYXTRACE(0x0, L"traces view lines count : " << Nyx::CTF_Int(linesCount));
        pView->ResetDirty();
    }
}


/**
 *
 */
void CTracesView::OnNewModuleViewItems( CModuleViewItems* pModule )
{
//    CViewItemsWalker::MethodsInterfaceRef   refMethods(m_pItemsWalker);

//    refMethods->OnNewModuleViewItem(pModule);
}


/**
 *
 */
void CTracesView::OnNewSessionViewItems( CModuleViewItems* pModule, CSessionViewItems* pSession )
{
//    CViewItemsWalker::MethodsInterfaceRef   refMethods(m_pItemsWalker);

//    refMethods->OnNewSessionViewItem(pModule, pSession);
}


/**
 *
 */
void CTracesView::OnBeginClearModule( const Nyx::CAString& ModuleName )
{
//    CViewItemsWalker::MethodsInterfaceRef   refMethods(m_pItemsWalker);

//    refMethods->Lock();
}


/**
 *
 */
void CTracesView::OnEndClearModule( const Nyx::CAString& ModuleName )
{
//    delete m_pItemsWalker;
//    m_pItemsWalker = new CViewItemsWalker(m_refViewCore->ViewItemsModulesMgr());

//    m_bViewDirty = true;
//    RefreshDisplay();
}


/**
 *
 */
void CTracesView::Save( const QString& filename )
{
//    CFileWriterViewItemsWalker      SaveWalker(*m_pItemsWalker);
//    Nyx::CAnsiFileRef               refFile = Nyx::CAnsiFile::Alloc();
//    Nyx::NyxResult                  res;

//    res = refFile->Create(filename.toStdString().c_str());
//    if ( Nyx::Succeeded(res) )
//    {
//        SaveWalker.Write(refFile);
//        refFile->Close();
//    }
}


/**
 *
 */
const QRectF CTracesView::ViewRect() const
{
    return QRectF(  0, 
                    0,
                    ClientRect().width(), 
                    ClientRect().height() - HeaderSize().height());
}


/**
 *
 */
int CTracesView::NumberOfLinesVisibles() const
{
    int                 height = ViewRect().height();
    CViewSettings&      rSettings = ViewCore()->ViewSettings();

    float               visibleLines = (height - ui->m_HorzScrollbar->height()) / rSettings.DrawSettings()->SingleLineHeight();

    return int(visibleLines - 0.5);
}

/**
 *
 */
void CTracesView::Invalidate(bool dirty)
{
//    float       ScrollBarPos = 0.0f;

//    {
//        CViewItemsWalker::MethodsInterfaceRef       refWalkerMethods(ItemsWalker());
//        ScrollBarPos = refWalkerMethods->LineNo();
////        ScrollBarPos = refWalkerMethods->ItemYPos();
//    }

//    ui->m_VertScrollbar->setValue(ScrollBarPos);
//    m_bViewDirty = dirty;
//    RefreshDisplay();
}


void CTracesView::SetTracesGroup( TraceClientCore::CTracesGroup* pGroup )
{
    m_TracesGroupNotificationsListener.ConnectTo(pGroup);
    m_pCurrentTracesGroup = pGroup;

    ui->m_HorzScrollbar->setValue(0);
    ui->m_VertScrollbar->setValue(0);
    UpdateScrollbarRange(ClientRect());

    update();
}


/**
 *
 */
void CTracesView::OnVertSliderPosChanged(int value)
{
//    CViewItemsWalker::MethodsInterfaceRef   refMethods(m_pItemsWalker);

//    if ( refMethods->MoveToLine(value) )
//    {
//        m_bKeepAtEnd = value == ui->m_VertScrollbar->maximum();
//        //update();
//    }


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


void CTracesView::paintEvent(QPaintEvent* pEvent)
{
    QPainter                                painter(this);
    CDrawViewItemState                      drawstate(&painter);
    CViewTracesIterator                     TraceIterator = CViewTracesIterator::FirstPos(m_pCurrentTracesGroup);
    qreal                                   ViewHeight = (qreal) ClientRect().height() + HeaderSize().height();
    CViewTracePainter                       TracePainter(painter);
    CViewSettings&                          rSettings = ViewCore()->ViewSettings();
//    CViewItem*                              pItem = NULL;
//    bool                                    bContinue = true;
//    CViewItemsWalker::MethodsInterfaceRef   refMethods(m_pItemsWalker);

//    drawstate.TextPos() = QPointF(0.0, HeaderSize().height());

//    refMethods->PushState();

//	painter.setClipping(true);
//    painter.setClipRect(0, HeaderSize().height(), ClientRect().width(), ViewHeight);

//    m_pHeader->update();

    QBrush  bkgndBrush = palette().base();
    painter.fillRect(pEvent->rect(), bkgndBrush);

    painter.drawLine(m_Margins.left()-1, 0, m_Margins.left()-1, ViewHeight);

    NYXTRACE(0x0, L"paint event hscroll value = " << ui->m_HorzScrollbar->value());

    painter.setClipRect(m_Margins.left(), HeaderSize().height(), ClientRect().width(), ViewHeight);

    TracePainter.Origin() = QPoint( m_Margins.left() - ui->m_HorzScrollbar->value(), HeaderSize().height());
    TracePainter.ViewSize() = QSize( ClientRect().width(), ViewHeight );
    TracePainter.LineHeight() = rSettings.DrawSettings()->SingleLineHeight();
    TracePainter.ColumnsSettings() = &rSettings.ColumnsSettings();

    TracePainter.Init();

    TraceIterator.MoveToLine(ui->m_VertScrollbar->value());

    while ( TraceIterator.Valid() && !TracePainter.Done() )
    {
        TracePainter.LineNumber() = TraceIterator.getLineNumber();
        TracePainter.Draw(TraceIterator.TraceData());

        ++ TraceIterator;
    }

    TracePainter.Release();
//    m_pHeader->update();
////    drawstate.TextPos().ry() = refMethods->ItemYPos() - ui->m_VertScrollbar->value() + HeaderSize().height();
//    drawstate.TextPos().ry() = HeaderSize().height();// - ui->m_VertScrollbar->value();

//    drawstate.ViewRect() = QRectF(  ui->m_HorzScrollbar->value(),
//                                    ui->m_VertScrollbar->value(),
//                                    ClientRect().width()+ui->m_HorzScrollbar->value(),
//                                    ClientRect().height()+ui->m_VertScrollbar->value());

//    drawstate.Highlighter() = (CViewItemHighlighter*)Highlighters();


//    while ( bContinue && refMethods->ValidPos() && drawstate.TextPos().y() < ViewHeight )
//    {
//        drawstate.TextPos().rx() = -ui->m_HorzScrollbar->value() + m_Margins.left();

//        pItem = refMethods->Item();

//        drawstate.ItemNumber() = refMethods->ItemNumber();
//        pItem->Display(Settings(), drawstate);

//        bContinue = refMethods->MoveToNext();
//    }

//    refMethods->PopState();
}


void CTracesView::closeEvent(QCloseEvent* event)
{
//    m_refViewCore->ViewItemsModulesMgr().Listeners().Remove( static_cast<IViewItemsModulesListener*>(this) );
    m_refViewCore->RemoveView(this);
	event->accept();
}


void CTracesView::UpdateScrollbarRange(const QRect& rcClient)
{
//    CViewItemsWalker::MethodsInterfaceRef   refMethods(m_pItemsWalker);
    CViewSettings&                          rSettings = ViewCore()->ViewSettings();
//    int                                     NumberOfLines = ViewCore()->ViewItemsModulesMgr().LinesCount();
    int                                     NumberOfLines = 0;
    int                                     NumberOfDisplayedLines = NumberOfLinesVisibles();

    if ( m_pCurrentTracesGroup != NULL )
    {
        NumberOfLines = m_pCurrentTracesGroup->LinesCount();
    }

//    //int nScrollHeight = Nyx::Max((int)(refMethods->Height()) - rcClient.height() + ui->m_HorzScrollbar->height(), 0);
    int nScrollHeight = Nyx::Max( NumberOfLines - NumberOfDisplayedLines, 0 );
    int nScrollWidth = Nyx::Max((int)(rSettings.ColumnsSettings().GetTotalWidth()) - rcClient.width() + ui->m_VertScrollbar->width() + 20,  0);

    ui->m_VertScrollbar->setMaximum( nScrollHeight );
    ui->m_HorzScrollbar->setMaximum( nScrollWidth );

//    ui->m_VertScrollbar->setSingleStep( rSettings.DrawSettings()->SingleLineHeight() );
    ui->m_VertScrollbar->setSingleStep( 1 );
    ui->m_VertScrollbar->setPageStep( NumberOfDisplayedLines );
    ui->m_HorzScrollbar->setSingleStep(20);
    ui->m_HorzScrollbar->setPageStep( rcClient.width()/2 );

    NYXTRACE(0x0, L"UpdateScrollBarRange : nScrollWidth = " << nScrollWidth );
    NYXTRACE(0x0, L"UpdateScrollBarRange : hscrollbar value = " << ui->m_HorzScrollbar->value());

    m_pHeader->SetHorzOffset(ui->m_HorzScrollbar->value());
    m_pHeader->update();
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
//    CViewItemsWalker::MethodsInterfaceRef   refMethods(m_pItemsWalker);

//    if ( event->pos().x() < m_Margins.left() && event->pos().y() > m_pHeader->size().height() )
//	{
////        float       y = refMethods->ItemYPos() - ui->m_VertScrollbar->value() + HeaderSize().height();
//        bool            bContinue = true;
//        CViewSettings&  rSettings = ViewCore()->ViewSettings();
//        qreal           ViewHeight = (qreal) ClientRect().height() + HeaderSize().height();
//        size_t          VisibleLineNo = (event->pos().y() - HeaderSize().height()) / rSettings.DrawSettings()->SingleLineHeight();
//        size_t          LineNo = refMethods->LineNo() + VisibleLineNo;

//        refMethods->PushState();

//        if ( refMethods->MoveToLine(LineNo) )
//        {
//            CViewItem*      pItem = refMethods->Item();

//            if ( event->button() == Qt::LeftButton )
//            {
//                if ( pItem->HasFlag(CViewItem::eVIF_Marked) )
//                {
//                    pItem->SetFlag(CViewItem::eVIF_Marked, false);
//                    pItem->HighlightBrush() = NULL;
//                }
//                else
//                {
//                    pItem->SetFlag(CViewItem::eVIF_Marked, true);
//                    pItem->HighlightBrush() = m_pLastSelectedBrush;
//                }
//            }
//            else if ( event->button() == Qt::RightButton )
//            {
//                pItem->SetFlag(CViewItem::eVIF_Marked, true);
//                m_pLastSelectedItem = pItem;

//                if ( m_pHighlightColorsPopup != NULL )
//                    delete m_pHighlightColorsPopup;

//                m_pHighlightColorsPopup = new CHighlightColorsPopup();
//                connect(    m_pHighlightColorsPopup, SIGNAL(OnChooseBrush( CHighlightBrush*)),
//                            this, SLOT(OnChooseHighlightBrush( CHighlightBrush*)));
//                m_pHighlightColorsPopup->Show( mapToGlobal(event->pos()), CTraceClientApp::Instance().AppSettings().ViewHighlightSettings().LineHighlights() );
//            }
//        }

//        refMethods->PopState();

//        update();
//	}
}


/**
 *
 */
void CTracesView::wheelEvent(QWheelEvent* event)
{
//    int numDegrees = event->delta() / 8;
//    int numSteps = numDegrees / 15;

//    int	value = Nyx::Max(0, ui->m_VertScrollbar->value() - (ui->m_VertScrollbar->singleStep()*numSteps));
//    ui->m_VertScrollbar->setValue( value );
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

    connect( &m_TracesGroupNotificationsListener, SIGNAL(ViewBeginUpdate(TraceClientCore::CTracesGroup*,TraceClientCore::CTracesView*)),
             this, SLOT(OnViewBeginUpdate(TraceClientCore::CTracesGroup*,TraceClientCore::CTracesView*)) );
    connect( &m_TracesGroupNotificationsListener, SIGNAL(ViewEndUpdate(TraceClientCore::CTracesGroup*,TraceClientCore::CTracesView*)),
             this, SLOT(OnViewEndUpdate(TraceClientCore::CTracesGroup*,TraceClientCore::CTracesView*)) );

    m_Margins.setLeft(25.0);
    m_Margins.setRight(25.0);

    if ( pBase )
    {
        m_refViewCore = pBase->ViewCore();

//        m_pItemsWalker = new CViewItemsWalker(m_refViewCore->ViewItemsModulesMgr());
//        m_pItemsWalker->Clone(*pBase->m_pItemsWalker);

        ui->m_VertScrollbar->setValue( pBase->ui->m_VertScrollbar->value());
    }
    else
    {
        m_refViewCore = new CTracesViewCore();
//        m_pItemsWalker = new CViewItemsWalker(m_refViewCore->ViewItemsModulesMgr());

        Settings().DrawSettings() = &CTraceClientApp::Instance().AppSettings().DefaultDrawSettings();
    }

    m_refHighlighters = new CViewItemHighlightersSet();

    m_pHeader = new CViewHeader( Settings().ColumnsSettings(), this );
    m_pHeader->InitDefaultWidth();
    m_pHeader->Margins() = m_Margins;

    m_refViewCore->AddView(this);
//    m_refViewCore->ViewItemsModulesMgr().Listeners().Insert( static_cast<IViewItemsModulesListener*>(this) );

    m_pLastSelectedBrush = CTraceClientApp::Instance().AppSettings().ViewHighlightSettings().LineHighlights()[0];

    m_pHighlightColorsPopup = new CHighlightColorsPopup();

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
