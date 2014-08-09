#ifndef VIEWTRACEOBJECT_H
#define VIEWTRACEOBJECT_H

#include "ViewObject.h"


class QPainter;
class QRectF;


namespace TraceClientCore
{
    class CTraceData;
}

class CViewTraceObject : public CViewObject
{
public:
    CViewTraceObject( TraceClientCore::CTraceData& rTraceData );
    CViewTraceObject( const CViewTraceObject& viewTraceObject );
    virtual ~CViewTraceObject();

    virtual void Draw( QPainter& rPainter, const QRectF& itemRect );

protected:

    TraceClientCore::CTraceData&    m_rTraceData;

};

#endif // VIEWTRACEOBJECT_H
