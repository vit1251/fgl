// Constructor rect.
//
void fgluRect(float Length, float Width, float Height);

// Standart primitives.
//
void fgluBox(float Length, float Width, float Height);
void fgluCone(float Radius1, float Radius2, float Height, long HeightSegments, long CapSegments, long Sides);
void fgluSphere(float Radius, long Segments);
void fgluGeoSphere(float Radius, long Segments);
void fgluCylinder(float Radius, float Height, long HeightSegments, long CapSegments, long Sides);
void fgluTube(float Radius1, float Radius2, long Height, long HeightSegments, long CapSegments, long Sides);
void fgluTorus(float Radius1, float Radius2, float Rotation, float Twist, long Segments, long Sides);
void fgluPyramid(float Width, float Depth, float Height);
void fgluPlane(float Length, float Width, long LengthSegs, long WidthSegs);

// Old style.
//
int oldfgluSphere(float r);
int oldfgluPiramid(float h);
int oldfgluMap(int width, int height, float *data);
