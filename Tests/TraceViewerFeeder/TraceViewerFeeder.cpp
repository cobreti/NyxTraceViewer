#include "TraceViewerFeeder.h"
#include "FeederEntryWidgetItem.hpp"

#include <Nyx.hpp>
#include <QFileDialog>

/**
 *
 */
CTraceViewerFeeder::CTraceViewerFeeder(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags),
      m_pUserTextFeeder(NULL),
      m_pTextFileFeeder(NULL)
{
    ui.setupUi(this);

    connect(    ui.btnAddChannel, SIGNAL(clicked()), 
                this, SLOT(OnAddFeeder()));
    connect(    ui.ChannelsName, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
                this, SLOT(OnChannelSelectionChanged(QListWidgetItem*, QListWidgetItem*)) );
    connect(    ui.btnRemoveChannel, SIGNAL(clicked()),
                this, SLOT(OnRemoveFeeder()));
    connect(    ui.btnStartStop, SIGNAL(clicked()),
                this, SLOT(OnStartStopFeeder()));
    connect(    ui.m_cbUseText, SIGNAL(clicked()),
                this, SLOT(OnUseTextClicked()) );
    connect(    ui.m_cbUseFile, SIGNAL(clicked()),
                this, SLOT(OnUseFilenameClicked()));
    connect(    ui.m_btnBrowseFile, SIGNAL(clicked()),
                this, SLOT(OnBrowseForFile()));
    connect(    ui.btnNyxPipeAPISource, SIGNAL(clicked()),
                this, SLOT(OnNyxPipeClicked()));
    connect(    ui.btnNyxTcpIpAPISource, SIGNAL(clicked()),
                this, SLOT(OnNyxTcpIpClicked()));
    connect(    ui.btnExternalAPISource, SIGNAL(clicked()),
                this, SLOT(OnExternalClicked()));
    connect(    ui.btnDllSource, SIGNAL(clicked()),
                this, SLOT(OnDllFeederClicked()));

    ui.btnAddChannel->setEnabled(true);
    ui.btnRemoveChannel->setEnabled(false);

    ui.m_cbUseText->setChecked(true);

    InitDetailsPanel(NULL);
}


/**
 *
 */
CTraceViewerFeeder::~CTraceViewerFeeder()
{

}


/**
 *
 */
void CTraceViewerFeeder::OnAddFeeder()
{
    CFeederEntryWidgetItem*     pItem = new CFeederEntryWidgetItem("new channel");

    pItem->setFlags( Qt::ItemIsEditable | pItem->flags() );
    pItem->SetFeederEntry( new CFeederEntry() );

    pItem->GetFeederEntry()->Settings().Name() = L"new channel";
    pItem->setForeground( QBrush(QColor(150, 0, 0)) );

    ui.ChannelsName->addItem(pItem);
}


/**
 *
 */
void CTraceViewerFeeder::OnRemoveFeeder()
{
    QListWidgetItem*    pItem = ui.ChannelsName->currentItem();

    delete pItem;
}


/**
 *
 */
void CTraceViewerFeeder::OnStartStopFeeder()
{
    CFeederEntryWidgetItem*         pItem = static_cast<CFeederEntryWidgetItem*>(ui.ChannelsName->currentItem());
    CFeederEntry&                   feeder = *pItem->GetFeederEntry();

    if ( feeder.IsRunning() )
    {
        feeder.Stop();
        pItem->setFlags( pItem->flags() | Qt::ItemIsEditable );
        pItem->setForeground( QBrush(QColor(150, 0, 0)) );
    }
    else
    {
        SaveSettings(pItem, feeder.Settings());

        feeder.Start();
        pItem->setFlags( pItem->flags() & ~Qt::ItemIsEditable );
        pItem->setForeground( QBrush(QColor(0, 150, 0)) );
    }

    InitDetailsPanel(&feeder);
}


/**
 *
 */
