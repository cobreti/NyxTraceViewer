#ifndef _TRACESPOOL_HPP_
#define _TRACESPOOL_HPP_

#include <Nyx.hpp>
#include <NyxRefCount_Impl.hpp>

#include "TraceDataRepository.hpp"
#include "TraceFeeder.hpp"

#include <QtCore>

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
        CTracesPool(Nyx::CMemoryPool* pMemoryPool, const QString& name);
		virtual ~CTracesPool();
		
        virtual const QString& Name() const	{ return m_Name; }
        virtual void SetName(const QString& name);

        virtual void setDescription(const QString& description);
        virtual const QString& getDescription() const		{ return m_Description; }
		
		CTraceDataRepository&	    Repository()		    { return *m_pRepository; }
        const CTraceDataRepository& Repository() const      { return *m_pRepository; }
				
		Nyx::CMemoryPoolRef			MemoryPool() const	{ return m_refMemoryPool; }
		
	protected:
	
        QString                     m_Name;
        QString     				m_Description;
		CTraceDataRepository*		m_pRepository;
		Nyx::CMemoryPoolRef			m_refMemoryPool;
	};
}


#endif // _TRACESPOOL_HPP_
