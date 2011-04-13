#include "ViewItemModuleNamePainter.hpp"
#include "ViewItem_TraceData.hpp"
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
    CViewItem_TraceData&                rItemData = static_cast<CViewItem_TraceData&>(item);
    TraceClientCore::CTracesPool*       pOwnerPool = rItemData.TraceData()->OwnerPool();
    QString                             text;

    if ( pOwnerPool )
        text = QString().fromWCharArray( pOwnerPool->Name().c_str() );
    else
        text = "unknown";

    CViewItemTextPainter::EvaluateSize(settings, item, text);
}


/**
 *
 */
void CViewItemModuleNamePainter::Display(const CViewSettings &settings, CDrawViewItemState &drawstate, CViewItem &item)
{
    CViewItem_TraceData&                rItemData = static_cast<CViewItem_TraceData&>(item);
    TraceClientCore::CTracesPool*       pOwnerPool = rItemData.TraceData()->OwnerPool();
    QString                             text;

    if ( pOwnerPool )
        text = QString().fromWCharArray( pOwnerPool->Name().c_str() );
    else
        text = "unknown";

    CViewItemTextPainter::Display(settings, drawstate, item, text);
}
