#include <Nyx.hpp>

#include "TracesWindows.hpp"



/**
 *
 */
CTracesWindows::CTracesWindows() :
    m_pListener(NULL),
    m_WindowNo(0)
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
size_t CTracesWindows::Count() const
{
    return m_Windows.size();
}


/**
 *
 */
void CTracesWindows::SetListener(ITracesWindowsListener *pListener)
{
    m_pListener = pListener;
}


/**
 *
 */
const unsigned int CTracesWindows::GetWindowNo()
{
    return ++m_WindowNo;
}

