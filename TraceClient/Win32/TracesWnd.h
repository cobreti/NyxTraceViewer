#pragma once

#include "TracesView.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


/// <summary>
/// Summary for TracesWnd
///
/// WARNING: If you change the name of this class, you will need to change the
///          'Resource File Name' property for the managed resource compiler tool
///          associated with all .resx files this class depends on.  Otherwise,
///          the designers will not be able to interact properly with localized
///          resources associated with this form.
/// </summary>
public ref class CTracesWnd : public System::Windows::Forms::Form
{
public:
	CTracesWnd();

	virtual void OnTest_EnumTraceData();
	virtual void OnTest_UpdateUIRepos();

protected:
	virtual ~CTracesWnd();

protected:

	void InitializeComponent(void);

	void UpdateTracesViewSize();

	void OnSizeChanged( Object^ Sender, EventArgs^ args );
	void OnClosed( Object^ Sender, EventArgs^ args );

protected: // protected members

	CTracesView^				m_TracesView;
};
