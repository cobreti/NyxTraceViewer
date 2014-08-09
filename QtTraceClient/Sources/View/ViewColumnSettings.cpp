#include "ViewColumnSettings.hpp"


/**
 *
 */
CViewColumnSettings::CViewColumnSettings() :
m_Width(0),
//m_PainterId(CViewItemPainter::ePId_Generic),
m_bVisible(true),
m_bAutoWidth(false)
{
}


CViewColumnSettings::CViewColumnSettings(const CViewColumnSettings& settings) :
    m_Width(settings.m_Width),
//    m_PainterId(settings.m_PainterId),
    m_bVisible(settings.m_bVisible),
    m_Title(settings.m_Title),
    m_Margins(settings.m_Margins),
    m_bAutoWidth(settings.m_bAutoWidth)
{
}


/**
 *
 */
CViewColumnSettings::~CViewColumnSettings()
{
}


/**
 *
 */
void CViewColumnSettings::SetWidth(const qreal& width)
{
	m_Width = width;
}

