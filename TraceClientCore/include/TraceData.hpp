#ifndef _TRACEDATA_HPP_
#define _TRACEDATA_HPP_

#include <Nyx.hpp>
#include <NyxRefCount_Impl.hpp>
#include <NyxMemPoolObj.hpp>
#include <NyxMemPoolWString.hpp>


namespace TraceClientCore
{
	class CTracesPool;
	
	class CTraceData : public Nyx::CMemPoolObj<>
	{
		typedef		Nyx::CMemPoolObj<>		BaseType;

    public:

        enum ETraceType
        {
            eTT_User,
            eTT_ConnectionStatus
        };

	public:
		CTraceData(Nyx::CMemoryPool* pMemPool);
		virtual ~CTraceData();
				
		const Nyx::CMemPoolWString& ThreadId() const		{ return m_ThreadId; }
		Nyx::CMemPoolWString& ThreadId()					{ return m_ThreadId; }
		
		const Nyx::CMemPoolWString& TickCount() const		{ return m_TickCount; }
		Nyx::CMemPoolWString& TickCount()					{ return m_TickCount; }
		
		const Nyx::CMemPoolWString& Data() const			{ return m_Data; }
		Nyx::CMemPoolWString& Data()						{ return m_Data; }

		CTracesPool* OwnerPool() const				{ return m_pOwnerPool; }
		CTracesPool*& OwnerPool()					{ return m_pOwnerPool; }

        const ETraceType& Type() const              { return m_eType; }
        ETraceType& Type()                          { return m_eType; }
		
	protected:
	
		Nyx::CMemPoolWString		m_ThreadId;
		Nyx::CMemPoolWString		m_TickCount;
		Nyx::CMemPoolWString		m_Data;
		CTracesPool*				m_pOwnerPool;
        ETraceType					m_eType;
	};
}

#endif // _TRACEDATA_HPP_
