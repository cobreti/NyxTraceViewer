#ifndef _UICOLORSETTINGS_HPP_
#define _UICOLORSETTINGS_HPP_


using namespace System::Drawing;


public ref class CUIColorSettings
{
public:
	CUIColorSettings();
	virtual ~CUIColorSettings();

	virtual void Init();
	virtual void Terminate();
};


#endif // _UICOLORSETTINGS_HPP_
