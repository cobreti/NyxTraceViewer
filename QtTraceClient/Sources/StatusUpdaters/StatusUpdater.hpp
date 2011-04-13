#ifndef _STATUSUPDATER_HPP_
#define _STATUSUPDATER_HPP_

#include "UISensorsCollection.hpp"


/**
 *
 */
class CStatusUpdater
{
public:
	CStatusUpdater();
	virtual ~CStatusUpdater();

	virtual void OnUpdate() const {};

	CUISensorsCollection&			UISensors()			{ return m_Sensors; }
	const CUISensorsCollection&		UISensors() const	{ return m_Sensors; }

	template <class CTRLTYPE>
	void Add( CTRLTYPE* pCtrl )
	{
		CreateSensorForCtrl(pCtrl, pCtrl->metaObject()->className());
	}

protected:

	virtual void CreateSensorForCtrl( void* pCtrl, const char* className );

protected:

	CUISensorsCollection		m_Sensors;
};


/**
 *
 */
template <class C>
class TStatusUpdater : public CStatusUpdater
{
public:
	
	typedef		void (C::*PFCTUpdate)( const CStatusUpdater& rUpdater );

public:

	TStatusUpdater( C& rObj, PFCTUpdate pMethod ) : m_rObj(rObj), m_pfctUpdateMethod(pMethod) {}
	virtual ~TStatusUpdater() {}

	virtual void OnUpdate() const { (m_rObj.*m_pfctUpdateMethod)(*this); }


private:

	C&				m_rObj;
	PFCTUpdate		m_pfctUpdateMethod;
};


#endif // _STATUSUPDATER_HPP_
