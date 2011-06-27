#ifndef __VIEWITEMSWALKERSTATS_HPP__
#define __VIEWITEMSWALKERSTATS_HPP__


#include <QSize>


/**
 *
 */
class CViewItemsWalkerStats
{
public:
    CViewItemsWalkerStats();
    CViewItemsWalkerStats(const CViewItemsWalkerStats& stats);
    ~CViewItemsWalkerStats();

    const CViewItemsWalkerStats& operator = (const CViewItemsWalkerStats& stats);

    const size_t&           ItemsCount() const              { return m_ItemsCount; }
    size_t&                 ItemsCount()                    { return m_ItemsCount; }

    const QSizeF&           Size() const                    { return m_Size; }
    QSizeF&                 Size()                          { return m_Size; }

    const QSizeF&           MaxLineSize() const             { return m_MaxLineSize; }
    QSizeF&                 MaxLineSize()                   { return m_MaxLineSize; }

    void Add( CViewItemsWalkerStats& stats );

protected:

    size_t      m_ItemsCount;
    QSizeF      m_Size;
    QSizeF      m_MaxLineSize;
};





#endif // VIEWITEMSWALKERSTATS_HPP
