#include <windows.h>

// Declaration.

long m_flag;

// Internal enable/disable extension flag.

void fglEnable(int flag)
{
	m_flag = m_flag | flag;
}

void fglDisable(int flag)
{
	m_flag = m_flag & ~flag;
}

// Color ext.: Blending function (overlapped ?)

COLORREF fglBlend(COLORREF color1, COLORREF color2, int x1, int x2)
{
	int r,g,b;
	int x;

	while (x1 <= 0)
		x1++;
	while (x2 <= 0)
		x2++;		

	x = x1 + x2;
	
	r = (x1*GetRValue(color1) + x2*GetRValue(color2))/x;
	g = (x1*GetGValue(color1) + x2*GetGValue(color2))/x;
	b = (x1*GetBValue(color1) + x2*GetBValue(color2))/x;

	return RGB(r,g,b);
}
