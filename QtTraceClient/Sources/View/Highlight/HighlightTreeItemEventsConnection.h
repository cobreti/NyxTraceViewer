#ifndef _CHIGHLIGHTTREEITEMEVENTSCONNECTION_HPP_
#define _CHIGHLIGHTTREEITEMEVENTSCONNECTION_HPP_

#include <QObject>

class CHighlightTreeItem;
class CColorBtn;

/**
 *
 */
class CHighlightTreeItemEventsConnection : public QObject
{
    Q_OBJECT

public:
    CHighlightTreeItemEventsConnection(CHighlightTreeItem* pOwner);
    virtual ~CHighlightTreeItemEventsConnection();

public slots:

    void OnColorChanged(CColorBtn* pBtn);

protected:

    CHighlightTreeItem*     m_pOwner;
};


#endif // _CHIGHLIGHTTREEITEMEVENTSCONNECTION_HPP_
