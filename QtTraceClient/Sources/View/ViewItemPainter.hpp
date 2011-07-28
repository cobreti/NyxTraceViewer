#ifndef _VIEWITEMPAINTER_HPP_
#define _VIEWITEMPAINTER_HPP_

#include <Nyx.hpp>
#include <QSizeF>
#include <QFont>
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
        ePId_Generic = 0,
        ePId_Collection,
        ePId_Data,
        ePId_TickCount,
        ePId_ThreadId,
        ePId_ModuleName,
        ePId_Header,
		ePId_Row,
        ePId_LineNumber,
        ePId_Count
    };

    static EViewColumnId PainterId2ColumnId( EPainterId );

public:
    virtual ~CViewItemPainter();

    virtual void EvaluateSize( CViewSettings& settings, CViewItem& item );
    virtual void Display( const CViewSettings& settings, CDrawViewItemState& drawstate, CViewItem& item );

    virtual EPainterId Id() const = 0;

    virtual void SetFont( const QFont& font );

    const QFont& Font() const       { return m_Font; }
//    QFont& Font()                   { return m_Font; }

    float MaxFontHeight() const     { return m_MaxFontHeight; }

protected:
    CViewItemPainter();

protected:

    QFont           m_Font;
    float           m_MaxFontHeight;
};

#endif // _VIEWITEMPAINTER_HPP_
