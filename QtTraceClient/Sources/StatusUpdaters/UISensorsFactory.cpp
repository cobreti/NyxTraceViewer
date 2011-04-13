#include "StatusUpdaters/UISensorsFactory.hpp"
#include "StatusUpdaters/UISensorCreator.hpp"
#include "StatusUpdaters/UISensor_LineEdit.hpp"


/**
 *
 */
CUISensorsFactory* CUISensorsFactory::s_pFactory = NULL;


/**
 *
 */
CUISensorsFactory& CUISensorsFactory::Instance()
{
	if ( s_pFactory == NULL )
		s_pFactory = new CUISensorsFactory();

	return *s_pFactory;
}


/**
 *
 */
void CUISensorsFactory::Terminate()
{
	if ( s_pFactory )
		delete s_pFactory;

	s_pFactory = NULL;
}


/**
 *
 */
void CUISensorsFactory::Add( const QString& className, CUISensorCreator* pCreator )
{
	m_UISensorCreators[className] = pCreator;
}


/**
 *
 */
CUISensorCreator* CUISensorsFactory::Get( const QString& className )
{
	CreatorsMap::const_iterator	pos = m_UISensorCreators.find(className);

	if ( pos != m_UISensorCreators.end() )
		return pos->second;

	return NULL;
}


/**
 *
 */
CUISensorsFactory::CUISensorsFactory()
{
	Add( CUISensor_LineEdit::className(), new TUISensorCreator<CUISensor_LineEdit>() );
}


/**
 *
 */
CUISensorsFactory::~CUISensorsFactory()
{
	while ( !m_UISensorCreators.empty() )
	{
		CreatorsMap::iterator	pos = m_UISensorCreators.begin();
		delete pos->second;
		m_UISensorCreators.erase(pos);
	}
}

