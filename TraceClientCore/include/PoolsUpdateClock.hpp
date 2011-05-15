#ifndef _POOLSUPDATECLOCK_HPP_
#define _POOLSUPDATECLOCK_HPP_

#include <Nyx.hpp>
#include <list>

namespace TraceClientCore
{
    class CTracesPool;

    class CPoolsUpdateClock
    {
    public:
        CPoolsUpdateClock();
        virtual ~CPoolsUpdateClock();

        virtual void Start();
        virtual void Stop();

        virtual void Insert( CTracesPool* pPool );
        virtual void Remove( CTracesPool* pPool );

    protected:

        virtual void ThreadRun();
        virtual void ThreadStop();
        
    protected:

        typedef     std::list<CTracesPool*>         PoolsList;

    protected:

        PoolsList                   m_Pools;
        Nyx::CThreadRef             m_refThread;
        Nyx::CMutexRef              m_refMutex;
        Nyx::CEventRef              m_refEvent;
        bool                        m_bRunning;
    };
}


#endif // _POOLSUPDATECLOCK_HPP_
