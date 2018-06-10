// Declarate enternal buffer.
//
extern int width;
extern int height;

extern unsigned char *m_fbuff;
extern unsigned char *m_zbuff;

#define GetZ(buffer, x, y)              ((buffer != NULL) && (0 <= x) && (x < width) && (0 <= y) && (y < height)?*(((DWORD *)(buffer)) + width*y + x):0)
#define SetZ(buffer, x, y, z)           ((buffer != NULL) && (0 <= x) && (x < width) && (0 <= y) && (y < height)?*(((DWORD *)(buffer)) + width*y + x) = z:0)

//#define _GetPoint(buffer, x,y)		    (((buffer != NULL) && ((0 <= x) && (x < width)) && ((0 <= y) && (y < height)))?*(((COLORREF *)(buffer)) + width*y + x):0)
//#define _SetPoint(buffer, x, y, color)	(((buffer != NULL) && ((0 <= x) && (x < width)) && ((0 <= y) && (y < height)))?*(((COLORREF *)(buffer)) + width*y + x) = color:0)

// External prototype.
//
int init(void);
int draw(void);
int deinit(void);
int keyboard(int nVirtKey);

//int resize(int width, int height);
