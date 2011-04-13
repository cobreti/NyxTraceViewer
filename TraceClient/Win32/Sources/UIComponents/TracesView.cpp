#include <Nyx.hpp>

#include "TracesView.h"
#include "TracesViewController.hpp"
#include "UITraceDataRepositoryIterator.hpp"
#include "UITraceDataRepository.hpp"
#include "UISettings.hpp"


/**
 *
 */
CTracesView::CTracesView() :
m_NumberOfVisibleLines(0),
m_AvgLineHeight(0.0f),
m_MaxLineWidth(0.0f),
m_bDisplayLastLine(false),
m_bKeepAtEnd(true)
{
	InitializeComponent();

	m_Controller = gcnew CTracesViewController(this);
	m_Controller->ReposUpdate += gcnew CTracesViewController::OnReposUpdate_Delegate(this, &CTracesView::OnReposUpdate);
}


/**
 *
 */
void CTracesView::OnTest_EnumTraceData()
{
	CUITraceDataRepository::ConstAccessor			ReposAccessor(m_Controller->Repository);

	if ( ReposAccessor )
	{
		CUITraceDataRepositoryIterator					pos( ReposAccessor );
		CUITraceDataRepositoryIterator::Accessor		PosAccessor(pos);

		if (PosAccessor)
		{
			PosAccessor = ReposAccessor->HeadPos();
			while ( PosAccessor != ReposAccessor->TailPos() )
			{
				CUITraceData*		pTD = ReposAccessor->Get(PosAccessor);

				Nyx::CTraceStream(0x0)
					<< Nyx::CTF_Text( L"[" )
					<< Nyx::CTF_Text( pTD->ThreadId() )
					<< Nyx::CTF_Text( L"] [" )
					<< Nyx::CTF_Text( pTD->TickCount() )
					<< Nyx::CTF_Text( L" | " )
					<< Nyx::CTF_Text( pTD->Data() );

				++ PosAccessor;
			}
		}
	}
}


/**
 *
 */
void CTracesView::OnTest_UpdateUIRepos()
{
	m_Controller->OnTest_UpdateUIRepos();
}


/**
 *
 */
CTracesView::~CTracesView()
{
	if ( m_Controller )
		delete m_Controller;
}


/**
 *
 */
void CTracesView::OnPaint( Object^ Sender, PaintEventArgs^ Args )
{
	Nyx::NyxResult		res;

	NyxBeginBody("CTracesView::OnPaint")
	{
		Drawing::Brush^ BkBrush = CUISettings::Instance().TracesView.BackgroundBrush;

		Args->Graphics->SetClip(ViewArea);
		Args->Graphics->FillRectangle(BkBrush, 0, 0, this->Width-20, this->Height);

		float		MaxY = (float)ViewArea.Height;

		if ( NULL != m_pFirstLinePos )
		{
			CUITraceDataRepositoryIterator					Pos(m_Controller->Repository);
			CUITraceDataRepositoryIterator::Accessor		PosAccess(Pos);
			CUITraceDataRepository::ConstAccessor			ReposAccess(m_Controller->Repository);

			CUITraceData*									pTraceData = NULL;
			CTracesViewColumnsArray^						Columns = CUISettings::Instance().TracesView.Columns;
			CTracesViewColumnSettings^						Settings = nullptr;
			CTraceItemDisplay^								ItemDisplay = nullptr;
			int												index;
			Drawing::SizeF									MaxLineSize(0.0f, 0.0f);
			Drawing::SizeF									LineSize(0.0f, 0.0f);
			Drawing::PointF									DisplayPos;
			float											fMaxWidth = 0.0f;

			PosAccess = *m_pFirstLinePos;
			DisplayPos.Y = (float)ViewArea.Top;

			while ( DisplayPos.Y < MaxY && PosAccess != ReposAccess->TailPos() )
			{
				pTraceData = ReposAccess->Get(PosAccess);

				LineSize = Drawing::SizeF(0.0f, 0.0f);
				MaxLineSize = Drawing::SizeF(0.0f, 0.0f);
				DisplayPos.X = (float)this->ViewArea.Left - m_HScrollBar->Value;

				for ( index = 0; index < Columns->Count; ++index )
				{
					Settings = Columns->Item[index];
					ItemDisplay = Settings->ItemDisplay;

					if ( ItemDisplay != nullptr )
					{
						LineSize = ItemDisplay->Display( *pTraceData, *Settings, DisplayPos, Args->Graphics );
						MaxLineSize.Height = max(MaxLineSize.Height, LineSize.Height);
						MaxLineSize.Width += LineSize.Width;
						DisplayPos.X += LineSize.Width;
					}
				}

				fMaxWidth = max(fMaxWidth, MaxLineSize.Width);
				DisplayPos.Y += MaxLineSize.Height;
				++ PosAccess;
			}

			m_MaxLineWidth = max(fMaxWidth, m_MaxLineWidth);

			UpdateHScrollRange();

			m_bDisplayLastLine = ( m_pFirstLinePos->Index() + m_NumberOfVisibleLines >= ReposAccess->Count() );

			System::GC::Collect(System::GC::MaxGeneration);
		}
	}
	NyxEndBody(res)
}