void CTraceViewerFeeder::SaveSettings(CFeederEntryWidgetItem* pItem, CFeederSettings& settings)
{
    if ( pItem->GetFeederEntry()->IsRunning() )
        return;

    if ( m_pUserTextFeeder )
        m_pUserTextFeeder->SetText( ui.editTraceText->toPlainText().toStdWString().c_str());

    settings.Text() = ui.editTraceText->toPlainText().toStdWString().c_str();
    settings.TracesPerBlock() = ui.TracesPerBlockSpinBox->value();
    settings.IntervalBetweenBlocks() = ui.IntervalBetweenBlocksSpinBox->value();
    settings.Name() = pItem->text().toStdWString().c_str();

    if ( ui.btnNyxPipeAPISource->isChecked() )
        settings.ApiType() = CFeederSettings::eTAPI_NyxPipe;
    else if ( ui.btnNyxTcpIpAPISource->isChecked() )
    {
        settings.ApiType() = CFeederSettings::eTAPI_NyxTcpIp;
        settings.TcpIpAddress() = ui.editTcpIpAddress->text().toStdString().c_str();
        settings.PortNumber() = ui.editPortNumber->text().toInt();
    }
    else if ( ui.btnExternalAPISource->isChecked() )
        settings.ApiType() = CFeederSettings::eTAPI_External;
    else if ( ui.btnDllSource->isChecked() )
        settings.ApiType() = CFeederSettings::eTAPI_Dll;

    settings.FeederSource() = NULL;

    if ( ui.m_cbUseText->isChecked() )
    {
        settings.FeederSource() = m_pUserTextFeeder;
    }
    else if ( ui.m_cbUseFile->isChecked() )
    {
        settings.FeederSource() = m_pTextFileFeeder;
    }
}


/**
 *
 */
void CTraceViewerFeeder::OnChannelSelectionChanged(QListWidgetItem* pCurrent, QListWidgetItem* pPrevious)
{
    if ( pPrevious )
    {
        CFeederEntryWidgetItem* pItem = static_cast<CFeederEntryWidgetItem*>(pPrevious);
        SaveSettings(pItem, pItem->GetFeederEntry()->Settings() );
    }

    m_pTextFileFeeder = NULL;
    m_pUserTextFeeder = NULL;

    if ( pCurrent )
    {
        CFeederEntryWidgetItem* pItem = static_cast<CFeederEntryWidgetItem*>(pCurrent);
        ui.btnRemoveChannel->setEnabled(true);

        if ( !pItem->GetFeederEntry()->IsRunning() )
        {
            m_pTextFileFeeder = &pItem->GetTextFileFeeder();
            m_pUserTextFeeder = &pItem->GetUserTextFeeder();
        }

        InitDetailsPanel(pItem->GetFeederEntry());
    }
    else
    {
        ui.btnRemoveChannel->setEnabled(false);
        InitDetailsPanel(NULL);
    }
}


/**
 *
 */
void CTraceViewerFeeder::OnUseTextClicked()
{
    ui.m_cbUseText->setChecked(true);
    ui.m_cbUseFile->setChecked(false);

    EnableUserTextSection(true);
    EnableFilenameSection(true);
}


/**
 *
 */
void CTraceViewerFeeder::OnUseFilenameClicked()
{
    ui.m_cbUseText->setChecked(false);
    ui.m_cbUseFile->setChecked(true);

    EnableUserTextSection(true);
    EnableFilenameSection(true);
}


/**
 *
 */
void CTraceViewerFeeder::OnNyxPipeClicked()
{
    ui.editTcpIpAddress->setEnabled(false);
    ui.editPortNumber->setEnabled(false);
}


/**
 *
 */
void CTraceViewerFeeder::OnNyxTcpIpClicked()
{
    ui.editTcpIpAddress->setEnabled(true);
    ui.editPortNumber->setEnabled(true);
}


/**
 *
 */
void CTraceViewerFeeder::OnExternalClicked()
{
    ui.editTcpIpAddress->setEnabled(false);
    ui.editPortNumber->setEnabled(false);
}


/**
 *
 */
void CTraceViewerFeeder::OnDllFeederClicked()
{
    ui.editTcpIpAddress->setEnabled(false);
    ui.editPortNumber->setEnabled(false);
}


/**
 *
 */
