#ifndef _TRACEDATA_HPP_
#define _TRACEDATA_HPP_

#include <Nyx.hpp>
#include <NyxRefCount_Impl.hpp>
#include <NyxMemPoolObj.hpp>
#include <NyxMemPoolWString.hpp>
#include <NyxNetTraceFlags.hpp>


namespace TraceClientCore
{
	class CTracesPool;
	
	class CTraceData : public Nyx::CMemPoolObj<>
	{
		typedef		Nyx::CMemPoolObj<>		BaseType;

    public:

        class CIdentifier
        {
        public:
            CIdentifier();
            CIdentifier(const int& repositoryId, const int& traceId, const int& level);
            CIdentifier(const CIdentifier& identifier);
            ~CIdentifier();


            const CIdentifier& operator = (const CIdentifier& identifier);
            bool operator == (const CIdentifier& identifier) const;
            bool operator != (const CIdentifier& identifier) const;
            bool operator < (const CIdentifier& identifier) const;
            bool operator <= (const CIdentifier& identifier) const;
            bool operator > (const CIdentifier& identifier) const;
            bool operator >= (const CIdentifier& identifier) const;

        protected:

            Nyx::UInt32     m_RepositoryId;
            Nyx::UInt32     m_TraceId;
            Nyx::UInt32     m_Level;
        };

        enum ETraceType
        {
            eTT_User,
            eTT_ConnectionStatus_Connection,
            eTT_ConnectionStatus_Disconnection
        };

	public:
		CTraceData(Nyx::CMemoryPool* pMemPool);
		virtual ~CTraceData();
				
		const Nyx::CMemPoolWString& TimeReference() const	{ return m_TimeReference; }
		Nyx::CMemPoolWString& TimeReference()				{ return m_TimeReference; }

        const Nyx::CMemPoolWString& TickCountReference() const		{ return m_TickCountReference; }
		Nyx::CMemPoolWString& TickCountReference()					{ return m_TickCountReference; }        

		const Nyx::CMemPoolWString& ThreadId() const		{ return m_ThreadId; }
		Nyx::CMemPoolWString& ThreadId()					{ return m_ThreadId; }
		
		const Nyx::CMemPoolWString& TickCount() const		{ return m_TickCount; }
		Nyx::CMemPoolWString& TickCount()					{ return m_TickCount; }
		
		const Nyx::CMemPoolWString& Data() const			{ return m_Data; }
		Nyx::CMemPoolWString& Data()						{ return m_Data; }

		CTracesPool* OwnerPool() const				        { return m_pOwnerPool; }
		CTracesPool*& OwnerPool()					        { return m_pOwnerPool; }

        const ETraceType& Type() const                      { return m_eType; }
        ETraceType& Type()                                  { return m_eType; }
        
        const NyxNet::CTraceFlags& Flags() const            { return m_Flags; }
        NyxNet::CTraceFlags& Flags()                        { return m_Flags; }
        
        const Nyx::UInt32& RepositoryId() const             { return m_RepositoryId; }
        Nyx::UInt32& RepositoryId()                         { return m_RepositoryId; }
        
        const Nyx::UInt32& TraceId() const                  { return m_TraceId; }
        Nyx::UInt32& TraceId()                              { return m_TraceId; }

        const Nyx::UInt32& Level() const                    { return m_Level; }
        Nyx::UInt32& Level()                                { return m_Level; }

        const CIdentifier identifier() const                { return CIdentifier(m_RepositoryId, m_TraceId, m_Level); }
		
	protected:
	
        Nyx::CMemPoolWString        m_TimeReference;
        Nyx::CMemPoolWString        m_TickCountReference;

		Nyx::CMemPoolWString		m_ThreadId;
		Nyx::CMemPoolWString		m_TickCount;
		Nyx::CMemPoolWString		m_Data;
		CTracesPool*				m_pOwnerPool;
        ETraceType					m_eType;
        NyxNet::CTraceFlags         m_Flags;
        Nyx::UInt32                 m_RepositoryId;
        Nyx::UInt32                 m_TraceId;
        Nyx::UInt32                 m_Level;
	};
}

#endif // _TRACEDATA_HPP_
