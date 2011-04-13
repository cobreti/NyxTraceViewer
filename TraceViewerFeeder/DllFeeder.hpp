#ifndef _DLLFEEDER_HPP_
#define _DLLFEEDER_HPP_

#include "FeederBase.hpp"
#include "Win32\DllFeed\DllFeedObject.hpp"

class CDllFeeder : public CFeederBase
{
public:
    CDllFeeder();
    virtual ~CDllFeeder();

protected:
    virtual void OnBegin();
    virtual void OnEnd();
    virtual void OnSendTrace();

protected:

    HINSTANCE           m_hDllInstance;
    CDllFeedObject*     m_pFeedObject;
};


#endif // _DLLFEEDER_HPP_
