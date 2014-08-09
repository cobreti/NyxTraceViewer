#ifndef CONNECTIONSTATUSTOOLBUTTON_H
#define CONNECTIONSTATUSTOOLBUTTON_H


#include <QToolButton>


class CConnectionStatusToolButton : public QToolButton
{
    Q_OBJECT

public:

    enum EState
    {
        eState_Connected,
        eState_NoConnection
    };

public:
    CConnectionStatusToolButton();
    virtual ~CConnectionStatusToolButton();

    void setConnectedIcon(QIcon icon);
    void setNoConnectionIcon(QIcon icon);

    void setState(EState state);

    EState state() const        { return m_State; }

protected:

    QIcon       m_ConnectedIcon;
    QIcon       m_NoConnectionIcon;
    EState      m_State;
};


#endif // CONNECTIONSTATUSTOOLBUTTON_H
