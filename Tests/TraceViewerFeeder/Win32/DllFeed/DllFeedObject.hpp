#ifndef _DLLFEEDOBJECT_HPP_
#define _DLLFEEDOBJECT_HPP_


class CDllFeedObject
{
public:
    CDllFeedObject();
    virtual ~CDllFeedObject();

    virtual void Start();
    virtual void SendTrace();
    virtual void Stop();
};

typedef CDllFeedObject* (*PFCTAllocDllFeedObject)();

extern "C" __declspec(dllexport) CDllFeedObject* AllocDllFeedObject();

#endif // _DLLFEEDOBJECT_HPP_
