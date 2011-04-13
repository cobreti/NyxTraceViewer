#ifndef _UITRACEDATAREPOSITORY_HPP_
#define _UITRACEDATAREPOSITORY_HPP_

#include <NyxMTInterfaceAccess.hpp>
#include <list>

#include "UITraceData.hpp"


class CUITraceDataRepositoryIterator;


/**
 *
 */
class IUITraceDataRepository
{
public:

	virtual const CUITraceDataRepositoryIterator& HeadPos() const = 0;
	virtual const CUITraceDataRepositoryIterator& TailPos() const = 0;
	virtual size_t Count() const = 0;
	virtual CUITraceData* Get( const CUITraceDataRepositoryIterator& pos ) const = 0;
	virtual void Add( CUITraceData* pTraceData ) = 0;
};


/**
 *
 */
class CUITraceDataRepository : public Nyx::CMTInterfaceAccess<CUITraceDataRepository, IUITraceDataRepository>
{
	friend class CUITraceDataRepositoryIterator;

public: // public methods
	CUITraceDataRepository();
	virtual ~CUITraceDataRepository();

protected: // protected types

	typedef		std::list<CUITraceDataRef>			UITraceDataList;

protected: // protected methods

	virtual const CUITraceDataRepositoryIterator& HeadPos() const;
	virtual const CUITraceDataRepositoryIterator& TailPos() const;
	virtual size_t Count() const;
	virtual CUITraceData* Get( const CUITraceDataRepositoryIterator& pos ) const;
	virtual void Add( CUITraceData* pTraceData );

protected: // protected members

	UITraceDataList							m_Traces;
	CUITraceDataRepositoryIterator*			m_pLastPos;
	CUITraceDataRepositoryIterator*			m_pHeadPos;
};


#endif // _UITRACEDATAREPOSITORY_HPP_
