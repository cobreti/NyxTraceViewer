#include "ViewItems.hpp"
#include "ViewItem.hpp"


/**
 *
 */
CViewItems::CViewItems( Nyx::CMemoryPool* pPool ) :
Nyx::CMemPoolObj<>(pPool)
{
}


/**
 *
 */
CViewItems::~CViewItems()
{
    Clear();
}


/**
 *
 */
void CViewItems::Add( CViewItem* pItem )
{
    m_Items.push_back(pItem);

//    m_Size.rheight() += pItem->GetSize().height();
//    m_Size.rwidth() = Nyx::Max( m_Size.width(), pItem->GetSize().width() );
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
}


/**
 *
 */
CViewItemPos CViewItems::begin() const
{
    return CViewItems::XPos(m_Items, m_Items.begin(), 0.0);
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


/*********************************************
  CViewItems::XPosData
  *******************************************/


/**
 *
 */
CViewItems::XPosData::XPosData(const CViewItems::XPosData &data) :
m_Pos(data.m_Pos),
m_pList(data.m_pList),
m_Y(data.m_Y)
{
}


/**
 *
 */
CViewItems::XPosData::XPosData(const TViewItemsList &rList, const TViewItemsList::const_iterator &pos, double y) :
m_Pos(pos),
m_pList(&rList),
m_Y(y)
{
}


/**
 *
 */
bool CViewItems::XPosData::IsValid() const
{
    if ( m_pList )
        return m_Pos != m_pList->end();

    return false;
}


/**
 *
 */
CViewItemPos::XData* CViewItems::XPosData::Clone() const
{
    return new CViewItems::XPosData(*this);
}


/**
 *
 */
void CViewItems::XPosData::MoveToNext()
{
    m_Y += (*m_Pos)->GetSize().height();
    ++ m_Pos;
}


/**
 *
 */
void CViewItems::XPosData::MoveToPrevious()
{
    -- m_Pos;
    m_Y -= (*m_Pos)->GetSize().height();
}


/**
 *
 */
bool CViewItems::XPosData::IsFirst() const
{
    if ( m_pList )
        return m_Pos == m_pList->begin();

    return false;
}


/**
 *
 */
bool CViewItems::XPosData::IsLast() const
{
    if ( m_pList )
        return m_Pos == m_pList->end();

    return false;
}


/**
 *
 */
bool CViewItems::XPosData::IsOfType(CViewItemPos::EViewItemPosIdentifier id) const
{
    return id == CViewItemPos::eViewItemPos;
}


/**
 *
 */
bool CViewItems::XPosData::IsEqual(const CViewItemPos::XData &data) const
{
    if ( data.IsOfType(CViewItemPos::eViewItemPos) )
        return m_Pos == static_cast<const CViewItems::XPosData&>(data).m_Pos;

    return false;
}


/**
 *
 */
CViewItem* CViewItems::XPosData::Item() const
{
    return *m_Pos;
}


/**
 *
 */
double CViewItems::XPosData::Y() const
{
    return m_Y;
}


/*********************************************
  CViewItems::XPos
  *******************************************/


/**
 *
 */
CViewItems::XPos::XPos(const TViewItemsList& rList, const TViewItemsList::const_iterator &pos, double y) :
CViewItemPos()
{
    m_pData = new CViewItems::XPosData(rList, pos, y);
}

