#include <Nyx.hpp>
#include <NyxAnsiFile.hpp>

#include "TracesView.h"
#include "TracesView.hpp"
#include "ui_TracesView.h"
#include "TraceClientApp.h"
#include "View/ViewHeader.hpp"


#include "View/DrawViewItemState.hpp"
#include "View/ViewColumnSettings.hpp"
#include "View/Highlight/ViewItemPattern_Text.hpp"
#include "View/Highlight/HighlightColorsPopup.h"
#include "TracesGroup.hpp"
#include "View/ViewTracePainter.h"
#include "View/ViewTracePicker.h"
#include "View/ViewTracePortal.h"
#include "View/Decorations/ViewTraceSectionHilight.h"


/**
 *
 */
CTracesView::CTracesView(QWidget* pParent, CTracesView* pBase) :
    QWidget(pParent),
    ui( new Ui::CTracesView() ),
    m_bViewDirty(false),
    m_bKeepAtEnd(true),
    m_pHeader(NULL),
    m_pHighlightColorsPopup(NULL),
    m_pCurrentTracesGroup(NULL)
{
    Init(pBase);
}


CTracesView::~CTracesView()
{
    delete m_pHeader;
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
}


/**
 *
 */
void CTracesView::RefreshDisplay()
{
}


/**
 *
 */
