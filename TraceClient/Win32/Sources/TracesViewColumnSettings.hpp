#ifndef _TRACESVIEWCOLUMNSETTINGS_HPP_
#define _TRACESVIEWCOLUMNSETTINGS_HPP_

#include "Margins.hpp"
#include "TraceItemDisplay.hpp"

using namespace System;


/**
 *
 */
public enum class ETracesViewColumnID
{
	ThreadID,
	TickCount,
	TraceData
};


/**
 *
 */
public ref class CTracesViewColumnSettings
{
public: // public methods
	CTracesViewColumnSettings();
	virtual ~CTracesViewColumnSettings();

	property ETracesViewColumnID^ ID
	{
		ETracesViewColumnID^ get() { return m_ID; }
		void set( ETracesViewColumnID^ id ) { m_ID = id; }
	}

	property Drawing::Font^ Font
	{
		Drawing::Font^ get() { return m_Font; }
		void set( Drawing::Font^ f) { m_Font = f; }
	}

	property float Width
	{
		float get() { return m_Width; }
		void set( float w ) { m_Width = w; }
	}

	property CMargins% Margins
	{
		CMargins% get() { return m_Margins; }
	}

	property CTraceItemDisplay^ ItemDisplay
	{
		CTraceItemDisplay^ get() { return m_ItemDisplay; }
		void set( CTraceItemDisplay^ item ) { m_ItemDisplay = item; }
	}

protected:

	ETracesViewColumnID^		m_ID;
	Drawing::Font^				m_Font;
	float						m_Width;
	CMargins					m_Margins;
	CTraceItemDisplay^			m_ItemDisplay;
};



#endif // _TRACESVIEWCOLUMNSETTINGS_HPP_
