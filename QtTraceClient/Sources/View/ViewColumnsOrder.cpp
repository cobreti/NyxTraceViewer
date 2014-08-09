#include "ViewColumnsOrder.hpp"


/**
 *
 */
CViewColumnsOrder::CViewColumnsOrder()
{
	m_ColumnsOrder.resize(eVCI_Count);

	m_ColumnsOrder[0] = eVCI_LineNumber;
    m_ColumnsOrder[1] = eVCI_ModuleName;
	m_ColumnsOrder[2] = eVCI_TickCount;
	m_ColumnsOrder[3] = eVCI_ThreadId;
	m_ColumnsOrder[4] = eVCI_Data;
}


/**
 *
 */
CViewColumnsOrder::~CViewColumnsOrder()
{
}


/**
 *
 */
void CViewColumnsOrder::Set( EViewColumnId id, size_t newPos )
{
	size_t		i = 0;
	size_t		oldPos = 0;

	for (i = 0; i < m_ColumnsOrder.size(); ++i)
		if ( m_ColumnsOrder[i] == id )
		{
			oldPos = i;
			break;
		}

	if ( oldPos < newPos )
	{
		for (i = oldPos; i < newPos; ++i)
			m_ColumnsOrder[i] = m_ColumnsOrder[i+1];
	}
	else
	{
		for (i = oldPos; i > newPos; --i)
			m_ColumnsOrder[i] = m_ColumnsOrder[i-1];
	}

	m_ColumnsOrder[newPos] = id;
}



/**
 *
 */
const CViewColumnsOrder& CViewColumnsOrder::operator = (const CViewColumnsOrder& columnsOrder)
{
    if ( this != &columnsOrder )
    {
        m_ColumnsOrder = columnsOrder.m_ColumnsOrder;
    }

    return *this;
}

