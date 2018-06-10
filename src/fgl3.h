extern COLORREF m_color;

// Color, texture...
int fglColor(COLORREF color);

// Drawing primetive.
int fglClear(void);
//int fglColor(struct TColor c);
int fglPixel(float x1, float y1, float z1);
//int fglPixel(struct TVertex a);
int fglLine(float x1, float y1, float z1, float x2, float y2, float z2);
//int fglLine(struct TVertex a, struct TVertex b);
int fglTrangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
//int fglTrangle(strct TVertex a, strct TVertex b, strct TVertex c);
int fglQuad(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4);

// Debug function drawing normal for algorithm search of depth.
int fglNormal(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);
void fglCross(int l);
