#ifndef __VIEWITEMS_HPP__
#define __VIEWITEMS_HPP__

#include <QSizeF>
#include <list>
#include <Nyx.hpp>
#include <NyxAssert.hpp>
#include "ViewItemPos.hpp"
#include "ViewItemsNodeObjectsPool.hpp"

class CViewItem;


/**
 *
 */
class CViewItems : public Nyx::CMemPoolObj<>
{
public:
    CViewItems( Nyx::CMemoryPool* pPool );
    virtual ~CViewItems();

    virtual void Add( CViewItem* pItem );
    virtual void RemoveFromClientSize( CViewItem* pItem );
    virtual void AddToClientSize( CViewItem* pItem );
    virtual CViewItemPos begin() const;
    virtual size_t ItemsCount() const;
    virtual const QSizeF& GetSize() const;
    virtual const QSizeF& GetLastLineSize() const;
    virtual const QSizeF& GetMaxLineSize() const;
    virtual void Clear(bool bDeleteItems = true);

    const CViewItems& operator += (CViewItems& items);

protected:


    template<class _Ty, class Pool>
    class MyAllocator
	{	// generic allocator for objects of class _Ty
    protected:

        Nyx::CObjectsPoolRef            m_refObjectsPool;

    public:
        typedef _Ty value_type;
        typedef value_type  *pointer;
        typedef value_type & reference;
        typedef const value_type  *const_pointer;
        typedef const value_type & const_reference;
        typedef size_t size_type;


	    template<class _Other>
		    struct rebind
		    {	// convert an allocator<_Ty> to an allocator <_Other>
		    typedef MyAllocator<_Other, Pool> other;
		    };

	    pointer address(reference _Val) const
		    {	// return address of mutable _Val
		    return (&_Val);
		    }

	    const_pointer address(const_reference _Val) const
		    {	// return address of nonmutable _Val
		    return (&_Val);
		    }

        MyAllocator()
		    {	// construct default allocator (do nothing)
                //m_refObjectsPool = Nyx::CObjectsPool::Alloc(2048, sizeof(_Ty));
                m_refObjectsPool = Pool::Instance();
		    }

        MyAllocator(const MyAllocator<_Ty, Pool>&)
		    {	// construct by copying (do nothing)
                m_refObjectsPool = Pool::Instance();
		    }

	    template<class _Other>
            MyAllocator(const MyAllocator<_Other, Pool>&)
		    {	// construct from a related allocator (do nothing)
                m_refObjectsPool = Pool::Instance();
		    }

	    template<class _Other>
		    MyAllocator<_Ty, Pool>& operator=(const MyAllocator<_Other, Pool>&)
		    {	// assign from a related allocator (do nothing)
		        return (*this);
		    }

	    void deallocate(pointer _Ptr, size_type)
		    {	// deallocate object at _Ptr, ignore size
		    //::operator delete(_Ptr);
                m_refObjectsPool->FreeMem(_Ptr);
		    }

	    pointer allocate(size_type _Count)
		    {	// allocate array of _Count elements
		    //return (_Allocate(_Count, (pointer)0));
                NyxAssert( _Count == 1, "invalid count value");
                return (pointer)m_refObjectsPool->AllocMem(sizeof(_Ty));
		    }

        pointer allocate(size_type _Count, const void *)
		    {	// allocate array of _Count elements, ignore hint
		    //return (allocate(_Count));
                NyxAssert( _Count == 1, "invalid cound value");
                return (pointer)m_refObjectsPool->AllocMem(sizeof(_Ty));
		    }

	    void construct(pointer _Ptr, const _Ty& _Val)
		    {	// construct object at _Ptr with value _Val
                std::_Construct(_Ptr, _Val);
		    }

	    void destroy(pointer _Ptr)
		    {	// destroy object at _Ptr
                std::_Destroy(_Ptr);
		    }

        size_type max_size() const
		    {	// estimate maximum array size
            size_type _Count = (size_type)(-1) / sizeof (_Ty);
		    return (0 < _Count ? _Count : 1);
		    }
	};

    typedef     std::list<CViewItem*, MyAllocator<CViewItem*, CViewItemsNodeObjectsPool> >       TViewItemsList;

    /**
     *
     */
    class XPosData : public CViewItemPos::XData
    {
    public:
        XPosData(const XPosData& data);
        XPosData(const TViewItemsList& rList, const TViewItemsList::const_iterator& pos, double y );

        virtual bool IsValid() const;
        virtual CViewItemPos::XData* Clone() const;

        virtual void MoveToNext();
        virtual void MoveToPrevious();
        virtual bool IsFirst() const;
        virtual bool IsLast() const;

        virtual bool IsOfType( CViewItemPos::EViewItemPosIdentifier id ) const;

        virtual bool IsEqual(const CViewItemPos::XData &data) const;

        virtual CViewItem* Item() const;
        virtual double Y() const;

    protected:

        TViewItemsList::const_iterator      m_Pos;
        const TViewItemsList*               m_pList;
        double                              m_Y;
    };

    /**
     *
     */
    class XPos : public CViewItemPos
    {
    public:
        XPos( const TViewItemsList& rList, const TViewItemsList::const_iterator& pos, double y );
    };

protected:

    TViewItemsList          m_Items;
    QSizeF                  m_Size;
    QSizeF                  m_LastLineSize;
    QSizeF                  m_MaxLineSize;
};


#endif // __VIEWITEMS_HPP__
