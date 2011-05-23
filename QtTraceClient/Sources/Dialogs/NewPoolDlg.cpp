#include <QPushButton>

#include "NewPoolDlg.hpp"
#include "ui_NewPoolDlg.h"

#include "TraceClientCoreModule.hpp"
#include "PipeTraceFeeder.hpp"

//#include "StatusUpdaters/UISensor_LineEdit.hpp"
//#include <QPushButton>


/**
 *
 */
CNewPoolDlg::CNewPoolDlg() :
ui(new Ui::NewPoolDlg),
m_pOkStatusUpdater(NULL)
{
	ui->setupUi(this);

	m_pOkStatusUpdater = new TStatusUpdater<CNewPoolDlg>(*this, &CNewPoolDlg::OnUpdate_Ok);
	m_pOkStatusUpdater->Add(ui->m_pPoolNameEdit);
	m_pOkStatusUpdater->OnUpdate();
}


/**
 *
 */
CNewPoolDlg::~CNewPoolDlg()
{
	delete m_pOkStatusUpdater;
}


/**
 *
 */
bool CNewPoolDlg::Exec( CNewPoolDlg::XData& data )
{
	int			nRet = 0;
	QString		name;

	nRet = exec();

	if ( QDialog::Accepted == nRet )
	{
		data.PoolName() = ui->m_pPoolNameEdit->text();
		data.PoolDescription() = ui->m_pPoolDescEdit->text();
		data.FeederType() = XData::ePFT_Pipe;

		return true;
	}

	return false;
}


/**
 *
 */
void CNewPoolDlg::OnUpdate_Ok(const CStatusUpdater& )
{
	bool	bEnabled = !ui->m_pPoolNameEdit->text().isEmpty();

	QPushButton*	pButton = ui->buttonBox->button(QDialogButtonBox::Ok);
	if ( pButton )
		pButton->setEnabled(bEnabled);
}