/**
 *
 */
void CTracesView::OnSizeChanged(Object ^Sender, EventArgs ^Args)
{
	CUITraceDataRepository::ConstAccessor		UIReposAccess( m_Controller->Repository );

	m_VScrollBar->Bounds = Drawing::Rectangle( Size.Width - 20, 0, 20, Size.Height-20 );
	m_HScrollBar->Bounds = Drawing::Rectangle( 0, Size.Height-20, Size.Width-20, 20 );

	UpdateMetrics();
	UpdateHScrollRange();

	m_VScrollBar->Maximum = max((int)(UIReposAccess->Count() - m_NumberOfVisibleLines), 0);

	if ( m_bDisplayLastLine && UIReposAccess->Count() > m_NumberOfVisibleLines)
	{
		CUITraceDataRepositoryIterator::Accessor		PosAccess(*m_pFirstLinePos);

		if (PosAccess)
		{
			PosAccess = UIReposAccess->TailPos();
			PosAccess->Goto( UIReposAccess->Count() - m_NumberOfVisibleLines );
			m_VScrollBar->Value = PosAccess->Index();
		}
	}

	Invalidate();
}


/**
 *
 */
void CTracesView::OnReposUpdate( void* param )
{
	CUITraceDataRepository::ConstAccessor		UIReposAccess( m_Controller->Repository );

	bool		bAtEnd = (m_VScrollBar->Value == m_VScrollBar->Maximum);
	size_t		NumLines = UIReposAccess->Count();

	m_VScrollBar->Maximum = max((int)(UIReposAccess->Count() - m_NumberOfVisibleLines), 0);

	if ( NULL == m_pFirstLinePos && UIReposAccess->Count() > 0 )
	{
		m_pFirstLinePos = new CUITraceDataRepositoryIterator(m_Controller->Repository);
		*m_pFirstLinePos = UIReposAccess->HeadPos();
	}

	if ( (m_bKeepAtEnd || m_bDisplayLastLine) && UIReposAccess->Count() > m_NumberOfVisibleLines)
	{
		CUITraceDataRepositoryIterator::Accessor		PosAccess(*m_pFirstLinePos);

		if (PosAccess)
		{
			PosAccess = UIReposAccess->TailPos();
			PosAccess->Goto( UIReposAccess->Count() - m_NumberOfVisibleLines );
			m_VScrollBar->Value = PosAccess->Index();
		}
	}

	if ( UIReposAccess->Count() < m_NumberOfVisibleLines )
	{
		Invalidate();
	}
}


/**
 *
 */
void CTracesView::OnVScrollValueChanged( Object^ Sender, EventArgs^ Args )
{
	if ( m_pFirstLinePos == NULL )
		return;

	CUITraceDataRepositoryIterator::Accessor			PosAccess(*m_pFirstLinePos);

	if (PosAccess)
		PosAccess->Goto(m_VScrollBar->Value);

	Invalidate();
}


/**
 *
 */
void  CTracesView::OnScroll( Object^ sender, ScrollEventArgs^ args )
{
	m_bKeepAtEnd = false;
}


/**
 *
 */
void CTracesView::OnHScrollValueChanged( Object^ Sender, EventArgs^ Args )
{
	Invalidate();
}


/**
 *
 */
