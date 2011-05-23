#include "NewViewDlg.hpp"
#include "ui_NewViewDlg.h"


/**
 *
 */
CNewViewDlg::CNewViewDlg() : QDialog(),
ui( new Ui::NewViewDlg() )
{
	ui->setupUi(this);

	m_pOkStatusUpdater = new TStatusUpdater<CNewViewDlg>(*this, &CNewViewDlg::OnUpdate_Ok);
	m_pOkStatusUpdater->Add(ui->m_editViewName);
	m_pOkStatusUpdater->OnUpdate();
}


/**
 *
 */
CNewViewDlg::~CNewViewDlg()
{
}


/**
 *
 */
bool CNewViewDlg::Exec( CNewViewDlg::XData& data )
{
	int		nRet = 0;

	nRet = exec();

	if ( QDialog::Accepted == nRet )
	{
		data.ViewName() = ui->m_editViewName->text();
		return true;
	}

	return false;
}


/**
 *
 */
void CNewViewDlg::OnUpdate_Ok( const CStatusUpdater& )
{
	bool	bEnabled = !ui->m_editViewName->text().isEmpty();

	ui->okButton->setEnabled(bEnabled);
	//QPushButton*	pButton = ui->buttonBox->button(QDialogButtonBox::Ok);
	//if ( pButton )
	//	pButton->setEnabled(bEnabled);
}
