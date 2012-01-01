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

protected:

	typedef		std::vector<EViewColumnId>		ColumnIdVector;

protected:

	ColumnIdVector		m_ColumnsOrder;
};


#endif // _VIEWCOLUMNSORDER_HPP_