void CTracesView::OnKeyDown( Object^ sender, KeyEventArgs^ args )
{
	switch (args->KeyCode)
	{
		case Keys::End:
			{
				if ( args->Control && NULL != m_pFirstLinePos )
				{
					CUITraceDataRepository::ConstAccessor			UIReposAccess( m_Controller->Repository );
					CUITraceDataRepositoryIterator::Accessor		PosAccess(*m_pFirstLinePos);

					if ( UIReposAccess->Count() > 0 && UIReposAccess && PosAccess )
					{
						PosAccess = UIReposAccess->TailPos();
						PosAccess->Goto( UIReposAccess->Count() - m_NumberOfVisibleLines );
						m_VScrollBar->Value = PosAccess->Index();
						m_bKeepAtEnd = true;
						Invalidate();
					}
				}
			}
			break;

		case Keys::Home:
			{
				if ( args->Control && NULL != m_pFirstLinePos )
				{
					m_bKeepAtEnd = false;
					CUITraceDataRepository::ConstAccessor			UIReposAccess( m_Controller->Repository );
					CUITraceDataRepositoryIterator::Accessor		PosAccess(*m_pFirstLinePos);

					if ( UIReposAccess->Count() > 0 && UIReposAccess && PosAccess )
					{
						PosAccess = UIReposAccess->HeadPos();
						m_VScrollBar->Value = PosAccess->Index();
						Invalidate();
					}
				}
			}
			break;
	}
}


bool CTracesView::ProcessCmdKey( Message% msg, Keys KeyData)
{
	bool		bRet = false;

	if ( msg.Msg == WM_KEYDOWN )
	{
		switch (KeyData)
		{
			case Keys::Down:
				{
					m_bKeepAtEnd = false;
					if ( m_VScrollBar->Value < m_VScrollBar->Maximum )
						m_VScrollBar->Value++;
					bRet = true;
				}
				break;
			case Keys::Up:
				{
					m_bKeepAtEnd = false;
					if ( m_VScrollBar->Value > 0 )
						m_VScrollBar->Value--;
					bRet = true;
				}
				break;
		};
	}

	return bRet;
}


/**
 *
 */
void CTracesView::InitializeComponent(void)
{
	this->SuspendLayout();

	this->Paint += gcnew PaintEventHandler(this, &CTracesView::OnPaint);
	this->SizeChanged += gcnew EventHandler(this, &CTracesView::OnSizeChanged);
	this->KeyDown += gcnew KeyEventHandler(this, &CTracesView::OnKeyDown);

	m_VScrollBar = gcnew VScrollBar();
	m_VScrollBar->Parent = this;
	m_VScrollBar->Maximum = 0;
	m_VScrollBar->Minimum = 0;
	m_VScrollBar->SmallChange = 1;
	m_VScrollBar->LargeChange = 1;
	m_VScrollBar->ValueChanged += gcnew EventHandler( this, &CTracesView::OnVScrollValueChanged );
	m_VScrollBar->Scroll += gcnew ScrollEventHandler(this, &CTracesView::OnScroll);
	m_VScrollBar->Show();

	m_HScrollBar = gcnew HScrollBar();
	m_HScrollBar->Parent = this;
	m_HScrollBar->Maximum = 0;
	m_HScrollBar->Minimum = 0;
	m_HScrollBar->SmallChange = 1;
	m_HScrollBar->LargeChange = 1;
	m_HScrollBar->ValueChanged += gcnew EventHandler( this, &CTracesView::OnHScrollValueChanged );
	m_HScrollBar->Show();

	this->ResumeLayout(false);
}


/**
 *
 */
void CTracesView::UpdateMetrics()
{
	Drawing::Font^								TraceDataFont = CUISettings::Instance().TracesView.Columns->Item[ETracesViewColumnID::TraceData]->Font;

	if ( m_AvgLineHeight <= 1.0f )
	{
		CUITraceDataRepository::ConstAccessor		ReposAccess( m_Controller->Repository );
		CTracesViewColumnsArray^					Columns = CUISettings::Instance().TracesView.Columns;
		int											index = 0;
		float										LineHeight = 0.0f;
		Drawing::Graphics^							ViewGraphics = this->CreateGraphics();

		for (index = 0; index < Columns->Count; ++index)
		{
			CTracesViewColumnSettings^		ColumnSettings = Columns->Item[index];
			CTraceItemDisplay^				ItemDisplay = ColumnSettings->ItemDisplay;

			if ( ItemDisplay != nullptr )
			{
				LineHeight = ItemDisplay->CalcItemSize( *ColumnSettings, ViewGraphics ).Height;

				if ( LineHeight > m_AvgLineHeight )
					m_AvgLineHeight = LineHeight;
			}
		}
	}

	m_NumberOfVisibleLines = (int)( ViewArea.Height / m_AvgLineHeight );
}


/**
 *
 */
void CTracesView::UpdateHScrollRange()
{
	m_HScrollBar->Maximum = max(0, (int)(m_MaxLineWidth - ViewArea.Width + 10.5f));
}
