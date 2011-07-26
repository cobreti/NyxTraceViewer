#include "ViewItemsSettings.hpp"


/**
 *
 */
CViewItemSettings::CViewItemSettings() :
m_pFont(NULL),
m_FontHeight(0)
{
}


/**
 *
 */
CViewItemSettings::CViewItemSettings(const CViewItemSettings& settings) :
m_pFont(NULL),
m_FontHeight(settings.m_FontHeight)
{
	CopyFrom(settings);
}


/**
 *
 */
CViewItemSettings::~CViewItemSettings()
{
}


/**
 *
 */
void CViewItemSettings::SetFont(QFont* pFont)
{
    if ( pFont != m_pFont )
    {
        if ( m_pFont )
        {
            delete m_pFont;
        }

        m_pFont = pFont;

        if ( m_pFont )
        {
            QFontMetrics        metrics(*m_pFont);

            m_FontHeight = metrics.height();
        }
    }
}


/**
 *
 */
int CViewItemSettings::FontHeight() const
{
    return m_FontHeight;
}


/**
 *
 */
const CViewItemSettings& CViewItemSettings::operator = (const CViewItemSettings& settings)
{
	if ( this != &settings )
		CopyFrom(settings);

	return *this;
}


/**
 *
 */
CViewItemSettings* CViewItemSettings::Clone() const
{
	return  new CViewItemSettings(*this);
}


/**
 *
 */
void CViewItemSettings::CopyFrom(const CViewItemSettings& settings)
{
	if ( m_pFont )
    {
		delete m_pFont;
        m_pFont = NULL;
    }

	if ( settings.m_pFont )
		m_pFont = new QFont(*settings.m_pFont);

    m_FontHeight = settings.m_FontHeight;
}


