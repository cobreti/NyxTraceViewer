#ifndef _UISENSORSFACTORY_HPP_
#define _UISENSORSFACTORY_HPP_

//#include <QtGui>
#include <QString>
#include <map>

class CUISensorCreator;


/**
 *
 */
class CUISensorsFactory
{
public:

	static CUISensorsFactory& Instance();
	static void Terminate();

public:

	void Add( const QString& className, CUISensorCreator* pCreator );
	CUISensorCreator* Get( const QString& className );

protected:
	CUISensorsFactory();
	virtual ~CUISensorsFactory();

protected:

	typedef		std::map<QString, CUISensorCreator*>	CreatorsMap;


	CreatorsMap						m_UISensorCreators;

	static CUISensorsFactory*		s_pFactory;
};

#endif // _UISENSORSFACTORY_HPP_
