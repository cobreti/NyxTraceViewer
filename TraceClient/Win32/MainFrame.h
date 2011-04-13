#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


/// <summary>
/// Summary for MainFrame
///
/// WARNING: If you change the name of this class, you will need to change the
///          'Resource File Name' property for the managed resource compiler tool
///          associated with all .resx files this class depends on.  Otherwise,
///          the designers will not be able to interact properly with localized
///          resources associated with this form.
/// </summary>
public ref class CMainFrame : public System::Windows::Forms::Form
{
public:
	CMainFrame(void) :
	  m_LastTraceIndex(0)
	{
		InitializeComponent();
		//
		//TODO: Add the constructor code here
		//
	}

protected:
	/// <summary>
	/// Clean up any resources being used.
	/// </summary>
	~CMainFrame()
	{
		if (m_Components)
		{
			delete m_Components;
		}
	}

protected:

	void CreateMainMenu();
	ToolStripMenuItem^ CreateFileMenu();
	ToolStripMenuItem^ CMainFrame::CreateTestMenu();

	
	void OnNew( Object^ Sender, EventArgs^ Args );
	void OnMenuDeactivated( Object^ Sender, EventArgs^ Args );
	void OnDropDownClosed( Object^ Sender, ToolStripDropDownClosedEventArgs^ args );

	// test callback
	void OnTestInsertTraceData( Object^ Sender, EventArgs^ Args );
	void OnTestEnumTraceData( Object^ Sender, EventArgs^ Args );
	void OnTestUpdateUIRepos( Object^ Sender, EventArgs^ Args );
	void OnTestCreateDummyFeeder( Object^ Sender, EventArgs^ Args );

private:
	/// <summary>
	/// Required designer variable.
	/// </summary>
	System::ComponentModel::Container^				m_Components;

	int												m_LastTraceIndex;

#pragma region Windows Form Designer generated code
	/// <summary>
	/// Required method for Designer support - do not modify
	/// the contents of this method with the code editor.
	/// </summary>
	void InitializeComponent(void)
	{
		this->m_Components = gcnew System::ComponentModel::Container();
		this->Size = System::Drawing::Size(300,300);
		this->Text = L"MainFrame";
		this->Padding = System::Windows::Forms::Padding(0);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->IsMdiContainer = true;

		CreateMainMenu();
    }
#pragma endregion

};
