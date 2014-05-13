#include "ConnectionStatusToolButton.h"


CConnectionStatusToolButton::CConnectionStatusToolButton() : QToolButton(),
    m_State(eState_NoConnection)
{

}


CConnectionStatusToolButton::~CConnectionStatusToolButton()
{

}


void CConnectionStatusToolButton::setConnectedIcon(QIcon icon)
{
    m_ConnectedIcon = icon;

    if ( m_State == eState_Connected )
    {
        setIcon(icon);
    }
}


void CConnectionStatusToolButton::setNoConnectionIcon(QIcon icon)
{
    m_NoConnectionIcon = icon;

    if ( m_State == eState_NoConnection )
    {
        setIcon(icon);
    }
}


void CConnectionStatusToolButton::setState(EState state)
{
    if ( m_State != state )
    {
        m_State = state;

        switch (m_State)
        {
        case eState_Connected:
            setIcon(m_ConnectedIcon);
            break;
        case eState_NoConnection:
            setIcon(m_NoConnectionIcon);
            break;
        };
    }
}
