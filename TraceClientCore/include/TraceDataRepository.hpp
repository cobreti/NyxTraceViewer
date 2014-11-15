#ifndef _TRACEDATAREPOSITORY_HPP_
#define _TRACEDATAREPOSITORY_HPP_

#include <Nyx.hpp>
//#include <NyxOpaqueList.hpp>
#include <list>
#include <map>

#include "TraceData.hpp"
#include "RepositoryTraceInserter.hpp"

#include <QtCore>

namespace TraceClientCore
{
    class CRepositoryObserver;

    typedef     std::list<CTraceData*>      TraceDataList;

    
    /**
	 *
	 */
	class CTraceDataRepository
	{		
	public: // public methods
		CTraceDataRepository();
		virtual ~CTraceDataRepository();
		
		virtual void Insert(TraceClientCore::CTraceData* pTraceData);
        virtual void Clear(const QString& ModuleName);
        virtual void InsertDisconnection(TraceClientCore::CTraceData* pTraceData);
        virtual void Insert(CRepositoryObserver* pObserver);
        virtual void Remove(CRepositoryObserver* pObserver);
        virtual bool Contains(CRepositoryObserver* pObserver) const;

        virtual void BeginUpdate();
        virtual void Update();
        virtual void EndUpdate();

	protected: // protected methods
	
        class XObserverData
        {
        public:
            XObserverData() : m_bEnabled(true) {}
            XObserverData(const XObserverData& data) : m_StartPos(data.m_StartPos), m_bEnabled(data.m_bEnabled) {}
            ~XObserverData() {}

            TraceDataList::const_iterator&      StartPos() { return m_StartPos; }
            
            bool&                               Enabled()   { return m_bEnabled; }
            bool                                Enabled() const     { return m_bEnabled; }

            const XObserverData& operator = (const XObserverData& data)
            {
                m_StartPos = data.m_StartPos;
                m_bEnabled = data.m_bEnabled;
                return *this;
            }

        protected:

            TraceDataList::const_iterator       m_StartPos;
            bool                                m_bEnabled;
        };


        typedef     std::map<CRepositoryObserver*, XObserverData>           ObserverDataTable;


	protected: // protected members

        TraceDataList                       m_Traces;
        ObserverDataTable                   m_Observers;
        ObserverDataTable                   m_ObserversSuspended;
        ObserverDataTable                   m_ObserversToUpdate; // map of observers used in the update process
        Nyx::CMutexRef                      m_refObserversMutex;
        Nyx::CMutexRef                      m_refTracesMutex;
        
        Nyx::UInt32                         m_RepositoryId;
        Nyx::UInt32                         m_NextTraceId;
        Nyx::UInt32                         m_LastTraceId;
        
        static Nyx::UInt32                  s_NextRepositoryId;
	};
}


#endif // _TRACEDATAREPOSITORY_HPP_
