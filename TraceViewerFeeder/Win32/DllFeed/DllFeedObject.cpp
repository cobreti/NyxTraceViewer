#include <Windows.h>

#include "DllFeedObject.hpp"

#include "TraceClientLink.hpp"


CDllFeedObject* AllocDllFeedObject()
{
    return new CDllFeedObject();
}


/**
 *
 */
void CDllFeedObject::Start()
{
    CTraceClientLink::Instance().Write(L"Starting");
}


/**
 *
 */
void CDllFeedObject::SendTrace()
{
    CTraceClientLink::Instance().Write(L"Sending trace from DLL");
}


/**
 *
 */
void CDllFeedObject::Stop()
{
    CTraceClientLink::Instance().Write(L"Stopping");
}


/**
 *
 */
CDllFeedObject::CDllFeedObject()
{
}


/**
 *
 */
CDllFeedObject::~CDllFeedObject()
{
}
