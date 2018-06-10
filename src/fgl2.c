#include <windows.h>

#include "fgl3.h"

inline int fglPixel2(int x1, int y1)
{
	fglPixel( (float)x1, (float)y1, 0.0f );	

	return 0;
}

inline int fglLine2(int x1, int y1, int x2, int y2)
{
	fglLine( (float)x1, (float)y1, 0.0f, (float)x2, (float)y2, 0.0f);
	
	return 0;
}
