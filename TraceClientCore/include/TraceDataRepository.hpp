#ifndef _TRACEDATAREPOSITORY_HPP_
#define _TRACEDATAREPOSITORY_HPP_

#include <Nyx.hpp>
//#include <NyxOpaqueList.hpp>
#include <list>
#include <map>

#include "TraceData.hpp"
#include "RepositoryTraceInserter.hpp"


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
            XObserverData() {};
            XObserverData(const XObserverData& data) : m_StartPos(data.m_StartPos) {}
            ~XObserverData() {};

            TraceDataList::const_iterator&      StartPos() { return m_StartPos; }

            const XObserverData& operator = (const XObserverData& data)
            {
                m_StartPos = data.m_StartPos;
                return *this;
            }

        protected:

            TraceDataList::const_iterator       m_StartPos;
        };


        typedef     std::map<CRepositoryObserver*, XObserverData>           ObserverDataTable;


	protected: // protected members

        TraceDataList                       m_Traces;
        ObserverDataTable                   m_Observers;
        ObserverDataTable                   m_ObserversToUpdate; // map of observers used in the update process
        Nyx::CMutexRef                      m_refObserversMutex;
	};	
}


#endif // _TRACEDATAREPOSITORY_HPP_
