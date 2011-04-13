#ifndef _FEEDERENTRY_HPP_
#define _FEEDERENTRY_HPP_

#include <Nyx.hpp>
#include "FeederSettings.hpp"

DECLARE_OBJECTREF(CFeederEntry)

class CFeederBase;

/**
 *
 */
class CFeederEntry : public Nyx::CRefCount_Impl<>
{
public:
    CFeederEntry();
    virtual ~CFeederEntry();

    const CFeederSettings&      Settings() const        { return m_Settings; }
    CFeederSettings&            Settings()              { return m_Settings; }

    void Start();
    void Stop();

    bool IsRunning() const;

protected:

    CFeederSettings         m_Settings;
    CFeederBase*            m_pFeeder;
};


#endif // _FEEDERENTRY_HPP_
