#include <windows.h>
#include <stdio.h>
#include <math.h>

#include "fgl.h"
#include "fgl3.h"

#include "fglu.h"

// Defi

#define dtoi(d) ((int)(d + 0.5f))

#ifndef M_PI
#define M_PI pi
#endif

#define DEBUG

#define cosf(a) cos(a)
#define sinf(a) sin(a)

// Constructor rect.

void fgluRect(float Length, float Width, float Height)
{
	float l = 20.0f;
	float z = 3.0f;
	COLORREF m_temp;
	
	// Save color.
	m_temp = m_color;
	m_color = RGB(192,192,192);
	
	// Point at -Width/2.0f, -Height/2.0f,-Length/2.0f.
	fglLine(-Width/2.0f - z, -Height/2.0f - z,-Length/2.0f - z,
			-Width/2.0f - z + l, -Height/2.0f - z,-Length/2.0f - z);
	fglLine(-Width/2.0f - z, -Height/2.0f - z,-Length/2.0f - z,
			-Width/2.0f - z, -Height/2.0f - z + l,-Length/2.0f - z);
	fglLine(-Width/2.0f - z, -Height/2.0f - z,-Length/2.0f - z,
			-Width/2.0f - z, -Height/2.0f - z,-Length/2.0f - z + l);
	
	// Point at -Width/2.0f, -Height/2.0f,+Length/2.0f.
	fglLine(-Width/2.0f - z, -Height/2.0f - z, +Length/2.0f + z,
			-Width/2.0f - z + l, -Height/2.0f - z, +Length/2.0f + z);
	fglLine(-Width/2.0f - z, -Height/2.0f - z, +Length/2.0f + z,
			-Width/2.0f - z, -Height/2.0f - z + l, +Length/2.0f + z);
	fglLine(-Width/2.0f - z, -Height/2.0f - z, +Length/2.0f + z,
			-Width/2.0f - z, -Height/2.0f - z, +Length/2.0f + z - l);
			
	// Point at -Width/2.0f, +Height/2.0f,-Length/2.0f.
	fglLine(-Width/2.0f - z, +Height/2.0f + z, -Length/2.0f - z,
			-Width/2.0f - z + l, +Height/2.0f + z, -Length/2.0f - z);
	fglLine(-Width/2.0f - z, +Height/2.0f + z, -Length/2.0f - z,
			-Width/2.0f - z, +Height/2.0f + z - l, -Length/2.0f - z);
	fglLine(-Width/2.0f - z, +Height/2.0f + z, -Length/2.0f - z,
			-Width/2.0f - z, +Height/2.0f + z, -Length/2.0f - z + l);			

	// Point at +Width/2.0f, -Height/2.0f,-Length/2.0f.	
	fglLine(+Width/2.0f + z, -Height/2.0f - z,-Length/2.0f - z,
			+Width/2.0f + z - l, -Height/2.0f - z,-Length/2.0f - z);
	fglLine(+Width/2.0f + z, -Height/2.0f - z,-Length/2.0f - z,
			+Width/2.0f + z, -Height/2.0f - z + l,-Length/2.0f - z);
	fglLine(+Width/2.0f + z, -Height/2.0f - z,-Length/2.0f - z,
			+Width/2.0f + z, -Height/2.0f - z,-Length/2.0f - z + l);
	
	// Point at +Width/2.0f, +Height/2.0f,-Length/2.0f.	
	fglLine(+Width/2.0f + z, +Height/2.0f + z,-Length/2.0f - z,
			+Width/2.0f + z - l, +Height/2.0f + z,-Length/2.0f - z);
	fglLine(+Width/2.0f + z, +Height/2.0f + z,-Length/2.0f - z,
			+Width/2.0f + z, +Height/2.0f + z - l,-Length/2.0f - z);
	fglLine(+Width/2.0f + z, +Height/2.0f + z,-Length/2.0f - z,
			+Width/2.0f + z, +Height/2.0f + z,-Length/2.0f - z + l);
	
	// Point at +Width/2.0f, +Height/2.0f,+Length/2.0f.	
	fglLine(+Width/2.0f + z, +Height/2.0f + z,+Length/2.0f + z,
			+Width/2.0f + z - l, +Height/2.0f + z,+Length/2.0f + z);
	fglLine(+Width/2.0f + z, +Height/2.0f + z,+Length/2.0f + z,
			+Width/2.0f + z, +Height/2.0f + z - l,+Length/2.0f + z);
	fglLine(+Width/2.0f + z, +Height/2.0f + z,+Length/2.0f + z,
			+Width/2.0f + z, +Height/2.0f + z,+Length/2.0f + z - l);
	
	// Point at -Width/2.0f, +Height/2.0f,+Length/2.0f.	
	fglLine(-Width/2.0f - z, +Height/2.0f + z,+Length/2.0f + z,
			-Width/2.0f - z + l, +Height/2.0f + z,+Length/2.0f + z);
	fglLine(-Width/2.0f - z, +Height/2.0f + z,+Length/2.0f + z,
			-Width/2.0f - z, +Height/2.0f + z - l,+Length/2.0f + z);
	fglLine(-Width/2.0f - z, +Height/2.0f + z,+Length/2.0f + z,
			-Width/2.0f - z, +Height/2.0f + z,+Length/2.0f + z - l);
			
	// Point at +Width/2.0f, -Height/2.0f, +Length/2.0f.	
	fglLine(+Width/2.0f + z, -Height/2.0f - z,+Length/2.0f + z,
			+Width/2.0f + z - l, -Height/2.0f - z,+Length/2.0f + z);
	fglLine(+Width/2.0f + z, -Height/2.0f - z,+Length/2.0f + z,
			+Width/2.0f + z, -Height/2.0f - z + l,+Length/2.0f + z);
	fglLine(+Width/2.0f + z, -Height/2.0f - z,+Length/2.0f + z,
			+Width/2.0f + z, -Height/2.0f - z,+Length/2.0f + z - l);			
	
	// Restore color.
	m_color = m_temp;
}

