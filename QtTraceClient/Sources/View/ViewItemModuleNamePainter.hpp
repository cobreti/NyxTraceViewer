#ifndef _VIEWITEMMODULENAMEPAINTER_HPP_
#define _VIEWITEMMODULENAMEPAINTER_HPP_

#include "ViewItemTextPainter.hpp"

/**
 *
 */
class CViewItemModuleNamePainter : public CViewItemTextPainter
{
public:

    static CViewItemPainter* Instance();

public:
    CViewItemModuleNamePainter();
    virtual ~CViewItemModuleNamePainter();

    virtual EPainterId Id() const { return ePId_ModuleName; }

    virtual void EvaluateSize( CViewSettings& settings, CViewItem& item );
    virtual void Display( const CViewSettings& settings, CDrawViewItemState& drawstate, CViewItem& item );

private:

    static CViewItemPainterRef      s_refPainter;
};

#endif // _VIEWITEMMODULENAMEPAINTER_HPP_
