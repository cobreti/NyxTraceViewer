#include "TraceDataRepository.hpp"
#include "TraceInserter.hpp"
#include "RepositoryObserver.hpp"

#include <ctime>


/********************************************************/
/*		Repository										*/
/********************************************************/


namespace TraceClientCore
{
    Nyx::UInt32 CTraceDataRepository::s_NextRepositoryId = 1;
    
    /**
     *
     */
    CTraceDataRepository::CTraceDataRepository() :
    m_RepositoryId( CTraceDataRepository::s_NextRepositoryId ),
    m_NextTraceId(1),
    m_LastTraceId(0)
    {
        m_refObserversMutex = Nyx::CMutex::Alloc();
        m_refTracesMutex = Nyx::CMutex::Alloc();
    }


    /**
     *
     */
    CTraceDataRepository::~CTraceDataRepository()
    {
    }


    void CTraceDataRepository::InsertDisconnection(CTraceData *pTraceData)
    {
        Nyx::TMutexLock     TracesLock(m_refTracesMutex, true);

        CTraceData* pLastTrace = m_Traces.back();
        pTraceData->TickCount() = pLastTrace->TickCount();

        Insert(pTraceData);
    }


    /**
     *
     */
    void CTraceDataRepository::Insert(TraceClientCore::CTraceData* pTraceData)
    {
        pTraceData->RepositoryId() = m_RepositoryId;
        pTraceData->TraceId() = m_NextTraceId;
        m_LastTraceId = m_NextTraceId;

        {
            Nyx::TMutexLock         TracesLock(m_refTracesMutex, true);
            
            m_Traces.push_back(pTraceData);
        }

        if ( pTraceData->Level() == 0 )
        {
            ++ m_NextTraceId;
        }
    }
    
    
    /**
     *
     */
    void CTraceDataRepository::Clear(const QString& ModuleName)
    {
        
		// notify traces are about to be cleared
        {
            Nyx::TLock<Nyx::CMutex>                 ObserversLock(m_refObserversMutex, true);
            ObserverDataTable::iterator             srcPos = m_Observers.begin();
            
            while ( srcPos != m_Observers.end() )
            {
                CRepositoryObserver*    pObserver = srcPos->first;
                
                srcPos->second.StartPos() = m_Traces.end();
                pObserver->BeginClear(ModuleName);
                
                ++ srcPos;
            }
        }

        {
            Nyx::TMutexLock         TracesLock(m_refTracesMutex, true);

            m_Traces.clear();
        }

		// notify traces have been cleared
        {
            Nyx::TLock<Nyx::CMutex>                 ObserversLock(m_refObserversMutex, true);
            ObserverDataTable::iterator             srcPos = m_Observers.begin();
            
            while ( srcPos != m_Observers.end() )
            {
                CRepositoryObserver*    pObserver = srcPos->first;
                
                srcPos->second.StartPos() = m_Traces.end();
                pObserver->EndClear(ModuleName);
                
                ++ srcPos;
            }
        }
    }


    /**
     *
     */
    void CTraceDataRepository::Insert(CRepositoryObserver* pObserver)
    {
        XObserverData       ObserverData;

        ObserverData.StartPos() = m_Traces.end();

        Nyx::TLock<Nyx::CMutex>     ObserversLock(m_refObserversMutex, true);

        ObserverDataTable::iterator     pos = m_ObserversSuspended.find(pObserver);
     
        if ( pos != m_ObserversSuspended.end() )
        {
            m_Observers[pObserver] = pos->second;
            m_ObserversSuspended.erase(pos);
        }
        else
        {
            m_Observers[pObserver] = ObserverData;
        }
    }


    /**
     *
     */
    void CTraceDataRepository::Remove(CRepositoryObserver* pObserver)
    {
        Nyx::TLock<Nyx::CMutex>     ObserversLock(m_refObserversMutex, true);

        ObserverDataTable::iterator     pos = m_Observers.find(pObserver);
        if ( pos != m_Observers.end() )
        {
            m_ObserversSuspended[pObserver] = pos->second;
//            pos->second.Enabled() = false;s
            m_Observers.erase(pos);
        }
    }


    /**
     *
     */
    bool CTraceDataRepository::Contains(CRepositoryObserver* pObserver) const
    {
        Nyx::TLock<Nyx::CMutex>     ObserversLock(m_refObserversMutex, true);

        return m_Observers.find(pObserver) != m_Observers.end();
    }


    /**
     *
     */
    void CTraceDataRepository::BeginUpdate()
    {

        //Nyx::CTraceStream(0x0).Write(L"DataRepository - BeginUpdate");

        {
            Nyx::TLock<Nyx::CMutex>     ObserversLock(m_refObserversMutex, true);
            ObserverDataTable::const_iterator       srcPos = m_Observers.begin();

            while ( srcPos != m_Observers.end() )
            {
                if ( srcPos->second.Enabled() )
                {
                    m_ObserversToUpdate[srcPos->first] = srcPos->second;
                }
                ++ srcPos;
            }
        }

        ObserverDataTable::iterator         ObserverPos = m_ObserversToUpdate.begin();
        while ( ObserverPos != m_ObserversToUpdate.end() )
        {
            ObserverPos->first->BeginUpdate();
            ++ ObserverPos;
        }
    }


    /**
     *
     */
    void CTraceDataRepository::Update()
    {
        if ( m_Traces.empty() )
            return;

        const clock_t                       kThreshold = CLOCKS_PER_SEC / 5;

        TraceDataList::const_iterator       EndPos;
        ObserverDataTable::iterator         posObserver = m_ObserversToUpdate.begin();
        clock_t                             start_clock;

        {
            Nyx::TMutexLock         TracesLock(m_refTracesMutex, true);

            EndPos = m_Traces.end();
            -- EndPos;
        }

        while ( posObserver != m_ObserversToUpdate.end() )
        {
            TraceDataList::const_iterator   pos = posObserver->second.StartPos();

            if ( pos != EndPos )
            {
                if ( pos == m_Traces.end() )
                    pos = m_Traces.begin();
                else
                    ++ pos;

                start_clock = clock();

                while ( pos != EndPos && clock() - start_clock < kThreshold )
                {
                    posObserver->first->Insert(*pos);
                    ++ pos;
                }

                posObserver->first->Insert(*pos);
                
                posObserver->second.StartPos() = pos;
            }

            ++ posObserver;
        }

        //Nyx::CTraceStream(0x0).Write(L"DataRepository - Update");
    }


    /**
     *
     */
    void CTraceDataRepository::EndUpdate()
    {
        //Nyx::CTraceStream(0x0).Write(L"DataRepository - EndUpdate");

        ObserverDataTable::iterator         ObserverPos = m_ObserversToUpdate.begin();
        while ( ObserverPos != m_ObserversToUpdate.end() )
        {
            ObserverPos->first->EndUpdate();
            ++ ObserverPos;
        }


        Nyx::TLock<Nyx::CMutex>         ObserversLock(m_refObserversMutex, true);

        while ( !m_ObserversToUpdate.empty() )
        {
            ObserverDataTable::iterator         pos = m_ObserversToUpdate.begin();
            ObserverDataTable::iterator         posObserver = m_Observers.find(pos->first);

            if ( posObserver != m_Observers.end() )
                m_Observers[pos->first] = pos->second;

            m_ObserversToUpdate.erase( pos );
        }
    }

}
