#ifndef _DOCUMENTSCOLLECTION_HPP_
#define _DOCUMENTSCOLLECTION_HPP_

#include <map>
#include <Nyx.hpp>

class CTracesDocument;

/**
 *
 */
class CDocumentsCollection : public std::map<Nyx::CAString, CTracesDocument*>
{
public:
	CDocumentsCollection();
	virtual ~CDocumentsCollection();

    virtual void Insert( const Nyx::CAString& name, CTracesDocument* pDoc );
    virtual void Update( CTracesDocument* pDoc );

    CTracesDocument* Get( const Nyx::CAString& name ) const;

	virtual void Clear();
};



#endif // _DOCUMENTSCOLLECTION_HPP_
