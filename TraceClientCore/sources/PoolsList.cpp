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
    CPoolsListItem::CPoolsListItem(const CPoolsListItem& item) :
    m_pPool(item.m_pPool)
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
	}

}
