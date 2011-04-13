#ifndef _TRACEDATAITEMDISPLAY_HPP_
#define _TRACEDATAITEMDISPLAY_HPP_

#include "TraceItemDisplay.hpp"


/**
 *
 */
public ref class CTraceDataItemDisplay : public CTraceItemDisplay
{
public:
	CTraceDataItemDisplay();
	virtual ~CTraceDataItemDisplay();

	virtual SizeF Display(	CUITraceData& trace,
							CTracesViewColumnSettings% settings,
							PointF% pos,
							Graphics^ graph ) override;
};

#endif // _TRACEDATAITEMDISPLAY_HPP_
