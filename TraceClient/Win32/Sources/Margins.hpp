#ifndef _MARGINS_HPP_
#define _MARGINS_HPP_


/**
 *
 */
public ref class CMargins
{
public:
	CMargins();
	virtual ~CMargins();

	property float Left
	{
		float get() { return m_Left; }
		void set(float m) { m_Left = m; }
	}

	property float Right
	{
		float get() { return m_Right; }
		void set(float m) { m_Right = m; }
	}

	property float Top
	{
		float get() { return m_Top; }
		void set(float m) { m_Top = m; }
	}

	property float Bottom
	{
		float get() { return m_Bottom; }
		void set(float m) { m_Bottom = m; }
	}

protected:

	float			m_Left;
	float			m_Right;
	float			m_Top;
	float			m_Bottom;
};


#endif // _MARGINS_HPP_
