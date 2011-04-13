#ifndef _TRACESFEEDER_HPP_
#define _TRACESFEEDER_HPP_

#include <Nyx.hpp>
#include <NyxRefCount_Impl.hpp>

#include "FeederLinkCollection.hpp"


DECLARE_OBJECTREF(CTracesFeeder)


class ITracesFeeder
{
public:
	virtual CFeederLinkCollection& FeederLinks() = 0;
	virtual void OnAddedToCollection() = 0;
	virtual void OnRemovedFromCollection() = 0;
};



/**
 *
 */
class CTracesFeeder : public Nyx::CRefCount_Impl<Nyx::CMTInterfaceAccess<CTracesFeeder, ITracesFeeder>>
{
public:
	CTracesFeeder(const wchar_t* wszName);
	virtual ~CTracesFeeder();

	Nyx::CString* Name() const { return m_refName; }

protected:

	virtual CFeederLinkCollection& FeederLinks();
	virtual void OnAddedToCollection();
	virtual void OnRemovedFromCollection();

protected:

	Nyx::CStringRef				m_refName;
	CFeederLinkCollection		m_FeederLinks;
};


#endif // _TRACESFEEDER_HPP_
