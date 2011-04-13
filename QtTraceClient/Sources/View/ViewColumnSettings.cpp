#include "ViewColumnSettings.hpp"


/**
 *
 */
CViewColumnSettings::CViewColumnSettings() :
m_Width(0),
m_PainterId(CViewItemPainter::ePId_Generic),
m_bVisible(true),
m_bAutoWidth(false)
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


/**
 *
 */
void CViewColumnSettings::SetPainterId( const CViewItemPainter::EPainterId& id )
{
	m_PainterId = id;
}
