#include "DynamicHighlight.h"

#include "../ViewTracePortal.h"
#include <QString>

CDynamicHighlight::CDynamicHighlight()
{

}


CDynamicHighlight::~CDynamicHighlight()
{

}


void CDynamicHighlight::Draw( CViewTracePainter::CPaintContext& context )
{
    QString     text = context.portal().GetColumnText(context.columnId());

    int index = text.indexOf("http");
    if ( index > -1 )
    {

        CViewTraceMetrics::CSubSection      section = context.metrics().GetSubTextRect( context.portal(),
                                                                                        context.columnId(),
                                                                                        context.area(),
                                                                                        index,
                                                                                        4);

        context.qpainter().fillRect(section.subRect(), Qt::green);
    }
}
