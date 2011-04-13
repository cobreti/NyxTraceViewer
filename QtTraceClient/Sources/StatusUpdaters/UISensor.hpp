#ifndef _UISENSOR_HPP_
#define _UISENSOR_HPP_

#include <QObject>

class CStatusUpdater;

class CUISensor : public QObject
{
	Q_OBJECT

public:
	CUISensor(void* pCtrl, const CStatusUpdater& rUpdater);
	virtual ~CUISensor();

protected:

	virtual void SendUpdate();

	const CStatusUpdater& StatusUpdater() const { return m_rStatusUpdater; }

protected:

	const CStatusUpdater&		m_rStatusUpdater;
};

#endif // _UISENSOR_HPP_
