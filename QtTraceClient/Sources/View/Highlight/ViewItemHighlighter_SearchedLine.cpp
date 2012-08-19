#include "View/Highlight/ViewItemHighlighter_SearchedLine.hpp"
#include "View/ViewSearchEngine.h"
#include "View/DrawViewItemState.hpp"
#include "View/ViewColumnSettings.hpp"


/**
 *
 */
CViewItemHighlighter_SearchedLine::CViewItemHighlighter_SearchedLine( CViewSearchEngine* pSearchEngine ) :
    m_pSearchEngine(pSearchEngine)
{
}


/**
 *
 */
CViewItemHighlighter_SearchedLine::~CViewItemHighlighter_SearchedLine()
{
}


/**
 *
 */
void CViewItemHighlighter_SearchedLine::OnPreItemDisplay(   const CViewSettings& rViewSettings,
                                                            const CViewColumnSettings& rColumnSettings,
                                                            CDrawViewItemState& rState,
                                                            QFontMetricsF& rMetrics,
                                                            const QString& text )
{
    if ( !m_pSearchEngine->FoundPos() )
        return;

    if ( m_pSearchEngine->FoundPos().ItemNumber() == rState.ItemNumber() )
    {
        QPainter&           rPainter = rState.Painter();
        QRectF              rcText = rMetrics.boundingRect(text);
        QRectF              rcArea( rState.TextPos().x() + rColumnSettings.Margins().left(), 
                                    rState.TextPos().y() + rColumnSettings.Margins().top(),
                                    rcText.width(), 
                                    rcText.height() - rColumnSettings.Margins().height() );

        rPainter.drawRect(rcArea);
    }
}
