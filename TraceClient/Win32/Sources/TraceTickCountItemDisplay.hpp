#ifndef _TRACETICKCOUNTITEMDISPLAY_HPP_
#define _TRACETICKCOUNTITEMDISPLAY_HPP_

#include "TraceItemDisplay.hpp"


/**
 *
 */
public ref class CTraceTickCountItemDisplay : public CTraceItemDisplay
{
public:
	CTraceTickCountItemDisplay();
	virtual ~CTraceTickCountItemDisplay();

	virtual SizeF Display(	CUITraceData& trace,
							CTracesViewColumnSettings% settings,
							PointF% pos,
							Graphics^ graph ) override;
};

#endif // _TRACETICKCOUNTITEMDISPLAY_HPP_
