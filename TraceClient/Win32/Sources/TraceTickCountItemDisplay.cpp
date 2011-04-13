#include "TraceTickCountItemDisplay.hpp"
#include "UITraceData.hpp"
#include "TracesViewColumnSettings.hpp"


/**
 *
 */
CTraceTickCountItemDisplay::CTraceTickCountItemDisplay() :
CTraceItemDisplay()
{
}


/**
 *
 */
CTraceTickCountItemDisplay::~CTraceTickCountItemDisplay()
{
}


/**
 *
 */
SizeF CTraceTickCountItemDisplay::Display(	CUITraceData& trace,
											CTracesViewColumnSettings% settings,
											PointF% pos,
											Graphics^ graph )
{
	SizeF		Size = Display( gcnew System::String(trace.TickCount()), settings, pos, graph );

	//graph->DrawRectangle( Pens::BlueViolet, m_rcDrawnText.Left, m_rcDrawnText.Top, m_rcDrawnText.Width, m_rcDrawnText.Height );
	//graph->DrawRectangle( Pens::DarkOrange, m_rcDrawnArea.Left, m_rcDrawnArea.Top, m_rcDrawnArea.Width, m_rcDrawnArea.Height );

	return Size;
}
