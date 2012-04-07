#ifndef _EXTERNALFEEDER_HPP_
#define _EXTERNALFEEDER_HPP_

#include "FeederBase.hpp"


/**
 *
 */
class CExternalFeeder : public CFeederBase
{
public:
    CExternalFeeder();
    virtual ~CExternalFeeder();

protected:

    virtual void OnBegin();
    virtual void OnEnd();
    virtual void OnSendTrace();
};


#endif // _EXTERNALFEEDER_HPP_
