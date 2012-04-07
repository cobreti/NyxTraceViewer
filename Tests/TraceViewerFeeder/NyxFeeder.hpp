#ifndef _NYXFEEDER_HPP_
#define _NYXFEEDER_HPP_

#include <Nyx.hpp>
#include "FeederBase.hpp"


/**
 *
 */
class CNyxFeeder : public CFeederBase
{
public:
    CNyxFeeder();
    virtual ~CNyxFeeder();

protected:

    virtual void OnBegin();
    virtual void OnEnd();
    virtual void OnSendTrace();

protected:

//    virtual void ReadSourceFile();

protected:

    Nyx::CTraceCompositorRef        m_refTraceCompositor;
    int                             m_Index;
};


#endif // _NYXFEEDER_HPP_
