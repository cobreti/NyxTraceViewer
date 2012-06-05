#include "TraceDataRepository.hpp"
#include "TraceInserter.hpp"
#include "RepositoryObserver.hpp"

#include <ctime>


/********************************************************/
/*		Repository										*/
/********************************************************/


namespace TraceClientCore
{
    /**
     *
     */
    CTraceDataRepository::CTraceDataRepository()
    {
        m_refObserversMutex = Nyx::CMutex::Alloc();
    }


    /**
     *
     */
    CTraceDataRepository::~CTraceDataRepository()
    {
    }


    /**
     *
     */
    void CTraceDataRepository::Insert(TraceClientCore::CTraceData* pTraceData)
    {
        m_Traces.push_back(pTraceData);
    }
    
    
    /**
     *
     */
    void CTraceDataRepository::Clear(const Nyx::CAString& ModuleName)
    {
        m_Traces.clear();

        {
            Nyx::TLock<Nyx::CMutex>                 ObserversLock(m_refObserversMutex, true);
            ObserverDataTable::iterator             srcPos = m_Observers.begin();
            
            while ( srcPos != m_Observers.end() )
            {
                CRepositoryObserver*    pObserver = srcPos->first;
                
                srcPos->second.StartPos() = m_Traces.end();
                pObserver->Clear(ModuleName);
                
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

        m_Observers[pObserver] = ObserverData;
    }


    /**
     *
     */
    void CTraceDataRepository::Remove(CRepositoryObserver* pObserver)
    {
        Nyx::TLock<Nyx::CMutex>     ObserversLock(m_refObserversMutex, true);

        ObserverDataTable::iterator     pos = m_Observers.find(pObserver);
        if ( pos != m_Observers.end() )
            m_Observers.erase(pos);
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
                m_ObserversToUpdate[srcPos->first] = srcPos->second;
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

        TraceDataList::const_iterator       EndPos = m_Traces.end();
        ObserverDataTable::iterator         posObserver = m_ObserversToUpdate.begin();
        clock_t                             start_clock;

        -- EndPos;

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
