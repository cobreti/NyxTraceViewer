#ifndef _VIEWCOLUMNSORDER_HPP_
#define _VIEWCOLUMNSORDER_HPP_

#include <Nyx.hpp>

#include "ViewColumnId.hpp"
#include <vector>

class CViewColumnsOrder
{
public:
	CViewColumnsOrder();
	virtual ~CViewColumnsOrder();

	EViewColumnId operator [] (size_t index) const		{ return m_ColumnsOrder[index]; }

	void Set( EViewColumnId id, size_t newPos );
    size_t Count() const        { return m_ColumnsOrder.size(); }

    const ColumnsIdVector& OrderVector() const          { return m_ColumnsOrder; }

    const CViewColumnsOrder& operator = (const CViewColumnsOrder& columnsOrder);

protected:

    ColumnsIdVector         m_ColumnsOrder;
};


#endif // _VIEWCOLUMNSORDER_HPP_
