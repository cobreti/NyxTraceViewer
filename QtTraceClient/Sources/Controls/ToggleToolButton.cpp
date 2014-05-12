#include "ToggleToolButton.h"


CToggleToolButton::CToggleToolButton() : QToolButton(),
    m_State(eState_Normal)
{
    connect(this, SIGNAL(clicked()), this, SLOT(onClicked()));
}


CToggleToolButton::~CToggleToolButton()
{

}


void CToggleToolButton::setNormalIcon(QIcon icon)
{
    m_NormalIcon = icon;
    setIcon(icon);
}


void CToggleToolButton::setSelectedIcon(QIcon icon)
{
    m_SelectedIcon = icon;
}


void CToggleToolButton::setState(EState state)
{
    if ( m_State != state )
    {
        m_State = state;

        switch (m_State)
        {
        case eState_Normal:
            setIcon(m_NormalIcon);
            break;

        case eState_Selected:
            setIcon(m_SelectedIcon);
            break;
        }

        emit stateChanged(m_State);
    }
}


void CToggleToolButton::onClicked()
{
    switch (m_State)
    {
    case eState_Normal:
        setIcon(m_SelectedIcon);
        m_State = eState_Selected;
        break;

    case eState_Selected:
        setIcon(m_NormalIcon);
        m_State = eState_Normal;
        break;
    }

    emit stateChanged(m_State);
}

