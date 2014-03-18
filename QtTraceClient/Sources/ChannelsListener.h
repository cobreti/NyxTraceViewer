#ifndef CHANNELSLISTENER_H
#define CHANNELSLISTENER_H

#include "TraceClientCoreModule.hpp"

#include <QWidget>

/**
 * @brief The CChannelsListener class
 */
class CChannelsListener : public QObject
{
    Q_OBJECT

public:
    CChannelsListener();
    virtual ~CChannelsListener();

public slots:

signals:

    void newChannel(TraceClientCore::CTraceChannel* pChannel);

protected:

    /**
     * @brief The XListener class
     */
    class XListener : public TraceClientCore::IChannelsNotificationsListener
    {
    public:
        XListener(CChannelsListener* pOwner) : m_pOwner(pOwner) {}
        virtual ~XListener() {}

    public:
        virtual void OnNewChannel( TraceClientCore::CTraceChannel* pChannel )
        {
            m_pOwner->OnNewChannel(pChannel);
        }

    protected:

        CChannelsListener* m_pOwner;
    };

protected:

    virtual void OnNewChannel( TraceClientCore::CTraceChannel* pChannel );

protected:

    XListener*          m_pListener;

};


#endif // CHANNELSLISTENER_H
