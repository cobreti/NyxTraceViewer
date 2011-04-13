#include <Nyx.hpp>

#include "TracesWnd.h"



/**
 *
 */
CTracesWnd::CTracesWnd()
{
	InitializeComponent();
}


/**
 *
 */
void CTracesWnd::OnTest_EnumTraceData()
{
	if ( m_TracesView != nullptr )
		m_TracesView->OnTest_EnumTraceData();
}


/**
 *
 */
void CTracesWnd::OnTest_UpdateUIRepos()
{
	if ( m_TracesView != nullptr )
		m_TracesView->OnTest_UpdateUIRepos();
}


/**
 *
 */
CTracesWnd::~CTracesWnd()
{
}


/**
 *
 */
void CTracesWnd::InitializeComponent()
{
	this->Size = System::Drawing::Size(300,300);
	this->Text = L"TracesWnd";
	this->Padding = System::Windows::Forms::Padding(0);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->SizeChanged += gcnew EventHandler(this, &CTracesWnd::OnSizeChanged);
	this->Closed += gcnew EventHandler( this, &CTracesWnd::OnClosed );

	m_TracesView = gcnew CTracesView();		
	m_TracesView->Parent = this;
	UpdateTracesViewSize();
	m_TracesView->Show();
}


/**
 *
 */
void CTracesWnd::UpdateTracesViewSize()
{
	Drawing::Rectangle	rcView = this->ClientRectangle;

	//rcView.Inflate(-20, -20);
	m_TracesView->Bounds = rcView;
}


/**
 *
 */
void CTracesWnd::OnSizeChanged( Object^ Sender, EventArgs^ args )
{
	UpdateTracesViewSize();

	this->Invalidate();
}


/**
 *
 */
void CTracesWnd::OnClosed( Object^ sender, EventArgs^ args )
{
	Nyx::CTraceStream(0x0).Write(L"TracesWnd Closed");
}
