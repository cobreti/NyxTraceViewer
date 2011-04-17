#include "ViewItemPainterCollection.hpp"


/**
 *
 */
CViewItemPainterCollection::CViewItemPainterCollection() :
CViewItemPainter(),
m_Id(ePId_Collection),
m_PaintersCount(0)
{
}


/**
 *
 */
CViewItemPainterCollection::~CViewItemPainterCollection()
{
}


/**
 *
 */
void CViewItemPainterCollection::Add( CViewItemPainter* pPainter, CViewItemPainterCollection::EChildPosition )
{
    m_Painters[m_PaintersCount++] = pPainter;
}


/**
 *
 */
CViewItemPainter* CViewItemPainterCollection::operator [] (const CViewItemPainter::EPainterId& id) const
{
    for (size_t index = 0; index < m_PaintersCount; ++ index)
        if ( m_Painters[index]->Id() == id )
            return m_Painters[index];

    return NULL;
}


/**
 *
 */
//void CViewItemPainterCollection::Remove(EPainterId id)
//{
//    //ViewItemPaintersList::iterator      pos = m_ChildPainters.begin();
//
//    //while ( pos != m_ChildPainters.end() )
//    //{
//    //    if ( (*pos)->Id() == id )
//    //    {
//    //        m_ChildPainters.erase(pos);
//    //        break;
//    //    }
//
//    //    ++ pos;
//    //}
//}


/**
 *
 */
void CViewItemPainterCollection::EvaluateSize(CViewSettings& settings, CViewItem &item)
{
    for (size_t index = 0; index < m_PaintersCount; ++index)
        m_Painters[index]->EvaluateSize(settings, item);
}


/**
 *
 */
void CViewItemPainterCollection::Display(const CViewSettings& settings, CDrawViewItemState &drawstate, CViewItem &item)
{
    for (size_t index = 0; index < m_PaintersCount; ++index)
        m_Painters[index]->Display(settings, drawstate, item);
}

