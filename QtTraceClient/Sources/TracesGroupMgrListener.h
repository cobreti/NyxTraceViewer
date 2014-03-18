#ifndef TRACESGROUPMGRLISTENER_H
#define TRACESGROUPMGRLISTENER_H

#include "TraceClientCoreModule.hpp"

#include <QWidget>

class CTracesGroupMgrListener : public QObject
{
    Q_OBJECT

public:
    CTracesGroupMgrListener();
    virtual ~CTracesGroupMgrListener();

public slots:

signals:

    void NewTracesGroup( TraceClientCore::CTracesGroup* pGroup );

protected:

    /**
     * @brief The XListener class
     */
    class XListener : public TraceClientCore::ITracesGroupMgrNotificationsListener
    {
    public:
        XListener(CTracesGroupMgrListener* pOwner) : m_pOwner(pOwner) {}
        virtual ~XListener() {}

    public:
        virtual void OnNewTracesGroup( TraceClientCore::CTracesGroup* pGroup )
        {
            m_pOwner->OnNewTracesGroup(pGroup);
        }

        virtual void OnTracesGroupWillBeDeleted( TraceClientCore::CTracesGroup* pGroup )
        {
            m_pOwner->OnTracesGroupWillBeDeleted(pGroup);
        }

    protected:

        CTracesGroupMgrListener* m_pOwner;
    };

protected:

    virtual void OnNewTracesGroup( TraceClientCore::CTracesGroup* pGroup );
    virtual void OnTracesGroupWillBeDeleted( TraceClientCore::CTracesGroup* pGroup );

protected:

    XListener*          m_pListener;

};

#endif // TRACESGROUPMGRLISTENER_H
