#include "ViewTraceObject.h"


CViewTraceObject::CViewTraceObject(TraceClientCore::CTraceData &rTraceData) : CViewObject(),
    m_rTraceData(rTraceData)
{

}


CViewTraceObject::CViewTraceObject(const CViewTraceObject &viewTraceObject) : CViewObject(),
    m_rTraceData(viewTraceObject.m_rTraceData)
{
}


CViewTraceObject::~CViewTraceObject()
{

}


void CViewTraceObject::Draw( QPainter& rPainter, const QRectF& itemRect )
{

}
