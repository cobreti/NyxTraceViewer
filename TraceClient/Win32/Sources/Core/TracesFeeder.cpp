#include "TracesFeeder.hpp"


/**
 *
 */
CTracesFeeder::CTracesFeeder(const wchar_t* wszName)
{
	m_refName = Nyx::CString::Alloc(wszName);
}


/**
 *
 */
CTracesFeeder::~CTracesFeeder()
{
}


/**
 *
 */
CFeederLinkCollection& CTracesFeeder::FeederLinks()
{
	return m_FeederLinks;
}


/**
 *
 */
void CTracesFeeder::OnAddedToCollection()
{
}


/**
 *
 */
void CTracesFeeder::OnRemovedFromCollection()
{
}


