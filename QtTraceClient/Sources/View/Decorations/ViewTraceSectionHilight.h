#ifndef VIEWTRACESECTIONHILIGHT_H
#define VIEWTRACESECTIONHILIGHT_H

#include "ViewTraceObject.h"
#include "../ViewColumnId.hpp"

#include <QRectF>
#include <Nyx.hpp>



class CViewTraceSectionHilight : public CViewTraceObject
{
public:
    CViewTraceSectionHilight(TraceClientCore::CTraceData& rTraceData, const EViewColumnId& columnId, const QRectF& rcHilight);
    virtual ~CViewTraceSectionHilight();

    const QRectF&               hilightRect() const         { return m_rcHilight; }
    QRectF&                     hilightRect()               { return m_rcHilight; }

    virtual void Draw(QPainter &rPainter, const QRectF &itemRect);

protected:

    EViewColumnId       m_ColumnId;
    QRectF              m_rcHilight;
};


DECLARE_OBJECTREF(CViewTraceSectionHilight)


#endif // VIEWTRACESECTIONHILIGHT_H
