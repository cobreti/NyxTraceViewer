#include "ViewDrawSettings.hpp"

static char* HeightCalcString = "abcdefghijklmnopqrstuvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

#include <QFont>
#include <QFontMetrics>

/**
 *
 */
CViewDrawSettings::CViewDrawSettings() :
    m_LineHeight(0)
{

}


/**
 *
 */
CViewDrawSettings::~CViewDrawSettings()
{
}


void CViewDrawSettings::setSingleLineHeight(float height)
{
    m_LineHeight = height;
}


/**
 *
 */
void CViewDrawSettings::CalculateLineHeight()
{
    m_LineHeight = QFontMetricsF(QFont()).boundingRect(HeightCalcString).height() * 1.2;
}


