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

    if ( m_pSearchEngine->FoundPos().LineNumber() == rState.LineNumber() )
    {
        QPainter&           rPainter = rState.Painter();
        QRectF              rcText = rMetrics.boundingRect(text);
        QRectF              rcArea( rState.TextPos().x() + rColumnSettings.Margins().left(), 
                                    rState.TextPos().y() + rColumnSettings.Margins().top(),
                                    rcText.width(), 
                                    rcText.height() - rColumnSettings.Margins().height() );

        rPainter.drawRect(rcArea);
    }

    //if ( !m_refPattern.Valid() )
    //    return;

    //long                startIndex = 0;

    //Nyx::CRange         range = m_refPattern->Match(text, startIndex);

    //while ( !range.IsEmpty() )
    //{
    //    long                textOffset = startIndex + range.Start();
    //    QPainter&           rPainter = rState.Painter();
    //    QBrush              brush(Qt::GlobalColor::yellow);
    //    QRectF              rcTextSelection = rMetrics.boundingRect( text.mid(range.Start(), range.Length()) );
    //    QRectF              rcTextWithSel = rMetrics.boundingRect( text.left(range.Start() + range.Length()) );
    //    QRectF              rcText = rMetrics.boundingRect( text );
    //    float               fStartPos = rcTextWithSel.width() - rcTextSelection.width();
    //    QRectF              rcArea( rState.TextPos().x() + rColumnSettings.Margins().left() + fStartPos, 
    //                                rState.TextPos().y() + rColumnSettings.Margins().top(),
    //                                rcTextSelection.width(), 
    //                                rcText.height() - rColumnSettings.Margins().height() );

    //    rPainter.fillRect(rcArea, brush);

    //    startIndex = textOffset + 1;
    //    range = m_refPattern->Match(text, startIndex);
    //}
}
