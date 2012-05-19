#include <Nyx.hpp>

#include "TracesWindows.hpp"



/**
 *
 */
CTracesWindows::CTracesWindows() :
    m_pListener(NULL)
{
}


/**
 *
 */
CTracesWindows::~CTracesWindows()
{
}


/**
 *
 */
void CTracesWindows::Insert(CTracesWindow *pWindow)
{
    m_Windows.insert(pWindow);
}


/**
 *
 */
void CTracesWindows::Remove(CTracesWindow *pWindow)
{
    m_Windows.erase(pWindow);

    if ( m_pListener && m_Windows.empty() )
        m_pListener->OnTracesWindows_Empty();
}


/**
 *
 */
void CTracesWindows::SetListener(ITracesWindowsListener *pListener)
{
    m_pListener = pListener;
}
