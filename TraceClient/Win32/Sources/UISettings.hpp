#ifndef _UISETTINGS_HPP_
#define _UISETTINGS_HPP_

#include "UIFontsSettings.hpp"
#include "UIColorSettings.hpp"
#include "TracesViewSettings.hpp"


public ref class CUISettings
{
public:	// public static methods

	static CUISettings% Instance();

public:	// public methods
	CUISettings();
	virtual ~CUISettings();

	virtual void Init();
	virtual void Terminate();

	property CUIFontsSettings% Fonts
	{
		CUIFontsSettings% get() { return m_FontsSettings; }
	}

	property CUIColorSettings% Colors
	{
		CUIColorSettings% get() { return m_ColorSettings; }
	}

	property CTracesViewSettings% TracesView
	{
		CTracesViewSettings% get() { return m_TracesViewSettings; }
	}

protected:	// protected members

	CUIFontsSettings			m_FontsSettings;
	CUIColorSettings			m_ColorSettings;
	CTracesViewSettings			m_TracesViewSettings;

protected:	// protected static members

	static CUISettings^ s_pInstance;
};


#endif // _UISETTINGS_HPP_
