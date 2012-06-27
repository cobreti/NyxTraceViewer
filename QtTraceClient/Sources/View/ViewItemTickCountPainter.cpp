#include "ViewItemTickCountPainter.hpp"
#include "ViewItemSettings.hpp"
#include "ViewItem.hpp"
#include "ViewSettings.hpp"
#include "ViewColumnsSettings.hpp"
#include "ViewColumnSettings.hpp"

#include "TimeStamp.hpp"

CViewItemPainterRef     CViewItemTickCountPainter::s_refPainter;


/**
 *
 */
CViewItemPainter* CViewItemTickCountPainter::Instance()
{
    if ( !s_refPainter.Valid() )
        s_refPainter = new CViewItemTickCountPainter();

    return s_refPainter;
}


/**
 *
 */
CViewItemTickCountPainter::CViewItemTickCountPainter() :
CViewItemTextPainter()
{
}


/**
 *
 */
CViewItemTickCountPainter::~CViewItemTickCountPainter()
{
}


/**
 *
 */
void CViewItemTickCountPainter::EvaluateSize(CViewSettings &settings, CViewItem &item)
{
    QString                     text = item.GetItemString( CViewItem::eII_TimeStamp );

    CViewItemTextPainter::EvaluateSize(settings, item, text);
}


/**
 *
 */
void CViewItemTickCountPainter::Display(const CViewSettings &settings, CDrawViewItemState &drawstate, CViewItem &item)
{
    if ( item.GetOwner() == &item )
    {
        CViewItemTextPainter::Display(settings, drawstate, item, item.GetItemString(CViewItem::eII_TimeStamp) );
    }
    else
    {
        const CViewColumnSettings&      rColSettings = settings.ColumnsSettings()[eVCI_TickCount];
        drawstate.TextPos().rx() += rColSettings.GetWidth();
    }
}


