#ifndef _TRACESWINDOWS_H_
#define _TRACESWINDOWS_H_

#include <set>


class CTracesWindow;
class ITracesWindowsListener;


/**
 *
 */
class CTracesWindows
{
public:
    CTracesWindows();
    virtual ~CTracesWindows();

    void Insert( CTracesWindow* pWindow );
    void Remove( CTracesWindow* pWindow );

    void SetListener( ITracesWindowsListener* pListener );

protected:

    typedef     std::set<CTracesWindow*>       XTracesWindowSet;

protected:

    XTracesWindowSet            m_Windows;
    ITracesWindowsListener*     m_pListener;
};


/**
 *
 */
class ITracesWindowsListener
{
public:

    virtual void OnTracesWindows_Empty() = 0;
};



#endif // _TRACESWINDOWS_H_
