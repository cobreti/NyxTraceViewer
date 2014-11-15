#include <QPushButton>
#include <QListView>
#include <QListWidget>
#include <QListWidgetItem>

#include "NewDocumentDlg.hpp"
#include "ui_NewDocumentDlg.h"
#include "TracesPool.hpp"
#include "TraceClientCoreModule.hpp"


Q_DECLARE_METATYPE(TraceClientCore::CTracesPool*);

/**
 *
 */
CNewDocumentDlg::CNewDocumentDlg() : QDialog(),
ui(new Ui::NewDocumentDlg()),
m_OkStatusUpdater(*this, &CNewDocumentDlg::OnUpdate_Ok),
m_pData(NULL)
{
	ui->setupUi(this);

	m_OkStatusUpdater.Add(ui->m_pDocNameEdit);
	m_OkStatusUpdater.OnUpdate();
}


/**
 *
 */
CNewDocumentDlg::~CNewDocumentDlg()
{
}


/**
 *
 */
bool CNewDocumentDlg::Exec( CNewDocumentDlg::XData& data )
{
	int		nRet = 0;

	m_pData = &data;
	FillPoolsListView(data.OriginalPools());
	nRet = exec();
	m_pData = NULL;

	if ( QDialog::Accepted == nRet )
	{
		data.DocumentName() = ui->m_pDocNameEdit->text();
		ExtractSelectedPools( data.SelectedPools() );
		return true;
	}

	return false;
}


/**
 *
 */
void CNewDocumentDlg::OnUpdate_Ok(const CStatusUpdater& )
{
	bool	bEnabled = !ui->m_pDocNameEdit->text().isEmpty();

	QPushButton*	pButton = ui->buttonBox->button(QDialogButtonBox::Ok);
	if ( pButton )
		pButton->setEnabled(bEnabled);
}


/**
 *
 */
void CNewDocumentDlg::FillPoolsListView( TraceClientCore::CPoolsList& Pools )
{
	TraceClientCore::CPoolsList::const_iterator		pos;

	for (pos = Pools.begin(); pos != Pools.end(); ++pos)
	{
        TraceClientCore::CTracesPool*	pPool = (*pos).Pool();
        QString	text = pPool->Name();
		
		QListWidgetItem*		pItem = new QListWidgetItem(text, ui->m_pPoolsList, Qt::ItemIsUserCheckable);
		pItem->setCheckState(Qt::Unchecked);
        pItem->setData( Qt::UserRole, QVariant(pPool->Name()) );

		ui->m_pPoolsList->addItem(pItem);
	}
}


/**
 *
 */
void CNewDocumentDlg::ExtractSelectedPools( TraceClientCore::CPoolsList& SelectedPools )
{
	int									nCount = ui->m_pPoolsList->count();
	int									nIndex = 0;
	QListWidgetItem*					pItem = NULL;
	TraceClientCore::CTracesPool*		pPool = NULL;
	TraceClientCore::CModule&			Module = TraceClientCore::CModule::Instance();

	while ( nIndex < nCount )
	{
		pItem = ui->m_pPoolsList->item(nIndex);
		if ( pItem->checkState() == Qt::Checked )
		{
			QString PoolName = pItem->data(Qt::UserRole).toString();
            pPool = Module.TracesPools()[PoolName];
			//pPool = pItem->data(QVariant::UserType).value<TraceClientCore::CTracesPool*>();
            SelectedPools.push_back( TraceClientCore::CPoolsListItem(pPool) );
		}
		++ nIndex;
	}
}


