#ifndef __VIEWITEM_HPP__
#define __VIEWITEM_HPP__

#include <QSizeF>
#include <QString>
#include <Nyx.hpp>
#include <bitset>

class CDrawViewItemState;
class CViewSettings;
class CHighlightBrush;


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

    enum EItemIndex
    {
        eII_Module = 0,
        eII_ThreadId = 1,
        eII_TimeStamp = 2,
        eII_TraceData = 3
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

    virtual void SetFlag( EViewItemFlags flag, bool status = true );
    virtual void RemoveFlag( EViewItemFlags flag );
    virtual bool HasFlag( EViewItemFlags flag ) const;

    const ViewItemID&   Id() const              { return m_Id; }
    ViewItemID&         Id()                    { return m_Id; }

    virtual const Nyx::CWString& TickCount() const;

    virtual const QString GetItemString(const EItemIndex&) const       { return ""; }

    void SetOwner( CViewItem* pOwner )          { m_pOwner = pOwner; }
    CViewItem* GetOwner() const                 { return m_pOwner; }

    CHighlightBrush*        HighlightBrush() const          { return m_pHighlightBrush; }
    CHighlightBrush*&       HighlightBrush()                { return m_pHighlightBrush; }

protected:

    typedef     std::bitset<eVIF_Count>         FlagsSet;

protected:

    QSizeF                          m_Size;
    FlagsSet                        m_Flags;
    size_t                          m_Id;
    CViewItem*                      m_pOwner;
    CHighlightBrush*                m_pHighlightBrush;
};


/**
 *
 */
class CViewItemMemPoolObj : public Nyx::CMemPoolObj<CViewItem>
{
    typedef     Nyx::CMemPoolObj<CViewItem>     Super;

public:
    CViewItemMemPoolObj(Nyx::CMemoryPool* pMemPool) : Super(pMemPool) {}
    virtual ~CViewItemMemPoolObj() {}
};



#endif // __VIEWITEM_HPP__
