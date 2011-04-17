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
    const CViewItemSettings*    pSetting = settings.ViewItemsSettings()[Id()];
    CViewColumnSettings&        rColSettings = settings.ColumnsSettings()[ CViewItemPainter::PainterId2ColumnId(Id()) ];
    QStringList                 TextLines = text.split('\n');
    QSizeF                      size;
    QFont*                      pFont = pSetting->GetFont();
    QFontMetricsF               metrics(*pFont);
    QRectF                      rcText = CalculateTextRect(metrics, TextLines);

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
void CViewItemTextPainter::Display(const CViewSettings &settings, CDrawViewItemState &drawstate, CViewItem&, const QString &text)
{
    const CViewItemSettings*        pSetting = settings.ViewItemsSettings()[Id()];
    const CViewColumnSettings&      rColSettings = settings.ColumnsSettings()[ CViewItemPainter::PainterId2ColumnId(Id()) ];
    QFont*                          pFont = pSetting->GetFont();
    QFontMetricsF                   metrics(*pFont);
    QRectF                          rcText;
    QRectF                          rcDrawTextArea;
    QRectF                          rcSubText;
    QStringList                     TextLines = text.split('\n');
    QStringList::const_iterator     pos;

    rcText = CalculateTextRect(metrics, TextLines);

    rcDrawTextArea = QRectF(    drawstate.TextPos().x() + rColSettings.Margins().left(), 
                                drawstate.TextPos().y() + rColSettings.Margins().top(),
                                rColSettings.GetWidth() - rColSettings.Margins().width(),
                                rcText.height() - rColSettings.Margins().height() );


    pos = TextLines.begin();
    while ( pos != TextLines.end() )
    {
        rcSubText = metrics.boundingRect( *pos);
        drawstate.Painter().drawText(rcDrawTextArea, Qt::AlignLeft, *pos);

        rcDrawTextArea.setTop( rcDrawTextArea.top() + rcSubText.height());

        ++pos;
    }


    drawstate.TextPos().rx() += rColSettings.GetWidth();
}


/**
 *
 */
QRectF CViewItemTextPainter::CalculateTextRect( QFontMetricsF& Metrics, const QStringList& Lines )
{
    QRectF                          rcText;
    QRectF                          rcSubText;
    QStringList::const_iterator     pos = Lines.begin();

    while ( pos != Lines.end() )
    {
        rcSubText = Metrics.boundingRect(*pos);
        rcText = QRectF(    Nyx::Min(rcText.left(), rcSubText.left()),
                            Nyx::Min(rcText.top(), rcSubText.top()),
                            Nyx::Max(rcText.width(), rcSubText.width()),
                            rcText.height() + rcSubText.height());

        ++pos;
    }

    return rcText;
}
