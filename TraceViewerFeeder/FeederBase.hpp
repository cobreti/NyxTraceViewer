#ifndef _FEEDERBASE_HPP_
#define _FEEDERBASE_HPP_

#include <Nyx.hpp>


DECLARE_OBJECTREF(CFeederBase);

class CFeederSettings;

/**
 *
 */
class CFeederBase
{
public:
    CFeederBase();
    virtual ~CFeederBase();

    virtual void Start(const CFeederSettings& settings);
    virtual void Stop();
    virtual bool IsRunning() const;

    const CFeederSettings& Settings() const     { return *m_pSettings; }

protected:

    virtual void RunningLoop();
    virtual void StopProc();

    virtual void OnBegin() = 0;
    virtual void OnEnd() = 0;
    virtual void OnSendTrace() = 0;

protected:

    Nyx::CThreadRef             m_refThread;
    Nyx::CEventRef              m_refEvent;
    bool                        m_bIsRunning;
    const CFeederSettings*      m_pSettings;
};

#endif // _FEEDERBASE_HPP_

