
#include "ViewTracesContentIterator.hpp"
#include "ViewTracePortal.h"


CViewTracesContentIterator::CViewTracesContentIterator() : CViewTracesIterator(),
    m_ColumnIndex(-1),
    m_TextIndex(-1)
{

}


CViewTracesContentIterator::CViewTracesContentIterator(const CViewTracesContentIterator &iterator) : CViewTracesIterator(iterator),
    m_ColumnIndex(iterator.m_ColumnIndex),
    m_TextIndex(iterator.m_TextIndex),
    m_Text(iterator.m_Text),
    m_ColumnsOrder(iterator.m_ColumnsOrder)
{

}


CViewTracesContentIterator::~CViewTracesContentIterator()
{

}


const CViewTracesContentIterator& CViewTracesContentIterator::operator = (const CViewTracesContentIterator& iterator)
{
    CViewTracesIterator::operator = (iterator);

    m_ColumnIndex = iterator.m_ColumnIndex;
    m_TextIndex = iterator.m_TextIndex;
    m_Text = iterator.m_Text;
    m_ColumnsOrder = iterator.m_ColumnsOrder;

    return *this;
}


const CViewTracesContentIterator& CViewTracesContentIterator::operator = (const CViewTracesIterator& iterator)
{
    CViewTracesIterator::operator = (iterator);

    m_ColumnIndex = 0;
    m_TextIndex = -1;

    return *this;
}


void CViewTracesContentIterator::setText(const QString &text)
{
    m_Text = text;
}


void CViewTracesContentIterator::setColumnsOrder(const ColumnsIdVector &columnsOrder)
{
    m_ColumnsOrder = columnsOrder;
}


CViewTracesContentIterator& CViewTracesContentIterator::operator ++ ()
{
    do
    {
        CViewTracePortal        portal(*(m_Pos.TraceData()), m_LineNumber);
        QString                 columnText = portal.GetColumnText( m_ColumnsOrder[m_ColumnIndex] );

        m_TextIndex = columnText.indexOf(m_Text, m_TextIndex+1);

        if ( m_TextIndex == -1 )
        {
            if ( m_ColumnIndex < m_ColumnsOrder.size() )
                ++ m_ColumnIndex;
            else
            {
                m_ColumnIndex = 0;
                CViewTracesIterator::operator ++();
            }
        }

    }
    while ( CViewTracesIterator::Valid() && m_TextIndex == -1 );

    return *this;
}
