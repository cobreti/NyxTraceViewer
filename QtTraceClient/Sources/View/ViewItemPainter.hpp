#ifndef _VIEWITEMPAINTER_HPP_
#define _VIEWITEMPAINTER_HPP_

#include <Nyx.hpp>
#include <QSizeF>
#include "DrawViewItemState.hpp"
#include "ViewColumnId.hpp"


class CViewItem;
class CViewSettings;


DECLARE_OBJECTREF(CViewItemPainter)


/**
 *
 */
class CViewItemPainter : public Nyx::CRefCount_Impl<>
{
public:

    enum EPainterId
    {
        ePId_Generic,
        ePId_Collection,
        ePId_Data,
        ePId_TickCount,
        ePId_ThreadId,
        ePId_ModuleName,
        ePId_Header,
		ePId_Row
    };

    static EViewColumnId PainterId2ColumnId( EPainterId );

public:
    virtual ~CViewItemPainter();

    virtual void EvaluateSize( CViewSettings& settings, CViewItem& item );
    virtual void Display( const CViewSettings& settings, CDrawViewItemState& drawstate, CViewItem& item );

    virtual EPainterId Id() const = 0;

protected:
    CViewItemPainter();
};

#endif // _VIEWITEMPAINTER_HPP_
