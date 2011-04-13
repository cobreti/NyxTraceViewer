#ifndef _TRACETHREADIDITEMDISPLAY_HPP_
#define _TRACETHREADIDITEMDISPLAY_HPP_

#include "TraceItemDisplay.hpp"


/**
 *
 */
public ref class CTraceThreadIdItemDisplay : public CTraceItemDisplay
{
public:
	CTraceThreadIdItemDisplay();
	virtual ~CTraceThreadIdItemDisplay();

	virtual SizeF Display(	CUITraceData& trace,
							CTracesViewColumnSettings% settings,
							PointF% pos,
							Graphics^ graph ) override;
};


#endif // _TRACETHREADIDITEMDISPLAY_HPP_
