#include "ViewItemDataPainter.hpp"
#include "ViewItem_TraceData.hpp"
#include "ViewItemSettings.hpp"


CViewItemPainterRef     CViewItemDataPainter::s_refPainter;


/**
 *
 */
CViewItemPainter* CViewItemDataPainter::Instance()
{
    if ( !s_refPainter.Valid() )
        s_refPainter = new CViewItemDataPainter();

    return s_refPainter;
}


/**
 *
 */
CViewItemDataPainter::CViewItemDataPainter() :
CViewItemTextPainter()
{
}


/**
 *
 */
CViewItemDataPainter::~CViewItemDataPainter()
{
}


/**
 *
 */
void CViewItemDataPainter::EvaluateSize(CViewSettings &settings, CViewItem &item)
{
    CViewItem_TraceData&        rItemData = static_cast<CViewItem_TraceData&>(item);
    QString                     text = QString().fromWCharArray(rItemData.TraceData()->Data().c_str());

    CViewItemTextPainter::EvaluateSize(settings, item, text);
}


/**
 *
 */
void CViewItemDataPainter::Display( const CViewSettings &settings,
                                            CDrawViewItemState &drawstate,
                                            CViewItem &item )
{
    CViewItem_TraceData&        rItemData = static_cast<CViewItem_TraceData&>(item);
    QString                     text = QString().fromWCharArray(rItemData.TraceData()->Data().c_str());

    CViewItemTextPainter::Display(settings, drawstate, item, text);
}


