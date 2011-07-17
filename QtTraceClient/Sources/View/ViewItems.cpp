#include "ViewItems.hpp"
#include "ViewItem.hpp"


/**
 *
 */
CViewItems::CViewItems( Nyx::CMemoryPool* pPool, bool bOwnItems ) :
Nyx::CMemPoolObj<>(pPool),
m_bOwnItems(bOwnItems)
{
}


/**
 *
 */
CViewItems::~CViewItems()
{
    Clear(m_bOwnItems);
}


/**
 *
 */
void CViewItems::Add( CViewItem* pItem )
{
    m_Items.push_back(pItem);

    AddToClientSize(pItem);
    m_LastLineSize = pItem->GetSize();
}


/**
 *
 */
void CViewItems::RemoveFromClientSize( CViewItem* pItem )
{
    m_Size.rheight() -= pItem->GetSize().height();
}


/**
 *
 */
void CViewItems::AddToClientSize( CViewItem* pItem )
{
    m_Size.rheight() += pItem->GetSize().height();
    m_Size.rwidth() = Nyx::Max( m_Size.width(), pItem->GetSize().width() );

    m_MaxLineSize = QSizeF(     Nyx::Max(m_MaxLineSize.width(), pItem->GetSize().width()),
                                Nyx::Max(m_MaxLineSize.height(), pItem->GetSize().height()) );
}


/**
 *
 */
CViewItemPos CViewItems::begin() const
{
    return CViewItemPos(m_Items, m_Items.begin());
}


/**
 *
 */
CViewItemPos CViewItems::end() const
{
    TViewItemsList::const_iterator        last = m_Items.end();
    -- last;

    return CViewItemPos(m_Items, last);
}


/**
 *
 */
size_t CViewItems::ItemsCount() const
{
    return m_Items.size();
}


/**
 *
 */
const QSizeF& CViewItems::GetSize() const
{
    return m_Size;
}


/**
 *
 */
const QSizeF& CViewItems::GetLastLineSize() const
{
    return m_LastLineSize;
}


/**
 *
 */
const QSizeF& CViewItems::GetMaxLineSize() const
{
    return m_MaxLineSize;
}


/**
 *
 */
void CViewItems::Clear(bool bDeleteItems /*= true*/)
{
    if ( bDeleteItems )
    {
        while (!m_Items.empty())
        {
            CViewItem* pItem = m_Items.front();
            m_Items.pop_front();
            delete pItem;
        }
    }
    else
        m_Items.clear();
}


/**
 *
 */
const CViewItems& CViewItems::operator += (CViewItems& items)
{
    TViewItemsList::iterator        pos = items.m_Items.begin();

    while ( pos != items.m_Items.end() )
    {
        Add( *pos );
        ++ pos;
    }

    return *this;
}
