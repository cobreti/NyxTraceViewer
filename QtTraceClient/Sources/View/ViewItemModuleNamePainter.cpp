#include "ViewItemModuleNamePainter.hpp"
#include "ViewItem.hpp"
#include "ViewSettings.hpp"
#include "ViewColumnsSettings.hpp"
#include "ViewColumnSettings.hpp"
#include "TracesPool.hpp"


CViewItemPainterRef     CViewItemModuleNamePainter::s_refPainter;


/**
 *
 */
CViewItemPainter* CViewItemModuleNamePainter::Instance()
{
    if ( !s_refPainter.Valid() )
        s_refPainter = new CViewItemModuleNamePainter();

    return s_refPainter;
}


/**
 *
 */
CViewItemModuleNamePainter::CViewItemModuleNamePainter() :
CViewItemTextPainter()
{
}


/**
 *
 */
CViewItemModuleNamePainter::~CViewItemModuleNamePainter()
{
}


/**
 *
 */
void CViewItemModuleNamePainter::EvaluateSize(CViewSettings &settings, CViewItem &item)
{
    CViewItemTextPainter::EvaluateSize(settings, item, item.GetItemString(CViewItem::eII_Module) );
}


/**
 *
 */
void CViewItemModuleNamePainter::Display(const CViewSettings &settings, CDrawViewItemState &drawstate, CViewItem &item)
{
    if ( item.GetOwner() == &item )
    {
        CViewItemTextPainter::Display(settings, drawstate, item, item.GetItemString(CViewItem::eII_Module) );
    }
    else
    {
        const CViewColumnSettings&      rColSettings = settings.ColumnsSettings()[eVCI_ModuleName];
        drawstate.TextPos().rx() += rColSettings.GetWidth();
    }
}
