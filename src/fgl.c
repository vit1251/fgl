#include <windows.h>

#include "fglaux.h"

#include "fgl.h"
#include "fglb.h"


COLORREF m_color;

int fglColor(COLORREF color)
{
	m_color=color;

	return 0;
}

int fglClear()
{
	int x,y;

	for(y=0;y < height;y++) {
		for(x=0;x < width;x++) {
//			_SetPoint(m_fbuff,x,y,m_color);
			SetPoint(0,x,y,m_color);
			SetZ(m_zbuff, x, y, INT32_MAX);
		}
	}
	
	return 0;
}
