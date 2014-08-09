#include "DynamicFocusedItemHighlight.hpp"
#include "../ViewTracesContentIterator.hpp"
#include "../ViewTracePortal.h"


CDynamicFocusedItemHighlight::CDynamicFocusedItemHighlight(CViewTracesContentIterator &rFocusedItem) : CDynamicHighlight(),
    m_rFocusedItem(rFocusedItem)
{

}


CDynamicFocusedItemHighlight::~CDynamicFocusedItemHighlight()
{

}


void CDynamicFocusedItemHighlight::Draw( CViewTracePainter::CPaintContext& context )
{
    if ( !m_rFocusedItem.Valid() )
        return;

    if ( !(m_rFocusedItem.getLineNumber() == context.portal().lineNumber() && m_rFocusedItem.columnId() == context.columnId()) )
        return;

    QString     text = context.portal().GetColumnText(context.columnId());

    CViewTraceMetrics::CSubSection section = context.metrics().GetSubTextRect(  context.portal(),
                                                                                context.columnId(),
                                                                                context.area(),
                                                                                m_rFocusedItem.textIndex(),
                                                                                m_rFocusedItem.text().length() );

    context.qpainter().drawRect(section.subRect());
}
