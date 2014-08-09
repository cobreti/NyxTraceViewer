#include "DynamicTextHighlight.h"

#include "../ViewTracePortal.h"
#include "TraceData.hpp"

CDynamicTextHighlight::CDynamicTextHighlight() : CDynamicHighlight(),
    m_Color(Qt::yellow)
{

}


CDynamicTextHighlight::~CDynamicTextHighlight()
{

}


void CDynamicTextHighlight::Draw( CViewTracePainter::CPaintContext& context )
{
    if ( m_Text.isEmpty() )
        return;

    if ( context.portal().traceData()->Type() != TraceClientCore::CTraceData::eTT_User )
        return;

    QString     text = context.portal().GetColumnText(context.columnId());

    int index = text.indexOf(m_Text);
    while ( index > -1 )
    {

        CViewTraceMetrics::CSubSection      section = context.metrics().GetSubTextRect( context.portal(),
                                                                                        context.columnId(),
                                                                                        context.area(),
                                                                                        index,
                                                                                        m_Text.length() );

        context.qpainter().fillRect(section.subRect(), m_Color);

        index = text.indexOf(m_Text, index+1);
    }
}

