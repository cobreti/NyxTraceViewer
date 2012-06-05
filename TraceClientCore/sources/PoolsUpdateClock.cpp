#include "PoolsUpdateClock.hpp"
#include "TracesPoolCollection.hpp"


namespace TraceClientCore
{
    /**
     *
     */
    CPoolsUpdateClock::CPoolsUpdateClock() :
    m_bRunning(false)
    {
        m_refThread = Nyx::CThread::Alloc();
        m_refMutex = Nyx::CMutex::Alloc();
        m_refEvent = Nyx::CEvent::Alloc();
    }


    /**
     *
     */
    CPoolsUpdateClock::~CPoolsUpdateClock()
    {
        Stop();
    }


    /**
     *
     */
    void CPoolsUpdateClock::Start()
    {
        if ( m_refThread->IsRunning())
            return;

        m_refThread->Start( new Nyx::CThreadDelegateNoRef<CPoolsUpdateClock>(this, &CPoolsUpdateClock::ThreadRun, &CPoolsUpdateClock::ThreadStop));
    }


    /**
     *
     */
    void CPoolsUpdateClock::Stop()
    {
        m_bRunning = false;
        m_refThread->Stop();
    }


    /**
     *
     */
    void CPoolsUpdateClock::Insert( CTracesPool* pPool )
    {
        Nyx::TLock<Nyx::CMutex>         lock(m_refMutex, true);

        m_Pools.push_back(pPool);
    }


    /**
     *
     */
    void CPoolsUpdateClock::Remove( CTracesPool* pPool )
    {
        Nyx::TLock<Nyx::CMutex>         lock(m_refMutex, true);

        PoolsList::iterator     pos = m_Pools.begin();

        while ( pos != m_Pools.end() )
        {
            if ( *pos == pPool )
            {
                m_Pools.erase(pos);
                pos = m_Pools.begin();
            }
            else
                ++ pos;
        }
    }


    /**
     *
     */
    void CPoolsUpdateClock::ThreadRun()
    {
        Nyx::NyxResult          res;
        m_bRunning = true;
        while ( m_bRunning )
        {
            PoolsList               pools;

            {
                Nyx::TLock<Nyx::CMutex>     PoolsLock(m_refMutex, true);

                pools = m_Pools;

                PoolsList::iterator     pos;

                for ( pos = pools.begin(); pos != pools.end(); ++pos)
                    (*pos)->Repository().BeginUpdate();

                for ( pos = pools.begin(); pos != pools.end(); ++pos)
                    (*pos)->Repository().Update();

                for ( pos = pools.begin(); pos != pools.end(); ++pos)
                    (*pos)->Repository().EndUpdate();
            }

            res = m_refEvent->WaitSignaled(1000);
        }
    }


    /**
     *
     */
    void CPoolsUpdateClock::ThreadStop()
    {
        m_bRunning = false;
        m_refEvent->Signal(0);
    }
}
