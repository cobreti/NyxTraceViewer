#ifndef _POOLSLIST_HPP_
#define _POOLSLIST_HPP_

#include <list>

namespace TraceClientCore
{
	class CTracesPool;


	/**
	 *
	 */
	class CPoolsListItem
	{
	public:
		CPoolsListItem( CTracesPool* pPool );
        CPoolsListItem( const CPoolsListItem& item );
		~CPoolsListItem();

		CTracesPool* Pool() const		{ return m_pPool; }

	protected:
		CTracesPool*		m_pPool;
	};


	/**
	 *
	 */
	class CPoolsList : public std::list<CPoolsListItem>
	{
	public:
		CPoolsList();
		virtual ~CPoolsList();
	};
}


#endif // _POOLSLIST_HPP_
