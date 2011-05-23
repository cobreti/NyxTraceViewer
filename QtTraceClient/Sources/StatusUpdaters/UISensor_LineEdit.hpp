#include "StatusUpdaters/UISensor.hpp"

#include <QLineEdit>

/**
 *
 */
class CUISensor_LineEdit : public CUISensor
{
	Q_OBJECT

public:

	static QString className() { return QLineEdit().metaObject()->className(); }

public:
	CUISensor_LineEdit(void* pCtrl, const CStatusUpdater& rUIUpdater) :
		CUISensor(pCtrl, rUIUpdater),
		m_pLineEdit((QLineEdit*)pCtrl)
	{
		connect(	m_pLineEdit, SIGNAL(textChanged(const QString&)), 
					this, SLOT(OnTextChanged(const QString&)) );
	}

public slots:

	virtual void OnTextChanged( const QString& )
	{
		SendUpdate();
	}

private:

	QLineEdit*		m_pLineEdit;
};