void CTracesView::OnChooseHighlightBrush( CHighlightBrush* pBrush )
{
    m_pLastSelectedBrush = pBrush;

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
void CTracesView::Save( const QString& filename )
{
    Nyx::CAnsiFileRef               refFile = Nyx::CAnsiFile::Alloc();
    Nyx::NyxResult                  res;
    CViewTracesIterator             iter = CViewTracesIterator::FirstPos(m_pCurrentTracesGroup);
    Nyx::CWString                   eol(L"\r\n");

    res = refFile->Create(filename.toStdString().c_str());
    if ( Nyx::Succeeded(res) )
    {
        while ( iter.Valid() )
        {
            Nyx::CWString   data = iter.TraceData()->Data();

            refFile->Write(data);
            refFile->Write(eol);

            ++ iter;
        }

        refFile->Close();
    }
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
}


void CTracesView::SetTracesGroup( TraceClientCore::CTracesGroup* pGroup )
{
    m_TracesGroupNotificationsListener.ConnectTo(pGroup);
    m_pCurrentTracesGroup = pGroup;
    m_TopPos = CViewTracesIterator();

    ui->m_HorzScrollbar->setValue(0);
    ui->m_VertScrollbar->setValue(0);
    UpdateScrollbarRange(ClientRect());
    m_DisplayCache.Clear();

    update();
}


/**
 *
 */
void CTracesView::OnVertSliderPosChanged(int value)
{
    m_TopPos.MoveToLine(value);
    m_DisplayCache.Clear();


    update();
}


void CTracesView::OnHorzSliderPosChanged(int value)
{
    m_pHeader->SetHorzOffset(value);
//    m_DisplayCache.Clear();

    update();
}


void CTracesView::resizeEvent(QResizeEvent *event)
{
    int     nHeight = ui->m_HorzScrollbar->height();
    int     nWidth = ui->m_VertScrollbar->width();
    QRect   rcWnd(  QPoint(0,0), event->size() );

    ui->m_HorzScrollbar->resize( event->size().width()-nHeight+1, nHeight );
    ui->m_HorzScrollbar->move(0, event->size().height()-nHeight);

    ui->m_VertScrollbar->resize( nWidth, event->size().height() );
    ui->m_VertScrollbar->move(event->size().width()-nWidth+1, 0);

    m_pHeader->move( this->ClientRect().left(), this->ClientRect().top());
    m_pHeader->resize( event->size().width()-nWidth, m_pHeader->size().height() );

    UpdateScrollbarRange( ClientRect(rcWnd) );

    update();
}


void CTracesView::paintEvent(QPaintEvent* pEvent)
{
    if ( !m_TopPos.Valid() )
    {
        m_TopPos = CViewTracesIterator::FirstPos(m_pCurrentTracesGroup);
        m_TopPos.MoveToLine(ui->m_VertScrollbar->value());
    }

    QPainter                                painter(this);
    CViewTracesIterator                     TraceIterator = m_TopPos;
    qreal                                   ViewHeight = (qreal) ClientRect().height() + HeaderSize().height();
    CViewTracePainter                       TracePainter(painter, m_DisplayCache);
    CViewSettings&                          rSettings = ViewCore()->ViewSettings();

    QBrush  bkgndBrush = palette().base();
    painter.fillRect(pEvent->rect(), bkgndBrush);

    painter.drawLine(m_Margins.left()-1, 0, m_Margins.left()-1, ViewHeight);

    painter.setClipRect(m_Margins.left(), HeaderSize().height(), ClientRect().width(), ViewHeight);

    TracePainter.Origin() = QPoint( m_Margins.left() - ui->m_HorzScrollbar->value(), HeaderSize().height());
    TracePainter.ViewSize() = QSize( ClientRect().width(), ViewHeight );
    TracePainter.LineHeight() = rSettings.DrawSettings()->SingleLineHeight();
    TracePainter.ColumnsSettings() = &rSettings.ColumnsSettings();

    TracePainter.Init();

    TracePainter.PrepareProcess();

    while ( TraceIterator.Valid() && !TracePainter.Done() )
    {
        TracePainter.LineNumber() = TraceIterator.getLineNumber();
        TracePainter.Process(TraceIterator.TraceData());

        ++ TraceIterator;
    }

    TraceIterator = m_TopPos;


    TracePainter.PrepareDrawing();

    m_TraceSectionsHilights.enumContent();

    while ( TraceIterator.Valid() && !TracePainter.Done() )
    {
        TracePainter.LineNumber() = TraceIterator.getLineNumber();
        TracePainter.PreDraw(TraceIterator.TraceData(), m_TraceSectionsHilights);

        ++ TraceIterator;
    }

    if ( !m_SelectionArea.isEmpty() )
    {
        QRect       rcArea = m_SelectionArea;
        rcArea.adjust( -ui->m_HorzScrollbar->value() + m_Margins.left(), 0, -ui->m_HorzScrollbar->value() + m_Margins.left(), 0 );
        QPen        pen(m_SelectionBorderBrush, 1.0);
        QPen        oldPen = painter.pen();

        painter.fillRect(rcArea, m_SelectionBrush);
        painter.setPen(pen);
        painter.drawRect(rcArea);
        painter.setPen(oldPen);
    }


    TraceIterator = m_TopPos;
    TracePainter.PrepareDrawing();

    while ( TraceIterator.Valid() && !TracePainter.Done() )
    {
        TracePainter.LineNumber() = TraceIterator.getLineNumber();
        TracePainter.Draw(TraceIterator.TraceData());

        ++ TraceIterator;
    }

    TracePainter.Release();


    if ( TracePainter.columnsWidthChanged() )
    {
        m_DisplayCache.Clear();
        update();
    }
}


void CTracesView::closeEvent(QCloseEvent* event)
{
    m_refViewCore->RemoveView(this);
	event->accept();
}


void CTracesView::UpdateScrollbarRange(const QRect& rcClient)
{
    CViewSettings&                          rSettings = ViewCore()->ViewSettings();
    int                                     NumberOfLines = 0;
    int                                     NumberOfDisplayedLines = NumberOfLinesVisibles();

    if ( m_pCurrentTracesGroup != NULL )
    {
        NumberOfLines = m_pCurrentTracesGroup->LinesCount();
    }

    int nScrollHeight = Nyx::Max( NumberOfLines - NumberOfDisplayedLines, 0 );
    int nScrollWidth = Nyx::Max((int)(rSettings.ColumnsSettings().GetTotalWidth()) - rcClient.width() + ui->m_VertScrollbar->width() + 20,  0);

    ui->m_VertScrollbar->setMaximum( nScrollHeight );
    ui->m_HorzScrollbar->setMaximum( nScrollWidth );

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
    if ( event->button() == Qt::LeftButton )
    {
        m_SelectionArea = QRect();
        m_SelectionArea.moveTo(event->pos().x() + ui->m_HorzScrollbar->value() - m_Margins.left(), event->pos().y());
    }

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


void CTracesView::mouseReleaseEvent(QMouseEvent *event)
{
    CViewTracePicker        picker(m_DisplayCache);

    CViewTracePicker::CPickerResult     pickResult = picker.pick(m_SelectionArea);

    pickResult.for_each( [&] (int y, int x, const CViewTracePicker::CPickerEntry& entry)
                        {
                            CViewTracePortal        tracePortal(*entry.traceData(), entry.lineNumber());
                            CTraceSectionId         id( entry.traceData()->identifier(), entry.columnId() );

                            m_TraceSectionsHilights.Set(id, new CViewTraceSectionHilight(*entry.traceData(), entry.columnId(), entry.subRect()) );

                            NYXTRACE(0x0, L"==> "
                                     << Nyx::CTF_AnsiText(tracePortal.GetColumnText(entry.columnId()).toStdString().c_str())
                                     << L" : top = "
                                     << Nyx::CTF_Int(y)
                                     << L" : left = "
                                     << Nyx::CTF_Int(x) );
                        } );

    m_SelectionArea = QRect();
    update();
}


void CTracesView::mouseMoveEvent(QMouseEvent *event)
{
    m_SelectionArea.setRight(event->pos().x() + ui->m_HorzScrollbar->value() - m_Margins.left());
    m_SelectionArea.setBottom(event->pos().y() );

    update();
}


/**
 *
 */
void CTracesView::wheelEvent(QWheelEvent* event)
{
    QPoint numPixels = event->pixelDelta();
//    int numDegrees = event->delta() / 8;
//    int numSteps = numDegrees / 15;

    int Vvalue = Nyx::Max(0, ui->m_VertScrollbar->value() - numPixels.y()/2);
    int Hvalue = Nyx::Max(0, ui->m_HorzScrollbar->value() - numPixels.x()/2);

//    int	value = Nyx::Max(0, ui->m_VertScrollbar->value() - (ui->m_VertScrollbar->singleStep()*numSteps));
    ui->m_VertScrollbar->setValue( Vvalue );
    ui->m_HorzScrollbar->setValue( Hvalue );
    m_DisplayCache.Clear();

    m_pHeader->update();
    update();
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

    m_SelectionBrush = QBrush(Settings().selectionColor());
    m_SelectionBorderBrush = QBrush(Settings().selectionBorderColor());

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
