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

    QSizeF                      size;
    QFont*                      pFont = pSetting->GetFont();
    QFontMetricsF               metrics(*pFont);
    QRectF                      rcText = metrics.boundingRect(text);

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
void CViewItemTextPainter::Display(const CViewSettings &settings, CDrawViewItemState &drawstate, CViewItem &item, const QString &text)
{
    const CViewItemSettings*    pSetting = settings.ViewItemsSettings()[Id()];
    const CViewColumnSettings&  rColSettings = settings.ColumnsSettings()[ CViewItemPainter::PainterId2ColumnId(Id()) ];
    QFont*                      pFont = pSetting->GetFont();
    QFontMetricsF               metrics(*pFont);
    QRectF                      rcText = metrics.boundingRect(text);
    QRectF                      rcDrawTextArea( drawstate.TextPos().x() + rColSettings.Margins().left(),
                                                drawstate.TextPos().y() + rColSettings.Margins().top(),
                                                rColSettings.GetWidth() - rColSettings.Margins().width(),
                                                rcText.height() - rColSettings.Margins().height() );

    drawstate.Painter().setFont(*pFont);
    drawstate.Painter().drawText(rcDrawTextArea, Qt::AlignLeft, text);

    drawstate.TextPos().rx() += rColSettings.GetWidth();
}


