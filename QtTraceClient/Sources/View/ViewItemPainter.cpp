#include "ViewItemPainter.hpp"


/**
 *
 */
EViewColumnId CViewItemPainter::PainterId2ColumnId( CViewItemPainter::EPainterId id )
{
    switch (id)
    {
    case ePId_ModuleName:
        return eVCI_ModuleName;
    case ePId_TickCount:
        return eVCI_TickCount;
    case ePId_ThreadId:
        return eVCI_ThreadId;
    case ePId_Data:
        return eVCI_Data;
    case ePId_LineNumber:
        return eVCI_LineNumber;
    };

    return (EViewColumnId)-1;
}


/**
 *
 */
CViewItemPainter::~CViewItemPainter()
{
}


/**
 *
 */
void CViewItemPainter::EvaluateSize(CViewSettings&, CViewItem& )
{
}


/**
 *
 */
void CViewItemPainter::Display(const CViewSettings&, CDrawViewItemState&, CViewItem&)
{
}


/**
 *
 */
void CViewItemPainter::SetFont( const QFont& font )
{
    m_Font = font;
    m_MaxFontHeight = QFontMetricsF(m_Font).xHeight() * 1.5;
}


/**
 *
 */
CViewItemPainter::CViewItemPainter() :
    m_MaxFontHeight(0)
{
    m_MaxFontHeight = QFontMetricsF(m_Font).xHeight() * 1.5;
}
