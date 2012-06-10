#include "View/Highlight/ViewItemHighlighter.hpp"
#include "View/DrawViewItemState.hpp"
#include "View/ViewColumnSettings.hpp"

#include <QtGui>

/**
 *
 */
CViewItemHighlighter::CViewItemHighlighter()
{
}


void CViewItemHighlighter::OnPreItemDisplay(    const CViewSettings& rViewSettings,
                                                const CViewColumnSettings& rColumnSettings,
                                                CDrawViewItemState& rState,
                                                QFontMetricsF& rMetrics,
                                                const QString& text )
{
    if ( !m_refPattern.Valid() )
        return;

    Nyx::CRange         range = m_refPattern->Match(text);

    if ( range.IsEmpty() )
        return;

    QPainter&           rPainter = rState.Painter();
    QBrush              brush(Qt::GlobalColor::yellow);
    QRectF              rcTextBefore = rMetrics.boundingRect( text.left(range.Start()) );
    QRectF              rcTextSelection = rMetrics.boundingRect( text.mid(range.Start(), range.Length()) );
    QRectF              rcTextWithSel = rMetrics.boundingRect( text.left(range.Start() + range.Length()) );
    QRectF              rcText = rMetrics.boundingRect( text );
    float               fStartPos = rcTextWithSel.width() - rcTextSelection.width();
    QRectF              rcArea( rState.TextPos().x() + rColumnSettings.Margins().left() + fStartPos, 
                                rState.TextPos().y() + rColumnSettings.Margins().top(),
                                rcTextSelection.width(), 
                                rcText.height() - rColumnSettings.Margins().height() );

    rPainter.fillRect(rcArea, brush);
}


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
