#include "ViewItemTextPainter.hpp"
#include "ViewSettings.hpp"
#include "ViewItem.hpp"
#include "ViewColumnsSettings.hpp"
#include "ViewColumnSettings.hpp"


/**
 *
 */
CViewItemTextPainter::CViewItemTextPainter()
{
}


/**
 *
 */
CViewItemTextPainter::~CViewItemTextPainter()
{
}


/**
 *
 */
void CViewItemTextPainter::EvaluateSize(CViewSettings &settings, CViewItem &item, const QString &text)
{
    const qreal                 safeTextMargins = 5.0;
    CViewColumnSettings&        rColSettings = settings.ColumnsSettings()[ CViewItemPainter::PainterId2ColumnId(Id()) ];
    QStringList                 TextLines = text.split('\n');
    QSizeF                      size;
    QFontMetricsF               metrics(Font());
    QRectF                      rcText = CalculateTextRect(settings, metrics, TextLines);

    size = QSizeF(rcText.width() + safeTextMargins, rcText.height());

    size.rwidth() += rColSettings.Margins().width();
    size.rheight() += rColSettings.Margins().height();

    if ( rColSettings.AutoWidth() && size.width() > rColSettings.GetWidth() )
        rColSettings.SetWidth( size.width() );

    item.AddSize(size);
}


/**
 *
 */
void CViewItemTextPainter::Display(const CViewSettings &settings, CDrawViewItemState &drawstate, CViewItem& item, const QString &text)
{
    const CViewColumnSettings&      rColSettings = settings.ColumnsSettings()[ CViewItemPainter::PainterId2ColumnId(Id()) ];
    QFontMetricsF                   metrics(Font());
    QRectF                          rcText;
    QRectF                          rcDrawTextArea;
    QRectF                          rcSubText;
    QStringList                     TextLines = text.split('\n');
    QStringList::const_iterator     pos;
    float                           lineHeight = settings.DrawSettings()->SingleLineHeight();

    rcText = CalculateTextRect(settings, metrics, TextLines);

    rcDrawTextArea = QRectF(    drawstate.TextPos().x() + rColSettings.Margins().left(), 
                                drawstate.TextPos().y() + rColSettings.Margins().top(),
                                rColSettings.GetWidth() - rColSettings.Margins().width(),
                                rcText.height() - rColSettings.Margins().height() );

    pos = TextLines.begin();
    while ( pos != TextLines.end() )
    {
        rcSubText = metrics.boundingRect( *pos);
        rcSubText.setHeight( lineHeight );
        drawstate.Painter().setFont( Font() );
        drawstate.Painter().drawText(rcDrawTextArea, Qt::AlignLeft, *pos);

        rcDrawTextArea.setTop( rcDrawTextArea.top() + rcSubText.height());

        ++pos;
    }

    drawstate.TextPos().rx() += rColSettings.GetWidth();
}


/**
 *
 */
QRectF CViewItemTextPainter::CalculateTextRect( const CViewSettings& settings, QFontMetricsF& Metrics, const QStringList& Lines )
{
    QRectF                          rcText;
    QRectF                          rcSubText;
    QStringList::const_iterator     pos = Lines.begin();

    while ( pos != Lines.end() )
    {
        rcSubText = Metrics.boundingRect(*pos);

        rcSubText.setHeight( settings.DrawSettings()->SingleLineHeight());

        rcText = QRectF(    Nyx::Min(rcText.left(), rcSubText.left()),
                            Nyx::Min(rcText.top(), rcSubText.top()),
                            Nyx::Max(rcText.width(), rcSubText.width()),
                            rcText.height() + rcSubText.height());

        ++pos;
    }

    return rcText;
}
