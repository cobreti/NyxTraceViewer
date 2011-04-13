#ifndef __VIEWITEMPOS_HPP__
#define __VIEWITEMPOS_HPP__

#include <Nyx.hpp>

class CViewItem;

/**
 *
 */
class CViewItemPos
{
public: // public types

    /**
     *
     */
    enum EViewItemPosIdentifier
    {
        eViewItemPos,
        eViewItemFilteredIndexPos
    };


    /**
     *
     */
    class XData
    {
    public:
        XData() {}
        XData(const XData& data) {}
        virtual ~XData() {}

        virtual bool IsValid() const { return false; }
        virtual XData* Clone() const { return new XData(); }

        virtual void MoveToNext() {}
        virtual void MoveToPrevious() {}
        virtual bool IsFirst() const { return false; }
        virtual bool IsLast() const { return false; }

        virtual bool IsOfType( EViewItemPosIdentifier id ) const { return false; }

        virtual bool IsEqual(const XData& data) const { return false; }

        virtual CViewItem* Item() const { return NULL; }

        virtual double Y() const { return 0; }
    };

public: // public methods
    CViewItemPos();
    CViewItemPos(const CViewItemPos& rPos);
    virtual ~CViewItemPos();

    void operator ++ () { m_pData->MoveToNext(); }
    void operator -- () { m_pData->MoveToPrevious(); }
    virtual bool IsFirst() const { return m_pData->IsFirst(); }
    virtual bool IsLast() const { return m_pData->IsLast(); }
    virtual bool IsValid() const;

    virtual bool IsOfType( EViewItemPosIdentifier id ) const { return m_pData->IsOfType(id); }

    bool operator == (const CViewItemPos& pos) const { return m_pData->IsEqual(*pos.m_pData); }
    bool operator != (const CViewItemPos& pos) const { return !m_pData->IsEqual(*pos.m_pData); }

    const CViewItemPos& operator = (const CViewItemPos& pos);

    virtual CViewItem* Item() const { return m_pData->Item(); }

    virtual double Y() const { return m_pData->Y(); }

    virtual void MoveTo( const double& y );

protected:

    XData*      m_pData;
};


#endif // __VIEWITEMPOS_HPP__
