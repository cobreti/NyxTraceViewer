#include "TraceViewerFeeder.h"
#include "FeederEntryWidgetItem.hpp"

#include <Nyx.hpp>

/**
 *
 */
CTraceViewerFeeder::CTraceViewerFeeder(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
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

    ui.btnAddChannel->setEnabled(true);
    ui.btnRemoveChannel->setEnabled(false);

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
        //feeder.Settings().Text() = Nyx::CString::Alloc( ui.editTraceText->toPlainText().toStdWString().c_str() );
        //feeder.Settings().Frequency() = ui.FrequencySpinBox->value();
        //feeder.Settings().Name() = Nyx::CString::Alloc( pItem->text().toStdWString().c_str() );
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

    settings.Text() = ui.editTraceText->toPlainText().toStdWString().c_str();
    settings.TracesPerBlock() = ui.TracesPerBlockSpinBox->value();
    settings.IntervalBetweenBlocks() = ui.IntervalBetweenBlocksSpinBox->value();
    settings.Name() = pItem->text().toStdWString().c_str();

    if ( ui.btnNyxAPISource->isChecked() )
        settings.ApiType() = CFeederSettings::eTAPI_Nyx;
    else if ( ui.btnExternalAPISource->isChecked() )
        settings.ApiType() = CFeederSettings::eTAPI_External;
    else if ( ui.btnDllSource->isChecked() )
        settings.ApiType() = CFeederSettings::eTAPI_Dll;
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

    if ( pCurrent )
    {
        ui.btnRemoveChannel->setEnabled(true);

        CFeederEntryWidgetItem*     pItem = static_cast<CFeederEntryWidgetItem*>(pCurrent);
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
void CTraceViewerFeeder::InitDetailsPanel(CFeederEntry *pEntry)
{
    bool        bFieldsEnabled = (pEntry != NULL);

    ui.btnStartStop->setText("Start");

    if ( pEntry )
    {
        ui.TracesPerBlockSpinBox->setValue(pEntry->Settings().TracesPerBlock());
        ui.IntervalBetweenBlocksSpinBox->setValue(pEntry->Settings().IntervalBetweenBlocks());

        switch (pEntry->Settings().ApiType())
        {
        case CFeederSettings::eTAPI_Nyx:
            ui.btnNyxAPISource->setChecked(true);
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
        ui.btnNyxAPISource->setChecked(false);
        ui.btnExternalAPISource->setChecked(false);
        ui.btnDllSource->setChecked(false);
        ui.TracesPerBlockSpinBox->setValue(0);
        ui.IntervalBetweenBlocksSpinBox->setValue(1000);
        ui.editTraceText->clear();
        ui.btnStartStop->setEnabled(false);
    }

    ui.TracesPerBlockSpinBox->setEnabled(bFieldsEnabled);
    ui.IntervalBetweenBlocksSpinBox->setEnabled(bFieldsEnabled);
    ui.btnNyxAPISource->setEnabled(bFieldsEnabled);
#if defined(WIN32)
    ui.btnExternalAPISource->setEnabled(bFieldsEnabled);
    ui.btnDllSource->setEnabled(bFieldsEnabled);
#else
    ui.btnExternalAPISource->setEnabled(false);
    ui.btnDllSource->setEnabled(false);
#endif
    ui.editTraceText->setEnabled(bFieldsEnabled);
}
