#ifndef _TRACEITEMDISPLAY_HPP_
#define _TRACEITEMDISPLAY_HPP_


class CUITraceData;
ref class CTracesViewColumnSettings;

using namespace System::Drawing;


/**
 *
 */
public ref class CTraceItemDisplay
{
public: // public methods
	CTraceItemDisplay();
	virtual ~CTraceItemDisplay();

	virtual SizeF Display(	CUITraceData& trace,
							CTracesViewColumnSettings% settings,
							PointF% pos,
							Graphics^ graph );

	virtual SizeF CalcItemSize( CTracesViewColumnSettings% settings,
								Graphics^ graph );

protected: // protected methods

	virtual SizeF Display(	System::String^ text,
							CTracesViewColumnSettings% settings,
							PointF% pos,
							Graphics^ graph );

protected: // protected members

	RectangleF		m_rcDrawnText;	// rectangle containing the text actually drawn
	RectangleF		m_rcDrawnArea;	// rectangle containing the whole area actually drawn: text + margins
};


#endif // _TRACEITEMDISPLAY_HPP_
