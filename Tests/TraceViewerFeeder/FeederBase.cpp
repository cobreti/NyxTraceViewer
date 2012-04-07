#include "FeederBase.hpp"
#include "FeederSettings.hpp"


/**
 *
 */
CFeederBase::CFeederBase() :
    m_bIsRunning(false),
    m_pSettings(NULL)
{
    m_refEvent = Nyx::CEvent::Alloc();
    m_refThread = Nyx::CThread::Alloc();
}


/**
 *
 */
CFeederBase::~CFeederBase()
{
}


/**
 *
 */
void CFeederBase::Start(const CFeederSettings& settings)
{
    m_pSettings = &settings;

    m_bIsRunning = true;
    m_refThread->Start( new Nyx::CThreadDelegateNoRef<CFeederBase>(this, 
        &CFeederBase::RunningLoop, &CFeederBase::StopProc ) );
}


/**
 *
 */
void CFeederBase::Stop()
{
    m_refThread->Stop();
}


/**
 *
 */
bool CFeederBase::IsRunning() const
{
    return m_bIsRunning;
}


/**
 *
 */
void CFeederBase::RunningLoop()
{
    OnBegin();

    while (m_bIsRunning)
    {
        for ( size_t count = 0; count < Settings().TracesPerBlock(); ++ count )
            OnSendTrace();

        m_refEvent->WaitSignaled(Settings().IntervalBetweenBlocks());
    }

    OnEnd();
}


/**
 *
 */
void CFeederBase::StopProc()
{
    m_bIsRunning = false;
    m_refEvent->Signal(0);
}

