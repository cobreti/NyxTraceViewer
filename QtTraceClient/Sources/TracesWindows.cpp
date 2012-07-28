#include <Nyx.hpp>

#include "TracesWindows.hpp"
#include "TracesWindow.hpp"

#include <QWidget>


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


/**
 *
 */
CTracesWindow* CTracesWindows::FindRelatedTracesWindow( QWidget* pWidget )
{
    if ( pWidget == NULL )
        return NULL;

    QWidget*                    pParent = pWidget->parentWidget();
    CTracesWindow*              pFoundWnd = NULL;
    XTracesWindowSet::iterator  pos = m_Windows.find(qobject_cast<CTracesWindow*>(pWidget));

    if ( pos == m_Windows.end() )
        pos = m_Windows.find(qobject_cast<CTracesWindow*>(pParent));

    if ( pos != m_Windows.end() )
        pFoundWnd = *pos;

    return pFoundWnd;
}


/**
 *
 */
CTracesWindow* CTracesWindows::GetTopWindow()
{
    if ( m_Windows.empty() )
        return NULL;

    return *m_Windows.begin();
}

