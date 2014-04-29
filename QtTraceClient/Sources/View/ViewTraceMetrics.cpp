#include "ViewTraceMetrics.h"
#include "ViewTracePortal.h"
#include "ViewTracesDisplayCache.h"

#include <QFontMetricsF>
#include <algorithm>


CViewTraceMetrics::CViewTraceMetrics()
{

}



CViewTraceMetrics::~CViewTraceMetrics()
{

}


void CViewTraceMetrics::CalcTraceSize(const CViewTracePortal& tracePortal, const ColumnsIdVector& columnsIds, CViewTracesDisplayCache& displayCache)
{
    auto    fct = [&] (EViewColumnId id)
            {
                this->CalcColumnSize(id, tracePortal, displayCache);
            };


    std::for_each( columnsIds.begin(), columnsIds.end(), fct );
}


void CViewTraceMetrics::CalcColumnSize(EViewColumnId columnId, const CViewTracePortal& tracePortal, CViewTracesDisplayCache& displayCache)
{
    CTraceSectionId       entryId(tracePortal.traceData()->identifier(), columnId);

    if ( displayCache.hasEntry(entryId) )
        return;

    QFontMetricsF                           metrics(m_Font);
    QString                                 text = tracePortal.GetColumnText(columnId);
    QRectF                                  rcText = metrics.boundingRect(text);

    rcText.adjust(0, 0, 0.5, 0.5);

    m_ColumnsRect[columnId] = rcText;
}


const CViewTraceMetrics::CSubSection CViewTraceMetrics::GetTextInRect( const CViewTracePortal& tracePortal, EViewColumnId columnId, const QRectF& itemArea, const QRectF& rcArea )
{
    QString         text;
    QString         srcText = tracePortal.GetColumnText(columnId);
    QFontMetricsF   metrics(m_Font);
    QRectF          rcText;
    QRectF          adjustedItemArea = itemArea;
    qreal           threshold = metrics.averageCharWidth() / 2;
    QRectF          adjustedArea = rcArea;
    qreal           offset = 0;
    int             startPos = 1;
    int             len = srcText.length();
    CSubSection     subSection;

    adjustedItemArea.adjust( -itemArea.left(), 0, -itemArea.left(), 0 );
    adjustedArea.adjust( -itemArea.left(), 0, -itemArea.left(), 0 );

    rcText = metrics.boundingRect(srcText.mid(0, startPos));

    while ( rcText.right() < adjustedArea.left() && startPos <= len )
    {
        ++ startPos;
        rcText = metrics.boundingRect(srcText.mid(0, startPos));
    }

    startPos --;
    rcText = metrics.boundingRect(srcText.mid(0, startPos));
    offset = rcText.right();

    subSection.startIndex() = startPos;
    subSection.subRect().setTop(rcText.top());
    subSection.subRect().setLeft( rcText.right() );

    rcText = metrics.boundingRect(srcText.mid(startPos, len));
    rcText.adjust(offset, 0, offset, 0);

    while ( rcText.right() - threshold > adjustedArea.right() && len > 0 )
    {
        -- len;
        rcText = metrics.boundingRect(srcText.mid(startPos, len));
        rcText.adjust(offset, 0, offset, 0);
    }

    subSection.length() = len;
    subSection.subRect().setRight(rcText.right());
    subSection.subRect().setBottom(rcText.bottom());
    subSection.text() = srcText.mid(startPos, len);

    return subSection;
}


const CViewTraceMetrics::CSubSection CViewTraceMetrics::GetSubTextRect( const CViewTracePortal& tracePortal, EViewColumnId columnId, const QRectF& itemArea, int startIndex, int len )
{
    QString         srcText = tracePortal.GetColumnText(columnId);
    QFontMetrics    metrics(m_Font);
    QRectF          rcText;
    CSubSection     subSection;
    qreal           left = 0;
    qreal           width = itemArea.width();

    if ( startIndex > 0 )
    {
        left = metrics.width(srcText, startIndex);
//        left = rcText.right();
    }

    if ( startIndex + len <= srcText.length() )
    {
        width = metrics.width(srcText, startIndex+len) - left;
//        width = rcText.right() - left;
    }

    subSection.startIndex() = startIndex;
    subSection.length() = len;
    subSection.text() = srcText.mid(startIndex, len);
    subSection.subRect() = QRectF(  left + itemArea.left(),
                                    itemArea.top(),
                                    width,
                                    itemArea.height());

    return subSection;
}


CViewTraceMetrics::CSubSection::CSubSection() :
    m_StartIndex(-1),
    m_Length(0),
    m_SubRect(QRectF())
{

}


CViewTraceMetrics::CSubSection::CSubSection(const CSubSection &section) :
    m_Text(section.m_Text),
    m_StartIndex(section.m_StartIndex),
    m_Length(section.m_Length),
    m_SubRect(section.m_SubRect)
{

}


CViewTraceMetrics::CSubSection::~CSubSection()
{

}


const CViewTraceMetrics::CSubSection& CViewTraceMetrics::CSubSection::operator = (const CSubSection& section)
{
    m_Text = section.m_Text;
    m_StartIndex = section.m_StartIndex;
    m_Length = section.m_Length;
    m_SubRect = section.m_SubRect;

    return *this;
}
