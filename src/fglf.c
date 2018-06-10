#include <windows.h>

#include "fglaux.h"
#include "fgl.h"

/* DONE (Vit1251#1#): Размытие (fglfBlur) */

int fglfBlur()
{
	COLORREF color;
	int r,g,b;
	int x,y;
	int len;

	for(y=0; y < height; y++) {
		for(x=0; x < width; x++) {
			// Clear value.
			r = 0;
			g = 0;
			b = 0;

			// Center pixel.
			color = GetPoint(m_fbuff, x-1, y);
			r += GetRValue(color);
			g += GetGValue(color);
			b += GetBValue(color);

			// Center pixel.
			color = GetPoint(m_fbuff, x+1,y);
			r += GetRValue(color);
			g += GetGValue(color);
			b += GetBValue(color);

			// Center pixel.
			color = GetPoint(m_fbuff, x,y-1);
			r += GetRValue(color);
			g += GetGValue(color);
			b += GetBValue(color);

			// Center pixel.
			color = GetPoint(m_fbuff, x,y+1);
			r += GetRValue(color);
			g += GetGValue(color);
			b += GetBValue(color);

			// Center pixel.
			color = GetPoint(m_fbuff, x,y);
			r += 4*GetRValue(color);
			g += 4*GetGValue(color);
			b += 4*GetBValue(color);

			// Coeff value.
			r /= 8;
			g /= 8;
			b /= 8;

			SetPoint(m_fbuff, x, y, RGB(r,g,b));
		}
	}

	return 0;
}

/* TODO (Vit1251#1#): Эффект. Четкие края (fglfSharp) */

int fglfSharp()
{
	// ...
}

/* TODO (Vit1251#1#): Эффект. Размытие в движении (fglfMotion) */

int fglfMotion()
{
	// ...
}
