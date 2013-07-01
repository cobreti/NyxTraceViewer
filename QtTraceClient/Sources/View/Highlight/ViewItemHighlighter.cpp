#include "View/Highlight/ViewItemHighlighter.hpp"
#include "View/DrawViewItemState.hpp"
#include "View/ViewColumnSettings.hpp"

#include <QtGui>

/**
 *
 */
CViewItemHighlighter::CViewItemHighlighter() :
    m_HighlightColor(Qt::yellow)
{
}


/**
 *
 */
void CViewItemHighlighter::OnPreItemDisplay(    const CViewSettings& rViewSettings,
                                                const CViewColumnSettings& rColumnSettings,
                                                CDrawViewItemState& rState,
                                                QFontMetricsF& rMetrics,
                                                const QString& text )
{
    if ( !m_refPattern.Valid() )
        return;

    long                startIndex = 0;
    int                 patternLength = m_refPattern->PatternLength();

    Nyx::CRange         range = m_refPattern->Match(text, startIndex);

    while ( !range.IsEmpty() )
    {
        long                textOffset = startIndex + range.Start();
        QPainter&           rPainter = rState.Painter();
        QBrush              brush(m_HighlightColor);
        QRectF              rcTextSelection = rMetrics.boundingRect( text.mid(range.Start(), range.Length()) );
        QRectF              rcTextWithSel = rMetrics.boundingRect( text.left(range.Start() + range.Length()) );
        QRectF              rcText = rMetrics.boundingRect( text );
        float               fStartPos = rcTextWithSel.width() - rcTextSelection.width();
        QRectF              rcArea( rState.TextPos().x() + rColumnSettings.Margins().left() + fStartPos + 1, 
                                    rState.TextPos().y() + rColumnSettings.Margins().top() + 1,
                                    rcTextSelection.width() - 1, 
                                    rcText.height() - rColumnSettings.Margins().height() - 1 );

        rPainter.fillRect(rcArea, brush);

        startIndex = textOffset + patternLength;
        range = m_refPattern->Match(text, startIndex);
    }
}


/**
 *
 */
void CViewItemHighlighter::OnPostItemDisplay(   const CViewSettings& rViewSettings,
                                                const CViewColumnSettings& rColumnSettings,
                                                CDrawViewItemState& rState,
                                                QFontMetricsF& rMetrics,
                                                const QString& text )
{
}


/**
 *
 */
CViewItemHighlighter::~CViewItemHighlighter()
{
}
