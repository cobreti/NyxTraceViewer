#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


ref class CTracesViewController;
class CUITraceDataRepositoryIterator;

/// <summary>
/// Summary for TracesView
///
/// WARNING: If you change the name of this class, you will need to change the
///          'Resource File Name' property for the managed resource compiler tool
///          associated with all .resx files this class depends on.  Otherwise,
///          the designers will not be able to interact properly with localized
///          resources associated with this form.
/// </summary>
public ref class CTracesView : public System::Windows::Forms::Control
{
public:
	CTracesView();

	virtual void OnTest_EnumTraceData();
	virtual void OnTest_UpdateUIRepos();

protected:
	virtual ~CTracesView();

protected:

	property Drawing::Rectangle ViewArea
	{
		Drawing::Rectangle get()
		{
			return Drawing::Rectangle(	ClientRectangle.X, ClientRectangle.Y, 
										ClientRectangle.Width - m_VScrollBar->Width, 
										ClientRectangle.Height - m_HScrollBar->Height );
		}
	}

	void OnPaint( Object^ Sender, PaintEventArgs^ Args );
	void OnSizeChanged( Object^ Sender, EventArgs^ Args );
	void OnReposUpdate( void* param );
	void OnVScrollValueChanged( Object^ Sender, EventArgs^ Args );
	void OnScroll( Object^ sender, ScrollEventArgs^ args );
	void OnHScrollValueChanged( Object^ Sender, EventArgs^ Args );
	void OnKeyDown( Object^ sender, KeyEventArgs^ args );
	virtual bool ProcessCmdKey( Message% msg, Keys KeyData) override;

	void InitializeComponent(void);
	void UpdateMetrics();
	void UpdateHScrollRange();

protected:

	VScrollBar^							m_VScrollBar;
	HScrollBar^							m_HScrollBar;
	CTracesViewController^				m_Controller;
	CUITraceDataRepositoryIterator*		m_pFirstLinePos;

	unsigned int						m_NumberOfVisibleLines;
	float								m_AvgLineHeight;
	float								m_MaxLineWidth;
	bool								m_bDisplayLastLine;
	bool								m_bKeepAtEnd;
};
