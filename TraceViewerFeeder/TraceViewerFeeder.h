#ifndef TRACEVIEWERFEEDER_H
#define TRACEVIEWERFEEDER_H

#include <QtGui/QMainWindow>
#include "ui_traceviewerfeeder.h"
#include "FeederSource_UserText.hpp"
#include "FeederSource_TextFile.hpp"


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
    void OnUseTextClicked();
    void OnUseFilenameClicked();
    void OnBrowseForFile();

protected:

protected:

    void InitDetailsPanel( CFeederEntry* pEntry );
    void EnableUserTextSection( bool bEnable );
    void EnableFilenameSection( bool bEnable );

private:
    Ui::CTraceViewerFeederClass ui;

    CFeederSource_UserText*      m_pUserTextFeeder;
    CFeederSource_TextFile*      m_pTextFileFeeder;
};


#endif // TRACEVIEWERFEEDER_H
