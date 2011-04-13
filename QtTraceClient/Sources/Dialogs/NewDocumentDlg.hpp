#ifndef _NEWDOCUMENTDLG_HPP_
#define _NEWDOCUMENTDLG_HPP_

#include "StatusUpdaters/StatusUpdater.hpp"
#include "DataStruct/PoolsList.hpp"

#include <QDialog>

namespace Ui
{
	class NewDocumentDlg;
}


class CNewDocumentDlg : public QDialog
{
	Q_OBJECT

	typedef		TStatusUpdater<CNewDocumentDlg>		DlgUpdater;

public:

	class XData
	{
	public:
		XData() {}
		~XData() {}

		TraceClientCore::CPoolsList& OriginalPools()		{ return m_OriginalPools; }
		TraceClientCore::CPoolsList& SelectedPools()		{ return m_SelectedPools; }

		const QString&			DocumentName() const		{ return m_DocumentName; }
		QString&				DocumentName()				{ return m_DocumentName; }

	protected:

		TraceClientCore::CPoolsList		m_OriginalPools;
		TraceClientCore::CPoolsList		m_SelectedPools;
		QString							m_DocumentName;
	};

public:
	CNewDocumentDlg();
	virtual ~CNewDocumentDlg();

	virtual bool Exec( XData& data );

protected:

	void OnUpdate_Ok(const CStatusUpdater& rUpdater);
	void FillPoolsListView( TraceClientCore::CPoolsList& Pools );
	void ExtractSelectedPools( TraceClientCore::CPoolsList& SelectedPools );

protected:

	Ui::NewDocumentDlg*		ui;
	DlgUpdater				m_OkStatusUpdater;
	XData*					m_pData;
};



#endif // _NEWDOCUMENTDLG_HPP_
