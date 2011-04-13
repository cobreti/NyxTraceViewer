#include "DataStruct/PoolsList.hpp"


namespace TraceClientCore
{
	/**
	 *
	 */
	CPoolsListItem::CPoolsListItem(TraceClientCore::CTracesPool *pPool) : m_pPool(pPool)
	{
	}

	/**
	 *
	 */
	CPoolsListItem::~CPoolsListItem()
	{
	}


	/**
	 *
	 */
	CPoolsList::CPoolsList()
	{
	}

	/**
	 *
	 */
	CPoolsList::~CPoolsList()
	{
		while ( !empty() )
		{
			CPoolsListItem*	pItem = front();
			pop_front();
			delete pItem;
		}
	}

}
