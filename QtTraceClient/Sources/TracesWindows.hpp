#ifndef _TRACESWINDOWS_H_
#define _TRACESWINDOWS_H_

#include <Nyx.hpp>

#include <set>


class CTracesWindow;
class QWidget;
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
    size_t Count() const;

    void SetListener( ITracesWindowsListener* pListener );

    const unsigned int GetWindowNo();

    CTracesWindow* FindRelatedTracesWindow( QWidget* pWidget );
    CTracesWindow* GetTopWindow();

protected:

    typedef     std::set<CTracesWindow*>       XTracesWindowSet;

protected:

    XTracesWindowSet            m_Windows;
    ITracesWindowsListener*     m_pListener;

    unsigned int                m_WindowNo;
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
