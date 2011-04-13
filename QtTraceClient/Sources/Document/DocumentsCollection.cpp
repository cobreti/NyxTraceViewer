#include "DocumentsCollection.hpp"
#include "TracesDocument.hpp"

/**
 *
 */
CDocumentsCollection::CDocumentsCollection()
{
}


/**
 *
 */
CDocumentsCollection::~CDocumentsCollection()
{
	Clear();
}


/**
 *
 */
void CDocumentsCollection::Insert( const Nyx::CAString& name, CTracesDocument* pDoc )
{
	this->insert( std::make_pair(name, pDoc) );
}


/**
 *
 */
void CDocumentsCollection::Update( CTracesDocument* pDoc )
{
	iterator		pos;

	for (pos = begin(); pos != end(); ++pos)
		if ( pos->second == pDoc )
		{
			erase(pos);
			break;
		}

	Nyx::CAString		name( pDoc->Name().toStdString().c_str() );

	Insert(name, pDoc);
}


/**
 *
 */
CTracesDocument* CDocumentsCollection::Get( const Nyx::CAString& name ) const
{
	const_iterator		pos = find(name);

	if ( pos != end() )
		return pos->second;

	return NULL;
}


/**
 *
 */
void CDocumentsCollection::Clear()
{
	while ( !empty() )
	{
		iterator pos = begin();
		pos->second->Destroy();
		delete pos->second;
		erase(pos);
	}
}