// Standart Primetive.

/* DONE (Vit1251#1#): Модель кубика (fgluBox) */

void fgluBox(float Length, float Width, float Height)
{
	float l = 50;

	// X
	fglQuad(-Width/2.0f, -Height/2.0f, -Length/2.0f,
			-Width/2.0f, -Height/2.0f, +Length/2.0f,
			-Width/2.0f, +Height/2.0f, +Length/2.0f,
			-Width/2.0f, +Height/2.0f, -Length/2.0f);
	fglQuad(+Width/2.0f, -Height/2.0f, -Length/2.0f,
			+Width/2.0f, +Height/2.0f, -Length/2.0f,
			+Width/2.0f, +Height/2.0f, +Length/2.0f,
			+Width/2.0f, -Height/2.0f, +Length/2.0f);

	// Y
	fglQuad(-Width/2.0f, -Height/2.0f, -Length/2.0f,
			-Width/2.0f, +Height/2.0f, -Length/2.0f,
			+Width/2.0f, +Height/2.0f, -Length/2.0f,
			+Width/2.0f, -Height/2.0f, -Length/2.0f);
	fglQuad(-Width/2.0f, -Height/2.0f, +Length/2.0f,
			+Width/2.0f, -Height/2.0f, +Length/2.0f,
			+Width/2.0f, +Height/2.0f, +Length/2.0f,
			-Width/2.0f, +Height/2.0f, +Length/2.0f);

	// Z
	fglQuad(-Width/2.0f, -Height/2.0f, -Length/2.0f,
			+Width/2.0f, -Height/2.0f, -Length/2.0f,
			+Width/2.0f, -Height/2.0f, +Length/2.0f,
			-Width/2.0f, -Height/2.0f, +Length/2.0f);
	fglQuad(-Width/2.0f, +Height/2.0f, -Length/2.0f,
			-Width/2.0f, +Height/2.0f, +Length/2.0f,
			+Width/2.0f, +Height/2.0f, +Length/2.0f,
			+Width/2.0f, +Height/2.0f, -Length/2.0f);
			
#ifdef DEBUG
	fgluRect(Length, Width, Height);
#endif
}

/* TODO (Vit1251#1#): Модель конуса (fgluCone) */

