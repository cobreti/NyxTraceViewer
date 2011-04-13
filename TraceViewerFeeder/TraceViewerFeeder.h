#ifndef TRACEVIEWERFEEDER_H
#define TRACEVIEWERFEEDER_H

#include <QtGui/QMainWindow>
#include "ui_traceviewerfeeder.h"

class CFeederEntry;
class CFeederSettings;
class CFeederEntryWidgetItem;

/**
 *
 */
class CTraceViewerFeeder : public QMainWindow
{
    Q_OBJECT

public:
    CTraceViewerFeeder(QWidget *parent = 0, Qt::WFlags flags = 0);
    virtual ~CTraceViewerFeeder();

public slots:

    void OnAddFeeder();
    void OnRemoveFeeder();
    void OnStartStopFeeder();
    void SaveSettings( CFeederEntryWidgetItem* pItem, CFeederSettings& settings );
    void OnChannelSelectionChanged( QListWidgetItem* pCurrent, QListWidgetItem* pPrevious );

protected:

protected:

    void InitDetailsPanel( CFeederEntry* pEntry );

private:
    Ui::CTraceViewerFeederClass ui;
};


#endif // TRACEVIEWERFEEDER_H
