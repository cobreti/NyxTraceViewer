#ifndef _UITRACEDATAREPOSITORYITERATOR_HPP_
#define _UITRACEDATAREPOSITORYITERATOR_HPP_

#include <NyxMTObjAccessor.hpp>

#include "UITraceDataRepository.hpp"


/**
 *
 */
class IUITraceDataRepositoryIterator
{
public: // public methods

	virtual void Goto( size_t new_pos ) = 0;
	virtual size_t Index() const = 0;
};


/** 
 *
 */
class CUITraceDataRepositoryIterator : protected IUITraceDataRepositoryIterator
{
public: // public types

	friend class Nyx::CMTObjAccessor<CUITraceDataRepositoryIterator, IUITraceDataRepositoryIterator>;
	friend class CUITraceDataRepository;

	typedef		Nyx::CMTObjAccessor<CUITraceDataRepositoryIterator, IUITraceDataRepositoryIterator>		Accessor;

public:	// public methods
	CUITraceDataRepositoryIterator( const CUITraceDataRepository& rRepos );
	virtual ~CUITraceDataRepositoryIterator();

	const CUITraceDataRepositoryIterator& operator = ( const CUITraceDataRepositoryIterator& pos );
	bool operator == ( const CUITraceDataRepositoryIterator& pos ) const;
	bool operator != ( const CUITraceDataRepositoryIterator& pos ) const;

	virtual size_t Index() const;

protected: // protected types

	typedef	CUITraceDataRepository::UITraceDataList::const_iterator		TraceDataIterator;

protected: // protected methods

	virtual bool MTLock();
	virtual bool MTTryLock();
	virtual void MTUnlock();

	virtual void Goto( size_t new_pos );

	CUITraceDataRepositoryIterator& operator ++ ();
	CUITraceDataRepositoryIterator& operator -- ();

protected: // protected members

	const CUITraceDataRepository&		m_rRepos;
	TraceDataIterator					m_Pos;
	size_t								m_Index;
};


#endif // _UITRACEDATAREPOSITORYITERATOR_HPP_