void fgluCone(float Radius1, float Radius2, float Height, long HeightSegments, long CapSegments, long Sides)
{
	// ...

#ifdef DEBUG
	fgluRect(2.0f*Radius1, 2.0f*Radius1, Height);
#endif
}

/* TODO (Vit1251#1#): Модель сферы (fgluSphere) */

void fgluSphere(float Radius, long Segments)
{
	// ...

#ifdef DEBUG
	fgluRect(2.0f*Radius, 2.0f*Radius, 2.0f*Radius);
#endif
}

/* TODO (Vit1251#1#): Модель гео-сферы (fgluGeoSphere) */

void fgluGeoSphere(float Radius, long Segments)
{
	// ...

#ifdef DEBUG
	fgluRect(2.0f*Radius, 2.0f*Radius, 2.0f*Radius);
#endif
}

/* DONE (Vit1251#1#): Модель цилиндра (fgluCylinder) */

void fgluCylinder(float Radius, float Height, long HeightSegments, long CapSegments, long Sides)
// Cylinder is drawing.
//
//			x=r*sinf(l);
//			y=r*cosf(l);
//			z=h;
//
{
	float s, h;

	float x,y,z;

	float x1,y1,z1;
	float x2,y2,z2;
	float x3,y3,z3;
	float x4,y4,z4;

	float ds = 2.0f*M_PI/Sides;
	float dh = Height/HeightSegments;

	// Down side.

	for(s=0.0f; s < 2.0f*M_PI; s += ds) {
		x1=Radius*sinf(s);
		y1=Radius*cosf(s);
		z1=h;

		x2=Radius*sinf(s+ds);
		y2=Radius*cosf(s+ds);

		fglTrangle(x1,y1,-Height/2.0f, x2, y2, -Height/2.0f, 0,0, -Height/2.0f );
	}

	// Center side's.

	for(s=0.0f; s < 2.0f*M_PI; s += ds) {
		for(h=-Height/2.0f; h < Height/2.0f; h += dh) {

// Quadric based.
//
			x1=Radius*sinf(s);
			y1=Radius*cosf(s);
			z1=h;

			x2=Radius*sinf(s+ds);
			y2=Radius*cosf(s+ds);
			z2=h;

//			x3=Radius*sinf(s+ds);
//			y3=Radius*cosf(s+ds);
			x3=x2;
			y3=y2;
			z3=h+dh;

//			x4=Radius*sinf(l);
//			y4=Radius*cosf(l);
			x4=x1;
			y4=y1;
			z4=z3;
//			z4=h+dh;

			fglQuad(+x1,+y1,-z1, +x2,+y2,-z2, +x3,+y3,-z3, +x4,+y4,-z4);
		}
	}
	
	// Front side.

	for(s=0.0f; s < 2.0f*M_PI; s += ds) {
		x1=Radius*sinf(s);
		y1=Radius*cosf(s);
		z1=h;

		x2=Radius*sinf(s+ds);
		y2=Radius*cosf(s+ds);

		fglTrangle(0,0, Height/2.0f, x2, y2, Height/2.0f, x1,y1,Height/2.0f );
	}
	
#ifdef DEBUG
	fgluRect(Height, 2.0f*Radius, 2.0f*Radius);
#endif
}

/* TODO (Vit1251#1#): Модель трубы (fgluTube) */

void fgluTube(float Radius1, float Radius2, long Height, long HeightSegments, long CapSegments, long Sides)
{
	// ...

#ifdef DEBUG
	fgluRect(Height, 2.0f*Radius1, 2.0f*Radius1);
#endif
}

/* TODO (Vit1251#1#): Модель тора (fgluTorus) */

void fgluTorus(float Radius1, float Radius2, float Rotation, float Twist, long Segments, long Sides)
{
	// ...

#ifdef DEBUG
	fgluRect(2.0f*Radius1 + 2.0f*Radius2, 2.0f*Radius1 + 2.0f*Radius2, 2.0f*Radius2);
#endif
}

/* TODO (Vit1251#1#): Модель пирамиды (fgluPyramid) */

void fgluPyramid(float Width, float Depth, float Height)
{
	// ... 4-x
	
#ifdef DEBUG
	fgluRect(Depth, Width, Height);
#endif
}

