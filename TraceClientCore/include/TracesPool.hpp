#ifndef _TRACESPOOL_HPP_
#define _TRACESPOOL_HPP_

#include <Nyx.hpp>
#include <NyxRefCount_Impl.hpp>

#include "TraceDataRepository.hpp"
#include "TraceFeeder.hpp"


namespace TraceClientCore
{
	class CTraceFeeder;
	

	DECLARE_OBJECTREF(CTracesPool);

	/**
	 *
	 */
	class CTracesPool : public Nyx::CRefCount_Impl<>
	{
	public:
		CTracesPool(Nyx::CMemoryPool* pMemoryPool, const wchar_t* wszName);
		virtual ~CTracesPool();
		
		virtual const Nyx::CWString& Name() const	{ return m_Name; }
		virtual void SetName(const wchar_t* wszName);

		virtual void setDescription(const wchar_t* wszDescription);
		virtual const Nyx::CWString& getDescription() const		{ return m_Description; }
		
		CTraceDataRepository&	    Repository()		    { return *m_pRepository; }
        const CTraceDataRepository& Repository() const      { return *m_pRepository; }
		
		const CTraceFeederRef&		Feeder() const		{ return m_refFeeder; }
		CTraceFeederRef&			Feeder()			{ return m_refFeeder; }
		
		Nyx::CMemoryPoolRef			MemoryPool() const	{ return m_refMemoryPool; }
		
	protected:
	
		Nyx::CWString				m_Name;
		Nyx::CWString				m_Description;
		CTraceDataRepository*		m_pRepository;
		CTraceFeederRef				m_refFeeder;
		Nyx::CMemoryPoolRef			m_refMemoryPool;
	};
}


#endif // _TRACESPOOL_HPP_
