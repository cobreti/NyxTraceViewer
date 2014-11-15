#ifndef _TRACEDATA_HPP_
#define _TRACEDATA_HPP_

#include <Nyx.hpp>
#include <NyxRefCount_Impl.hpp>
#include <NyxMemPoolObj.hpp>
#include <NyxMemPoolWString.hpp>
#include <NyxNetTraceFlags.hpp>

#include <QtCore>

namespace TraceClientCore
{
    class CTraceChannel;
	
    class CTraceData// : public Nyx::CMemPoolObj<>
	{
//		typedef		Nyx::CMemPoolObj<>		BaseType;

    public:

        class CIdentifier
        {
        public:
            CIdentifier();
            CIdentifier(quint32 repositoryId, quint32 traceId, quint32 level);
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

            quint32     m_RepositoryId;
            quint32     m_TraceId;
            quint32     m_Level;
        };

        enum ETraceType
        {
            eTT_User,
            eTT_ConnectionStatus_Connection,
            eTT_ConnectionStatus_Disconnection
        };

	public:
        CTraceData();
		virtual ~CTraceData();
				
        const QString& TimeReference() const	{ return m_TimeReference; }
        QString& TimeReference()				{ return m_TimeReference; }

        const QString& TickCountReference() const		{ return m_TickCountReference; }
        QString& TickCountReference()					{ return m_TickCountReference; }

        const QString& ThreadId() const		{ return m_ThreadId; }
        QString& ThreadId()					{ return m_ThreadId; }
		
        const QString& TickCount() const		{ return m_TickCount; }
        QString& TickCount()					{ return m_TickCount; }
		
        const QString& Data() const			{ return m_Data; }
        QString& Data()						{ return m_Data; }

        const ETraceType& Type() const                      { return m_eType; }
        ETraceType& Type()                                  { return m_eType; }
        
        const NyxNet::CTraceFlags& Flags() const            { return m_Flags; }
        NyxNet::CTraceFlags& Flags()                        { return m_Flags; }
        
        const quint32& RepositoryId() const             { return m_RepositoryId; }
        quint32& RepositoryId()                         { return m_RepositoryId; }
        
        const quint32& TraceId() const                  { return m_TraceId; }
        quint32& TraceId()                              { return m_TraceId; }

        const quint32& Level() const                    { return m_Level; }
        quint32& Level()                                { return m_Level; }

        CTraceChannel*& Channel()                       { return m_pOwnerTraceChannel; }
        CTraceChannel* Channel() const                  { return m_pOwnerTraceChannel; }

        const CIdentifier identifier() const                { return CIdentifier(m_RepositoryId, m_TraceId, m_Level); }
		
	protected:
	
        QString        m_TimeReference;
        QString        m_TickCountReference;

        QString		m_ThreadId;
        QString		m_TickCount;
        QString		m_Data;
        ETraceType					m_eType;
        NyxNet::CTraceFlags         m_Flags;
        quint32                 m_RepositoryId;
        quint32                 m_TraceId;
        quint32                 m_Level;
        CTraceChannel*          m_pOwnerTraceChannel;
	};
}

#endif // _TRACEDATA_HPP_
