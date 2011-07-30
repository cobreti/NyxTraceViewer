#ifndef __VIEWITEM_HPP__
#define __VIEWITEM_HPP__

#include <QSizeF>
#include <Nyx.hpp>
#include <bitset>
#include "ViewItemPainterCollection.hpp"

class CDrawViewItemState;
class CViewSettings;


typedef     size_t          ViewItemID;


/**
 *
 */
class CViewItem
{
public:

    enum EViewItemType
    {
        eViewItem_TraceData
    };

    enum EViewItemFlags
    {
        eVIF_Marked = 1,
        eVIF_ApproxSize,    // size is an approximation only
        eVIF_SizeCalculated,
        eVIF_Count
    };

public:
    CViewItem();
    virtual ~CViewItem();

    virtual const Nyx::CWString& ModuleName() const = 0;

    virtual bool IsOfKind( EViewItemType ) const { return false; }

    virtual void dbgOutputInfo();

    const QSizeF& GetSize() { return m_Size; }
    virtual void SetSize(const QSizeF& size) { m_Size = size; }
    virtual void AddSize(const QSizeF& size);

    virtual void EvaluateSize(CViewSettings& settings);
    virtual void Display( CViewSettings& settings, CDrawViewItemState& drawstate );

//    CViewItemPainterCollection&         Painters()              { return m_Painters; }
//    const CViewItemPainterCollection&   Painters() const        { return m_Painters; }

    virtual void SetFlag( EViewItemFlags flag, bool status = true );
    virtual void RemoveFlag( EViewItemFlags flag );
    virtual bool HasFlag( EViewItemFlags flag ) const;

    const ViewItemID&   Id() const              { return m_Id; }
    ViewItemID&         Id()                    { return m_Id; }

    virtual const Nyx::CWString& TickCount() const;

protected:

    typedef     std::bitset<eVIF_Count>         FlagsSet;

protected:

    QSizeF                          m_Size;
//    CViewItemPainterCollection      m_Painters;
    FlagsSet                        m_Flags;
    size_t                          m_Id;
};


/**
 *
 */
typedef     Nyx::CMemPoolObj<CViewItem>     ViewItemMemPoolObj;


#endif // __VIEWITEM_HPP__