/* TODO (Vit1251#1#): Модель плоскость (fgluPlane) */

void fgluPlane(float Length, float Width, long LengthSegs, long WidthSegs)
{
	float ddw, ddl;
	float dw = WidthSegs;
	float dl = LengthSegs;
	int w, l;

	ddl=0.0f;
	for(l=0; l < LengthSegs; l++) {
		ddw=0.0f;
		for(w=0; w < WidthSegs; w++ ) {
			fglQuad( ddw,ddl,0, ddw,ddl+dl,0, ddw+dw,ddl+dl,0, ddw+dw,ddl,0 );
			ddw += dw;
		}
		ddl += dl;
	}
}

// Old style primitives.

extern unsigned char *m_fbuff;
extern COLORREF m_color;

int oldfgluSphere(float r)
{
	float a,b;
	float x,y,z;

	float x1,y1,z1;
	float x2,y2,z2;
	float x3,y3,z3;
	float x4,y4,z4;


	int c=0;

	// Идея создать *data из float и передать для fglNurb ;)
	// А вообще надо покрутить for-ы именно из-за них все ужасно

	float db = 2.0f*M_PI/15.0; // Where 10 is coeff..
	float da = M_PI/15.0; // Where 10 is coeff..

	for(a=0.0f; a < M_PI; a = a + da) {
		for(b=0.0f; b < 2.0f*M_PI; b = b + db) {
//			x=r*cosf(b)*cosf(a);
//			y=r*cosf(b)*sinf(a);
//			z=r*sinf(b);

			x1=r*cosf(b)*cosf(a);
			y1=r*cosf(b)*sinf(a);
			z1=r*sinf(b);

			x2=r*cosf(b)*cosf(a+da);
			y2=r*cosf(b)*sinf(a+da);
			z2=r*sinf(b);

			x3=r*cosf(b+db)*cosf(a);
			y3=r*cosf(b+db)*sinf(a);
			z3=r*sinf(b+db);

			x4=r*cosf(b+db)*cosf(a+da);
			y4=r*cosf(b+db)*sinf(a+da);
			z4=r*sinf(b+db);

//			fglColor(RGB(50*b,255,0));

			fglQuad(+x1,+y1,-z1, +x2,+y2,-z2, +x4,+y4,-z4, +x3,+y3,-z3);
				
//			fglPixel(px+x,py+y,pz+z);
		}
	}
	return 0;
}

int oldfgluPiramid(float h)
{
	float r;
	float dr;
	float l=30.0f;
	
	dr = 2*M_PI/8.0f;

	for(r=0.0f; r < 2*M_PI; r += dr) {
		fglTrangle(l*sinf(r+dr),0,l*cosf(r+dr), l*sinf(r), 0, l*cosf(r), 0, 0, 0);
		fglTrangle(l*sinf(r),0,l*cosf(r), l*sinf(r + dr), 0, l*cosf(r + dr), 0, h, 0);
	}

	return 0;
}

// Extended Primetive.

#define CEL 30

int oldfgluMap(int width, int height, float *data)
{
	int x, y;

	// Drawing the Mesh ;)
	for(y=0; y < height; y++) {
		for(x=0; x < width; x++) {

			if (( x < width-1) && (y < height-1)) {
				COLORREF m_temp;
				
				m_temp = m_color;

				m_color = fglBlend(m_color, RGB(0,0,0), CEL*(y), 100);

				fglTrangle(CEL*(x), CEL*data[x + width*y], CEL*(y), CEL*(x+1), CEL*data[x+1 + width*y], CEL*y, CEL*(x), CEL*data[x + width*(y+1)], CEL*(y+1));
				
				m_color = m_temp;
				m_color = fglBlend(m_color, RGB(0,0,0), CEL*(y), 150);
				
				fglTrangle(CEL*(x+1), CEL*data[x+1 + width*(y+1)], CEL*(y+1), CEL*(x+1), CEL*data[x+1 + width*y], CEL*y, CEL*(x), CEL*data[x + width*(y+1)], CEL*(y+1));

				m_color = m_temp;
			}
		}
	}
	return 0;
}
