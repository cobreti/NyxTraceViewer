#ifndef _NEWVIEWDLG_HPP_
#define _NEWVIEWDLG_HPP_

#include "StatusUpdaters/StatusUpdater.hpp"

#include <QDialog>

namespace Ui
{
	class NewViewDlg;
}


/**
 *
 */
class CNewViewDlg : public QDialog
{
	Q_OBJECT

public:

	/**
	 *
	 */
	class XData
	{
	public:
		XData() {}
		~XData() {}

		const QString&		ViewName() const		{ return m_ViewName; }
		QString&			ViewName()				{ return m_ViewName; }

	protected:

		QString		m_ViewName;
	};

public:
	CNewViewDlg();
	virtual ~CNewViewDlg();

	bool Exec( XData& data );

protected:

	void OnUpdate_Ok( const CStatusUpdater& rUpdater );

protected:

	Ui::NewViewDlg*		ui;
	CStatusUpdater*		m_pOkStatusUpdater;
};


#endif // _NEWVIEWDLG_HPP_
