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
void CViewItemPainter::EvaluateSize(CViewSettings& settings, CViewItem &item)
{
}


/**
 *
 */
void CViewItemPainter::Display(const CViewSettings& settings, CDrawViewItemState &drawstate, CViewItem &item)
{
}


/**
 *
 */
CViewItemPainter::CViewItemPainter()
{
}
