#ifndef TRACESGROUPNOTIFICATIONSLISTENER_H
#define TRACESGROUPNOTIFICATIONSLISTENER_H


#include "TracesGroup.hpp"

#include <QObject>

class CTracesGroupNotificationsListener : public QObject
{
    Q_OBJECT

public:
    CTracesGroupNotificationsListener();
    virtual ~CTracesGroupNotificationsListener();

    void ConnectTo( TraceClientCore::CTracesGroup* pGroup );
    void Disconnect();

public slots:

signals:

    void ViewBeginUpdate( TraceClientCore::CTracesGroup* pGroup, TraceClientCore::CTracesView* pView );
    void ViewEndUpdate( TraceClientCore::CTracesGroup* pGroup, TraceClientCore::CTracesView* pView );

protected:

    class XListener : public TraceClientCore::ITracesGroupNotificationsListener
    {
    public:
        XListener(CTracesGroupNotificationsListener* pOwner) : m_pOwner(pOwner) {}
        ~XListener() {}

    public:
        virtual void OnViewBeginUpdate( TraceClientCore::CTracesGroup* pGroup, TraceClientCore::CTracesView* pView )
        {
            m_pOwner->OnViewBeginUpdate(pGroup, pView);
        }

        virtual void OnViewEndUpdate( TraceClientCore::CTracesGroup* pGroup, TraceClientCore::CTracesView* pView )
        {
            m_pOwner->OnViewEndUpdate(pGroup, pView);
        }

    protected:

        CTracesGroupNotificationsListener* m_pOwner;
    };

protected:

    virtual void OnViewBeginUpdate( TraceClientCore::CTracesGroup* pGroup, TraceClientCore::CTracesView* pView );
    virtual void OnViewEndUpdate( TraceClientCore::CTracesGroup* pGroup, TraceClientCore::CTracesView* pView );

protected:

    XListener                           m_Listener;
    TraceClientCore::CTracesGroup*      m_pTracesGroup;
};


#endif // TRACESGROUPNOTIFICATIONSLISTENER_H
