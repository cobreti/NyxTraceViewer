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
#include "View/Decorations/DynamicTextHighlight.h"
#include "View/Decorations/DynamicFocusedItemHighlight.hpp"
#include "View/TracesGroupViewMgr.h"


/**
 *
 */
CTracesView::CTracesView(QWidget* pParent, CTracesView* pBase) :
    QWidget(pParent),
    ui( new Ui::CTracesView() ),
    m_bViewDirty(false),
//    m_bKeepAtEnd(false),
    m_pHeader(NULL),
    m_pHighlightColorsPopup(NULL),
    m_pCurrentTracesGroup(NULL),
    m_bUpdatingScrollPos(false),
    m_pCurrentTracesGroupView(NULL)
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


CViewTracesIterator CTracesView::FirstPos() const
{
    return CViewTracesIterator::FirstPos(m_pCurrentTracesGroup);
}



CViewTracesIterator CTracesView::LastPos() const
{
    return CViewTracesIterator::LastPos(m_pCurrentTracesGroup);
}


void CTracesView::setKeepAtEnd(bool keepAtEnd)
{
    m_pCurrentTracesGroupView->KeepAtEnd() = keepAtEnd;

//    m_bKeepAtEnd = keepAtEnd;

    if ( m_pCurrentTracesGroupView->KeepAtEnd() )
    {
        MovePosToDisplayLastLine();
    }

    update();
}


/**
 * @brief CTracesView::MakeFocusedItemVisible
 */