void CTraceViewerFeeder::OnBrowseForFile()
{
    QString         filename = QFileDialog::getOpenFileName(this);

    if ( !filename.isEmpty() )
    {
        ui.m_editFilename->setText(filename);
        m_pTextFileFeeder->SetFile(filename.toStdString().c_str());
    }
}


/**
 *
 */
void CTraceViewerFeeder::InitDetailsPanel(CFeederEntry *pEntry)
{
    bool        bFieldsEnabled = (pEntry != NULL);

    ui.btnStartStop->setText("Start");

    ui.editTcpIpAddress->setEnabled(false);
    ui.editPortNumber->setEnabled(false);

    if ( pEntry )
    {
        ui.TracesPerBlockSpinBox->setValue(pEntry->Settings().TracesPerBlock());
        ui.IntervalBetweenBlocksSpinBox->setValue(pEntry->Settings().IntervalBetweenBlocks());

        switch (pEntry->Settings().ApiType())
        {
        case CFeederSettings::eTAPI_NyxPipe:
            ui.btnNyxPipeAPISource->setChecked(true);
            break;
        case CFeederSettings::eTAPI_NyxTcpIp:
            ui.btnNyxTcpIpAPISource->setChecked(true);
            ui.editTcpIpAddress->setEnabled(true);
            ui.editTcpIpAddress->setText( pEntry->Settings().TcpIpAddress().c_str() );
            ui.editPortNumber->setEnabled(true);
            ui.editPortNumber->setText( QString::number(pEntry->Settings().PortNumber()));
            break;
        case CFeederSettings::eTAPI_External:
            ui.btnExternalAPISource->setChecked(true);
            break;
        case CFeederSettings::eTAPI_Dll:
            ui.btnDllSource->setChecked(true);
            break;
        };


        QString     Text;
        Text = QString().fromWCharArray(pEntry->Settings().Text().c_str());

        ui.editTraceText->setPlainText( Text );

        bFieldsEnabled = !pEntry->IsRunning();

        ui.btnStartStop->setEnabled(true);
        if ( pEntry->IsRunning() )
        {
            ui.btnStartStop->setText("Stop");
        }
        else
        {
            ui.btnStartStop->setText("Start");
        }
    }
    else
    {
        ui.btnNyxPipeAPISource->setChecked(false);
        ui.btnNyxTcpIpAPISource->setChecked(false);
        ui.btnExternalAPISource->setChecked(false);
        ui.btnDllSource->setChecked(false);
        ui.TracesPerBlockSpinBox->setValue(0);
        ui.IntervalBetweenBlocksSpinBox->setValue(1000);
        ui.editTraceText->clear();
        ui.btnStartStop->setEnabled(false);
    }

    ui.TracesPerBlockSpinBox->setEnabled(bFieldsEnabled);
    ui.IntervalBetweenBlocksSpinBox->setEnabled(bFieldsEnabled);
    ui.btnNyxPipeAPISource->setEnabled(bFieldsEnabled);
    ui.btnNyxTcpIpAPISource->setEnabled(bFieldsEnabled);
    ui.btnExternalAPISource->setEnabled(bFieldsEnabled);

#if defined(WIN32)
    ui.btnDllSource->setEnabled(bFieldsEnabled);
#else
//    ui.btnExternalAPISource->setEnabled(false);
    ui.btnDllSource->setEnabled(false);
#endif
    ui.editTraceText->setEnabled(bFieldsEnabled);

    EnableUserTextSection(bFieldsEnabled);
    EnableFilenameSection(bFieldsEnabled);
    ui.m_cbUseFile->setEnabled(bFieldsEnabled);
    ui.m_cbUseText->setEnabled(bFieldsEnabled);
}


/**
 *
 */
void CTraceViewerFeeder::EnableUserTextSection( bool bEnable )
{
    ui.editTraceText->setEnabled(bEnable && ui.m_cbUseText->isChecked());
}


/**
 *
 */
void CTraceViewerFeeder::EnableFilenameSection( bool bEnable )
{
    bool bChecked = ui.m_cbUseFile->isChecked();

    ui.m_editFilename->setEnabled( bEnable && bChecked );
    ui.m_btnBrowseFile->setEnabled( bEnable && bChecked );
}
