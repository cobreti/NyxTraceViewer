#ifndef TOGGLETOOLBUTTON_H
#define TOGGLETOOLBUTTON_H

#include <QToolButton>



class CToggleToolButton : public QToolButton
{
    Q_OBJECT

public:

    enum EState
    {
        eState_Normal,
        eState_Selected
    };

public:
    CToggleToolButton();
    virtual ~CToggleToolButton();

    void setNormalIcon( QIcon icon );
    void setSelectedIcon( QIcon icon );

    void setState( EState state );

    const EState state() const { return m_State; }

public slots:

    void onClicked();

signals:

    void stateChanged(CToggleToolButton::EState state);

protected:

    QIcon           m_NormalIcon;
    QIcon           m_SelectedIcon;
    EState          m_State;
};


#endif // TOGGLETOOLBUTTON_H
