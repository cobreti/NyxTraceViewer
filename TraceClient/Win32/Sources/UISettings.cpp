#include "UISettings.hpp"



/**
 *
 */
CUISettings% CUISettings::Instance()
{
	return *s_pInstance;
}


/**
 *
 */
CUISettings::CUISettings()
{
	s_pInstance = this;
}


/**
 *
 */
CUISettings::~CUISettings()
{
	s_pInstance = nullptr;
}


/**
 *
 */
void CUISettings::Init()
{
	m_FontsSettings.Init();
	m_ColorSettings.Init();
	m_TracesViewSettings.Init();
}


/**
 *
 */
void CUISettings::Terminate()
{
	m_TracesViewSettings.Terminate();
	m_ColorSettings.Terminate();
	m_FontsSettings.Terminate();
}

