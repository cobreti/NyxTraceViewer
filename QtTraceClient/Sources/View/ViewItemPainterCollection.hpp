#ifndef __VIEWITEMPAINTERCOLLECTION_HPP__
#define __VIEWITEMPAINTERCOLLECTION_HPP__

#include "ViewItemPainter.hpp"
#include <list>


/**
 *
 */
class CViewItemPainterCollection : public CViewItemPainter
{
public:

    enum EChildPosition
    {
        //eCP_First,
        eCP_Last
    };

public:
    CViewItemPainterCollection();
    virtual ~CViewItemPainterCollection();

    virtual EPainterId Id() const { return m_Id; }

    virtual void Add( CViewItemPainter* pPainter, EChildPosition pos = eCP_Last );
    CViewItemPainter* operator [] (const CViewItemPainter::EPainterId& id) const;
    //virtual void Remove( EPainterId id );

    virtual void EvaluateSize( CViewSettings& settings, CViewItem& item );
    virtual void Display( const CViewSettings& settings, CDrawViewItemState &drawstate, CViewItem &item );

protected:

    typedef     std::list<CViewItemPainterRef>      ViewItemPaintersList;

    enum
    {
        kMaxPainters = 20
    };

protected:

    //ViewItemPaintersList            m_ChildPainters;
    CViewItemPainter*               m_Painters[kMaxPainters];
    size_t                          m_PaintersCount;
    EPainterId                      m_Id;
};

#endif // __VIEWITEMPAINTERCOLLECTION_HPP__