void CTracesView::MakeFocusedItemVisible()
{
    Nyx::UInt32 numberOfVisibleLines = NumberOfLinesVisibles();
    Nyx::UInt32 lastVisibleLineNumber = m_TopPos.getLineNumber() + numberOfVisibleLines;

    if ( m_FocusedItem.Valid() && !(m_FocusedItem.getLineNumber() < lastVisibleLineNumber) )
    {
        int newTopLine = m_TopPos.getLineNumber() + m_FocusedItem.getLineNumber() - lastVisibleLineNumber + 2;
        ui->m_VertScrollbar->setValue(newTopLine);
        ui->m_VertScrollbar->update();
    }

    if ( m_FocusedItem.Valid() && m_FocusedItem.getLineNumber() < m_TopPos.getLineNumber() )
    {
        ui->m_VertScrollbar->setValue(m_FocusedItem.getLineNumber());
        ui->m_VertScrollbar->update();
    }
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

        if ( m_pCurrentTracesGroupView->KeepAtEnd() )
        {
            MovePosToDisplayLastLine();
        }

        update();

        int linesCount = pView->LinesCount();

//        NYXTRACE(0x0, L"traces view lines count : " << Nyx::CTF_Int(linesCount));
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


void CTracesView::Clear()
{
    if ( NULL != m_pCurrentTracesGroup )
    {
        m_pCurrentTracesGroup->Clear();
        m_DisplayCache.Clear();
        m_TopPos = CViewTracesIterator();
        update();
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
    if ( m_pCurrentTracesGroupView == NULL )
        return 1;

    int                         height = ViewRect().height();
    const CViewSettings&        rSettings = m_Settings;

    float                       visibleLines = (height - ui->m_HorzScrollbar->height()) / rSettings.DrawSettings()->SingleLineHeight();

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
    CTraceClientApp& rApp = CTraceClientApp::Instance();

    if ( m_pCurrentTracesGroupView != NULL )
    {
        m_pCurrentTracesGroupView->ColumnsSettings() = m_Settings.ColumnsSettings();
    }

    m_pCurrentTracesGroupView = rApp.TracesGroupViewMgr().Get(pGroup->Id());

    m_Settings.ColumnsSettings() = m_pCurrentTracesGroupView->ColumnsSettings();

    if ( m_pCurrentTracesGroupView->DynamicHilights().Get(CDynamicHighlight::kDefault) == NULL )
    {
        CDynamicHighlight*  pHighlight = new CDynamicTextHighlight();
        pHighlight->id() = CDynamicHighlight::kDefault;
        m_pCurrentTracesGroupView->DynamicHilights().Add(pHighlight);
    }

    if ( m_pCurrentTracesGroupView->DynamicHilights().Get(CDynamicHighlight::kFocusedItem) == NULL )
    {
        CDynamicFocusedItemHighlight*   pFocusedItemHighlight = new CDynamicFocusedItemHighlight(m_FocusedItem);
        pFocusedItemHighlight->id() = CDynamicHighlight::kFocusedItem;
        m_pCurrentTracesGroupView->DynamicHilights().Add(pFocusedItemHighlight);
    }

    m_TracesGroupNotificationsListener.ConnectTo(pGroup);
    m_pCurrentTracesGroup = pGroup;
    m_TopPos = CViewTracesIterator();

    ui->m_VertScrollbar->blockSignals(true);
    ui->m_HorzScrollbar->setValue(0);
    ui->m_VertScrollbar->setValue(0);
    UpdateScrollbarRange(ClientRect());
    m_DisplayCache.Clear();
    m_pHeader->AdjustColumnsSize();

    ui->m_VertScrollbar->blockSignals(false);

    update();
}


/**
 *
 */
void CTracesView::OnVertSliderPosChanged(int value)
{
    m_TopPos.MoveToLine(value);
    m_DisplayCache.Clear();

    if ( !updatingScrollPos() && m_pCurrentTracesGroupView->KeepAtEnd() )
    {
        m_pCurrentTracesGroupView->KeepAtEnd() = false;
        emit keepAtEndDisabled();
    }

    update();
}


void CTracesView::OnHorzSliderPosChanged(int value)
{
    m_pHeader->SetHorzOffset(value);
    m_DisplayCache.Clear();

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

    QBrush  bkgndBrush = palette().base();
    painter.fillRect(pEvent->rect(), bkgndBrush);

    painter.drawLine(m_Margins.left()-1, 0, m_Margins.left()-1, ViewHeight);

    if ( m_pCurrentTracesGroup == NULL )
        return;

    CViewSettings&                          rSettings = m_Settings;

    painter.setClipRect(m_Margins.left(), HeaderSize().height(), ClientRect().width(), ViewHeight);

    TracePainter.Origin() = QPoint( m_Margins.left() - ui->m_HorzScrollbar->value(), HeaderSize().height()+1);
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

    while ( TraceIterator.Valid() && !TracePainter.Done() )
    {
        TracePainter.LineNumber() = TraceIterator.getLineNumber();
        TracePainter.PreDraw(TraceIterator.TraceData(), m_pCurrentTracesGroupView->DynamicHilights());

        ++ TraceIterator;
    }


    m_pCurrentTracesGroupView->StaticHighlights().Draw(painter, m_DisplayCache);
    m_LiveStaticHighlights.Draw(painter, m_DisplayCache);


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
    if ( m_pCurrentTracesGroupView == NULL )
        return;

    CViewSettings&                          rSettings = m_Settings;
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

//    NYXTRACE(0x0, L"UpdateScrollBarRange : nScrollWidth = " << nScrollWidth );
//    NYXTRACE(0x0, L"UpdateScrollBarRange : hscrollbar value = " << ui->m_HorzScrollbar->value() << L" of " << nScrollWidth );

    m_DisplayCache.Clear();

    m_pHeader->SetHorzOffset(ui->m_HorzScrollbar->value());
    m_pHeader->update();
    update();
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

    m_LiveStaticHighlights.Clear();

}


void CTracesView::mouseReleaseEvent(QMouseEvent *event)
{
    CViewTracePicker        picker(m_DisplayCache);

    int scrollOffset = ui->m_HorzScrollbar->value();

    m_pCurrentTracesGroupView->StaticHighlights() += m_LiveStaticHighlights;

    m_SelectionArea = QRect();
    update();
}


void CTracesView::mouseMoveEvent(QMouseEvent *event)
{
    m_SelectionArea.setRight(event->pos().x() + ui->m_HorzScrollbar->value() - m_Margins.left());
    m_SelectionArea.setBottom(event->pos().y() );

    CViewTracePicker        picker(m_DisplayCache);

    int scrollOffset = ui->m_HorzScrollbar->value();

    QRect area = m_SelectionArea;

    if ( area.width() < 0 )
    {
        qreal left = area.left() + area.width() - 1;
        qreal right = area.left();

        area.setLeft(left);
        area.setRight(right);
    }

    area.adjust( m_Margins.left() - scrollOffset, 0, m_Margins.left() - scrollOffset, 0);

    m_LiveStaticHighlights.Clear();


    if ( area.width() > 0 )
    {
        if ( area.height() == 0 )
            area.setHeight(1);

        CViewTracePicker::CPickerResult     pickResult = picker.pick(area);

        pickResult.for_each( [&] (int y, int x, const CViewTracePicker::CPickerEntry& entry)
                            {
                                CViewTracePortal        tracePortal(*entry.traceData(), entry.lineNumber());
                                CTraceSectionId         id( entry.traceData()->identifier(), entry.columnId() );

                                m_LiveStaticHighlights.Set(id, new CViewTraceSectionHilight(*entry.traceData(), entry.columnId(), entry.subRect()) );
                            } );
    }

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

    m_Settings = CTraceClientApp::Instance().AppSettings().DefaultViewSettings();
    m_Settings.DrawSettings() = &CTraceClientApp::Instance().AppSettings().DefaultDrawSettings();

    if ( pBase )
    {
        m_refViewCore = pBase->ViewCore();

        ui->m_VertScrollbar->setValue( pBase->ui->m_VertScrollbar->value());
    }
    else
    {
        m_refViewCore = new CTracesViewCore();

        Settings().DrawSettings() = &CTraceClientApp::Instance().AppSettings().DefaultDrawSettings();
    }

    m_refHighlighters = new CViewItemHighlightersSet();

    m_pHeader = new CViewHeader( Settings().ColumnsSettings(), this );
//    m_pHeader->InitDefaultWidth();
    m_pHeader->Margins() = m_Margins;

    m_refViewCore->AddView(this);

    m_pLastSelectedBrush = CTraceClientApp::Instance().AppSettings().ViewHighlightSettings().LineHighlights()[0];

    m_pHighlightColorsPopup = new CHighlightColorsPopup();

    connect( ui->m_VertScrollbar, SIGNAL(sliderMoved(int)), this, SLOT(OnVertSliderPosChanged(int)));
    connect( ui->m_VertScrollbar, SIGNAL(valueChanged(int)), this, SLOT(OnVertSliderPosChanged(int)));
    connect( ui->m_HorzScrollbar, SIGNAL(sliderMoved(int)), this, SLOT(OnHorzSliderPosChanged(int)));
    connect( ui->m_HorzScrollbar, SIGNAL(valueChanged(int)), this, SLOT(OnHorzSliderPosChanged(int)));
    connect( &m_RefreshTimer, SIGNAL(timeout()), this, SLOT(RefreshDisplay()));

    m_RefreshTimer.start(250);

    m_SelectionBrush = QBrush(Settings().selectionColor());
    m_SelectionBorderBrush = QBrush(Settings().selectionBorderColor());

    m_FocusedItem.setColumnsOrder(Settings().ColumnsSettings().Order().OrderVector());

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


void CTracesView::MovePosToDisplayLastLine()
{
    Nyx::UInt32 lastLineNo = m_pCurrentTracesGroup->LinesCount() - 1;
    Nyx::UInt32 linesVisible = NumberOfLinesVisibles();

    int firstLineNo = Nyx::Max( int(lastLineNo - linesVisible), 0);

    if ( !m_TopPos.Valid())
    {
        m_TopPos = CViewTracesIterator::FirstPos(m_pCurrentTracesGroup);
    }

    m_TopPos.MoveToLine(firstLineNo);

    {
        XScrollPosUpdate        scrollPosUpdate(*this);
        ui->m_VertScrollbar->setValue(firstLineNo);
    }
}
