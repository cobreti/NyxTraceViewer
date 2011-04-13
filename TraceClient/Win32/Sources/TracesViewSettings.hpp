#ifndef _TRACESVIEWSETTINGS_HPP_
#define _TRACESVIEWSETTINGS_HPP_

#include "TracesViewColumnsArray.hpp"


using namespace System::Drawing;


/**
 *
 */
public ref class CTracesViewSettings
{
public:	// public methods
	CTracesViewSettings();
	virtual ~CTracesViewSettings();

	virtual void Init();
	virtual void Terminate();

	property Brush^ BackgroundBrush
	{
		Brush^ get() { return m_BackgroundBrush; }
	}

	property CTracesViewColumnsArray^ Columns
	{
		CTracesViewColumnsArray^ get() { return m_Columns; }
	}

protected: // protected functions

	virtual void CreateColumn_TraceData();
	virtual void CreateColumn_ThreadId();
	virtual void CreateColumn_TickCount();

protected: // protected members

	Brush^							m_BackgroundBrush;
	CTracesViewColumnsArray^		m_Columns;
};


#endif // _TRACESVIEWSETTINGS_HPP_
