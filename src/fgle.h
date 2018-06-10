#define FGL_WIRE    0x01   // Wire
#define FGL_NORMAL  0x02   // Noramle
#define FGL_ALPHA   0x04   // Alpha chanell

// Declarate external.

extern long m_flag;

// Flag Function

void fglEnable(int flag);
void fglDisable(int flag);

// Color ext.: Blending

COLORREF fglBlend(COLORREF color1, COLORREF color2, int x1, int x2);
