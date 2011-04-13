#ifndef _VIEWITEMROWPAINTER_H_
#define _VIEWITEMROWPAINTER_H_

#include "ViewItemPainter.hpp"


/**
 *
 */
class CViewItemRowPainter : public CViewItemPainter
{
public:
	CViewItemRowPainter();
	virtual ~CViewItemRowPainter();

	virtual EPainterId Id() const { return ePId_Row; }
};


#endif // _VIEWITEMROWPAINTER_H_
