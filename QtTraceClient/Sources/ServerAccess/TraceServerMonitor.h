#ifndef TRACESERVERMONITOR_H
#define TRACESERVERMONITOR_H

#include <QObject>
#include <QTimer>


class CTraceServerPortal;


class CTraceServerMonitor : public QObject
{
    Q_OBJECT

public:
    CTraceServerMonitor(CTraceServerPortal& rServerPortal);
    virtual ~CTraceServerMonitor();

    void Start();
    void Stop();

    bool active() const { return m_bActive; }

public slots:

    void onHeartbeatTimeout();
    void onHeartbeatSuccess();
    void onHeartbeatFailure();

signals:

    void connected();
    void connectionLost();

protected:

    void checkConnection();

protected:

    CTraceServerPortal&     m_rServerPortal;
    QTimer                  m_HeartbeatTimer;
    bool                    m_bActive;
};

#endif // TRACESERVERMONITOR_H
