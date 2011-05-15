#include <QtGui>

#include "DebugPanel.h"
#include "ui_DebugPanel.h"

#include "TraceClientCoreModule.hpp"
#include "DbgTracesFeeder.hpp"


CDebugPanel::CDebugPanel(QWidget* parent) :
        QWidget(parent),
        ui( new Ui::CDebugPanel() )
{
    ui->setupUi(this);

    connect(ui->btnInsertTraces, SIGNAL(clicked()), this, SLOT(OnInsertTraces()));
    connect(ui->btnEnumTraces, SIGNAL(clicked()), this, SLOT(OnEnumTraces()));

    TraceClientCore::CModule&                   rModule = TraceClientCore::CModule::Instance();
    TraceClientCore::CTracesPoolRef             refTracesPool;
    TraceClientCore::CDbgTracesFeeder*          pFeeder = NULL;

    refTracesPool = rModule.TracesPools()[L"QtDefault"];

    pFeeder = new TraceClientCore::CDbgTracesFeeder( refTracesPool );

    refTracesPool->Feeder() = pFeeder;

    pFeeder->Start();
}



CDebugPanel::~CDebugPanel()
{
}



void CDebugPanel::OnInsertTraces()
{
    TraceClientCore::CModule&                   rModule = TraceClientCore::CModule::Instance();
    TraceClientCore::CTracesPoolRef             refTracesPool;
    int                                         NumTracesToAdd = ui->TracesToAddSpinBox->value();
    int                                         SleepTime = ui->SleepTimeBetweenInsertSpinBox->value();
    TraceClientCore::CDbgTracesFeeder*          pFeeder = NULL;

    refTracesPool = rModule.TracesPools()[L"QtDefault"];

    pFeeder = dynamic_cast<TraceClientCore::CDbgTracesFeeder*>((TraceClientCore::CTraceFeeder*)refTracesPool->Feeder());

    if ( pFeeder )
    {
        pFeeder->StartFeed(NumTracesToAdd, SleepTime);
    }
}



void CDebugPanel::OnEnumTraces()
{
 //   TraceClientCore::CModule&								rModule = TraceClientCore::CModule::Instance();
 //   TraceClientCore::CTracesPoolRef							refTracesPool = rModule.TracesPools()[L"QtDefault"];
 //   TraceClientCore::CTraceData*							pTrace = NULL;
	//TraceClientCore::ITraceDataRepository::IteratorHandle	hPos = NULL;
 //   TraceClientCore::ITraceDataRepository::IteratorHandle   hEndPos = NULL;

 //   TraceClientCore::CTraceDataRepository::Accessor			ReposAccess(refTracesPool->Repository());

 //   hPos = ReposAccess->AllocIterator();
 //   hEndPos = ReposAccess->AllocIterator();

 //   ReposAccess->GetHeadPos(hPos);
 //   ReposAccess->GetTailPos(hEndPos);

 //   Nyx::CTraceStream(0x0) << Nyx::CTF_Text(L"Beginning traces enumeration");

 //   while ( !ReposAccess->AreEqual(hPos, hEndPos)  )
 //   {
 //       pTrace = ReposAccess->Get(hPos);

 //       Nyx::CTraceStream(0x0)
 //               << Nyx::CTF_Text(pTrace->TickCount().c_str()) << Nyx::CTF_Text(L" -- ")
 //               << Nyx::CTF_Text(pTrace->ThreadId().c_str()) << Nyx::CTF_Text(L" -- ")
 //               << Nyx::CTF_Text(pTrace->Data().c_str());

 //       ReposAccess->IncrIterator(hPos);
 //   }

 //   Nyx::CTraceStream(0x0) << Nyx::CTF_Text(L"Completed traces enumeration");

 //   ReposAccess->ReleaseIterator(hPos);
 //   ReposAccess->ReleaseIterator(hEndPos);
}


void CDebugPanel::closeEvent(QCloseEvent *event)
{
}

