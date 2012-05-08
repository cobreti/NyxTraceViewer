#include <Nyx.hpp>
#include "TracesViewSet.hpp"

/**
 *
 */
CTracesViewSet::CTracesViewSet()
{
}


/**
 *
 */
CTracesViewSet::CTracesViewSet(const CTracesViewSet &set) :
m_Views(set.m_Views)
{

}


/**
 *
 */
CTracesViewSet::~CTracesViewSet()
{
}


/**
 *
 */
const CTracesViewSet& CTracesViewSet::operator = (const CTracesViewSet& set)
{
    if ( &set != this )
    {
        m_Views = set.m_Views;
    }

    return *this;
}


/**
 *
 */
void CTracesViewSet::Insert(CTracesView *pView)
{
    m_Views.insert(pView);
}


/**
 *
 */
void CTracesViewSet::Remove(CTracesView *pView)
{
    m_Views.erase(pView);
}


/**
 *
 */
CTracesViewSetIterator::CTracesViewSetIterator(const CTracesViewSet& rSet) :
    m_rSet(rSet)
{
}


/**
 *
 */
CTracesViewSetIterator::CTracesViewSetIterator(const CTracesViewSetIterator &iterator) :
    m_rSet(iterator.m_rSet),
    m_Pos(iterator.m_Pos)
{

}


/**
 *
 */
CTracesViewSetIterator::~CTracesViewSetIterator()
{
}


/**
 *
 */
const CTracesViewSetIterator& CTracesViewSetIterator::operator = (const CTracesViewSetIterator& iterator)
{
    if ( &iterator != this && &iterator.m_rSet == &m_rSet )
    {
        m_Pos = iterator.m_Pos;
    }

    return *this;
}


/**
 *
 */
bool CTracesViewSetIterator::Valid() const
{
    return (m_Pos != m_rSet.m_Views.end());
}


/**
 *
 */
bool CTracesViewSetIterator::MoveToFirst()
{
    m_Pos = m_rSet.m_Views.begin();

    return Valid();
}


/**
 *
 */
bool CTracesViewSetIterator::MoveToNext()
{
    ++ m_Pos;

    return Valid();
}


/**
 *
 */
CTracesView* CTracesViewSetIterator::View() const
{
    if ( !Valid() )
        return NULL;

    return *m_Pos;
}
