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

