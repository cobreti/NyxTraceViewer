#ifndef _UISENSORCREATOR_HPP_
#define _UISENSORCREATOR_HPP_


class CUISensor;
class CStatusUpdater;


/**
 *
 */
class CUISensorCreator
{
public:
	CUISensorCreator() {}
	virtual ~CUISensorCreator() {}

	virtual CUISensor* CreateUISensor(void* pCtrl, const CStatusUpdater& rUpdater) = 0;
};


/**
 *
 */
template <class C>
class TUISensorCreator : public CUISensorCreator
{
public:
	TUISensorCreator() : CUISensorCreator() {}
	virtual ~TUISensorCreator() {}

	virtual CUISensor* CreateUISensor(void* pCtrl, const CStatusUpdater& rUpdater)
	{
		return new C(pCtrl, rUpdater);
	}

};


#endif // _UISENSORCREATOR_HPP_
