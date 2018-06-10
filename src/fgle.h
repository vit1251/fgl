#ifndef __FGLE_H__
#define __FGLE_H__

#ifdef WIN32
typedef COLORREF color_t;
#else
typedef long color_t;
#endif

#define FGL_WIRE    0x01   // Wire
#define FGL_NORMAL  0x02   // Noramle
#define FGL_ALPHA   0x04   // Alpha chanell

// Declarate external.

extern long m_flag;

// Flag Function

void fglEnable(int flag);
void fglDisable(int flag);

// Color ext.: Blending

color_t fglBlend(color_t color1, color_t color2, int x1, int x2);

#endif /* __FGLE_H__ */
