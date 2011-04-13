#ifndef _NEWPOOLDLG_HPP_
#define _NEWPOOLDLG_HPP_

#include "TracesPool.hpp"
#include "StatusUpdaters/StatusUpdater.hpp"

#include <QDialog>

namespace Ui
{
	class NewPoolDlg;
}


class CNewPoolDlg : public QDialog
{
	Q_OBJECT

public:

	/**
	 *
	 */
	class XData
	{
	public:

		enum EPoolFeederType
		{
			ePFT_Unknown,
			ePFT_Pipe
		};

	public:
		XData() : m_eFeederType(ePFT_Unknown) {}
		~XData() {}

		TraceClientCore::CTracesPoolRef		Pool() const		{ return m_refPool; }
		TraceClientCore::CTracesPoolRef&	Pool()				{ return m_refPool; }

		EPoolFeederType		FeederType() const					{ return m_eFeederType; }
		EPoolFeederType&	FeederType()						{ return m_eFeederType; }

		const QString&		PoolName() const					{ return m_PoolName; }
		QString&			PoolName()							{ return m_PoolName; }

		const QString&		PoolDescription() const				{ return m_PoolDescription; }
		QString&			PoolDescription()					{ return m_PoolDescription; }

	protected:

		TraceClientCore::CTracesPoolRef		m_refPool;
		EPoolFeederType						m_eFeederType;
		QString								m_PoolName;
		QString								m_PoolDescription;
	};

public:
	CNewPoolDlg();
	~CNewPoolDlg();

	virtual bool Exec( XData& data );

protected:

	void OnUpdate_Ok( const CStatusUpdater& rUpdater );

protected:

	Ui::NewPoolDlg*		ui;

	CStatusUpdater*			m_pOkStatusUpdater;
};

#endif // _NEWPOOLDLG_HPP_
