#include "ViewItemLineNumberPainter.hpp"
#include "ViewSettings.hpp"
#include "ViewItem.hpp"
#include "ViewColumnsSettings.hpp"
#include "ViewColumnSettings.hpp"


CViewItemPainterRef     CViewItemLineNumberPainter::s_refPainter;


/**
 *
 */
CViewItemPainter* CViewItemLineNumberPainter::Instance()
{
    if ( !s_refPainter.Valid() )
        s_refPainter = new CViewItemLineNumberPainter();

    return s_refPainter;
}


/**
 *
 */
CViewItemLineNumberPainter::CViewItemLineNumberPainter()
{
}


/**
 *
 */
CViewItemLineNumberPainter::~CViewItemLineNumberPainter()
{
}


/**
 *
 */
void CViewItemLineNumberPainter::EvaluateSize(CViewSettings &settings, CViewItem &item)
{
    QString                     text = QString::number(item.LineNumber());

    CViewItemTextPainter::EvaluateSize(settings, item, text);
}


/**
 *
 */
void CViewItemLineNumberPainter::Display( const CViewSettings &settings,
                                            CDrawViewItemState &drawstate,
                                            CViewItem &item )
{
    QString                     text = QString::number(item.LineNumber());

    CViewItemTextPainter::Display(settings, drawstate, item, text);
}
