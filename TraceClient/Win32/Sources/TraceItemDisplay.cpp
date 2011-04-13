#include "UITraceData.hpp"
#include "TraceItemDisplay.hpp"
#include "TracesViewColumnSettings.hpp"

/**
 *
 */
CTraceItemDisplay::CTraceItemDisplay()
{
}


/**
 *
 */
CTraceItemDisplay::~CTraceItemDisplay()
{
}


/**
 *
 */
SizeF CTraceItemDisplay::Display(	CUITraceData& trace,
									CTracesViewColumnSettings% settings,
									PointF% pos,
									Graphics^ graph )
{
	return SizeF(0.0f, 0.0f);
}


/**
 *
 */
SizeF CTraceItemDisplay::CalcItemSize(	CTracesViewColumnSettings% settings,
										Graphics^ graph )
{
	SizeF		size(0.0f, 0.0f);

	size = graph->MeasureString( gcnew System::String(L"|"), settings.Font );
	size.Width += settings.Margins.Left + settings.Margins.Right;
	size.Height += settings.Margins.Top + settings.Margins.Bottom;

	return size;
}


/**
 *
 */
SizeF CTraceItemDisplay::Display(	System::String^ text,
									CTracesViewColumnSettings% settings,
									PointF% pos,
									Graphics^ graph )
{
	SizeF				TextSize;
	Drawing::Color		TextColor = Drawing::Color::FromArgb(0, 0, 0);
	Drawing::Brush^		TextBrush = gcnew Drawing::SolidBrush(TextColor);
	
	TextSize = graph->MeasureString( text, settings.Font );

	if ( settings.Width != -1 )
		TextSize.Width = settings.Width;

	m_rcDrawnText = RectangleF(	pos.X + settings.Margins.Left,
								pos.Y + settings.Margins.Top,
								TextSize.Width,
								TextSize.Height );
	m_rcDrawnArea = RectangleF( pos.X, 
								pos.Y, 
								TextSize.Width + settings.Margins.Left + settings.Margins.Right,
								TextSize.Height + settings.Margins.Top + settings.Margins.Bottom );

	graph->DrawString(text, settings.Font, TextBrush, m_rcDrawnText );

	return m_rcDrawnArea.Size;
}


