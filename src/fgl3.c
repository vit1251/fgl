#include <windows.h>
#include <math.h>

#include "fglaux.h"
#include "fgl.h"
#include "fglb.h"
#include "fglt.h"
#include "fgle.h"

#define dtoi(d) ((int)(d + 0.5f))
#define FOV 3.14 // Angle locking 180

#define sinf(x) sin(x)
#define cosf(x) cos(x)

// Drawing and etc.

/* DONE (Vit1251#1#): Cортировка по глубине (алгоритм Z-Buffer'а) */
/* TODO (Vit1251#1#): Добавить нормальное смешение цвета (Alpha) */

int fglPixel(float x1, float y1, float z1)
{
#ifdef DEBUG
	syslog("%s: fglPixel()", __FILE__ );
#endif
	
	double cc[4];
	double x,y;
	int bx, by;

	// Color translation.

	COLORREF m_temp;
	
	char r;
	char g;
	char b;	

	m_temp=m_color;

	r=GetRValue(m_temp);
	g=GetGValue(m_temp);
	b=GetBValue(m_temp);

	m_temp = RGB(b,g,r); // Microsoft bitmap MUST die! Fuck...
	
	// Matrix.
	cc[0]=x1; cc[1]=y1; cc[2]=z1; cc[3]=1.0f;

	_mmul1(dm, cc);

#define dist	300.0f

	if (cc[2] > dist)
		return 0;

#define PERSPECTIVE

#ifdef ISO
	x = cc[0] + cc[2];
	y = cc[1] + cc[2]/2;
#endif

#ifdef PERSPECTIVE
	x = cc[0] * dist / (cc[2] + dist);
	y = cc[1] * dist / (cc[2] + dist);
#endif

#ifdef PERSPECTIVE2
	float kx = sqrt( (+0.5f*cc[0] - 0.5f*cc[1])*(+0.5f*cc[0] - 0.5f*cc[1]) ) / 100.0f;
	float ky = 1.0f;

	x = (+0.5f*cc[0] - 0.5f*cc[1]);
	y = (cc[2] + +0.25f*cc[0] + 0.25f*cc[1]);
#endif

	bx = width/2 + dtoi(x);
	by = height/2 - dtoi(y);

	if ((bx < width) && (by < height)) {

//	if (GetZ(m_zbuff, bx, by) < INT32_MAX)
//		m_temp = fglBlend(m_temp, GetPoint(m_fbuff, bx, by), dtoi(cc[2]), GetZ(m_zbuff, bx, by) );

		if ( (int)dtoi(cc[2]) < (int)GetZ(m_zbuff, bx, by) ) {
//			_SetPoint(m_fbuff, bx, by, m_temp );
			SetPoint(0, bx, by, m_temp);
			SetZ(m_zbuff, bx, by, dtoi(cc[2]));
		}
		
	}

	return 0;
}

/* TODO (Vit1251#1#): Сделать проверку 26-связности точек, если нет то уменьшить временно шаг */

int fglLine(float x1, float y1, float z1, float x2, float y2, float z2)
{
#ifdef DEBUG
	syslog("%s: fglLine()", __FILE__ );
#endif
	
	float dx, dy, dz;
	float kdx, kdy, kdz;
	float ddx, ddy, ddz;

	float len;

	dx = x2-x1;
	dy = y2-y1;
	dz = z2-z1;

	len = sqrt(dx*dx + dy*dy + dz*dz);

	kdx = dx / len;
	kdy = dy / len;
	kdz = dz / len;

	ddx=ddy=ddz=0.0f;

	if ((fabs(dx) > 0.0f)&& (fabs(dx) >= fabs(dy)) && (fabs(dx) >= fabs(dz))) {
		// Dx is max.
		
		while ( fabs(ddx) < fabs(dx) ) {
			fglPixel( x1+ddx, y1+ddy, z1+ddz );

			ddx += kdx;
			ddy += kdy;
			ddz += kdz;
		}
	} else
	if ((fabs(dy) > 0.0f) && (fabs(dy) >= fabs(dx)) && (fabs(dy) >= fabs(dz))) {
		// Dy is max.
		
		while ( fabs(ddy) < abs(dy) ) {
			fglPixel( x1+ddx, y1+ddy, z1+ddz );

			ddx += kdx;
			ddy += kdy;
			ddz += kdz;
		}
	} else
	if ((fabs(dz) > 0.0f) && (fabs(dz) >= fabs(dx)) && (fabs(dz) >= fabs(dy))) {
		// Dz is max.
		
		while ( fabs(ddz) < fabs(dz) ) {
			fglPixel( x1+ddx, y1+ddy, z1+ddz );

			ddx += kdx;
			ddy += kdy;
			ddz += kdz;
		}
	}

	return 0;
}

/* TODO (Vit1251#1#): Отсекать нелецевых граней фигуры (угол между нормалью и наблюдателем) */

int fglTrangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{
#ifdef DEBUG
	syslog("%s: fglTrangle()", __FILE__ );
#endif
	
	if (m_flag & FGL_NORMAL)
		fglNormal(x1, y1, z1, x2, y2, z2, x3, y3, z3);

	if (m_flag & FGL_WIRE) {
		fglLine(x1, y1, z1, x2, y2, z2);
		fglLine(x2, y2, z2, x3, y3, z3);
		fglLine(x3, y3, z3, x1, y1, z1);
	} else {
		float dx, dy, dz;
		float kdx, kdy, kdz;
		float ddx, ddy, ddz;
		float len;
		float step;
		
////////////////////////////////////////VERTEX SORT///////////////

		double a, b, c;
		double xt1, yt1, zt1;
		double xt2, yt2, zt2;
		double xt3, yt3, zt3;		
		
		a = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) + (z2-z1)*(z2-z1) );
		b = sqrt( (x3-x2)*(x3-x2) + (y3-y2)*(y3-y2) + (z3-z2)*(z3-z2) );
		c = sqrt( (x1-x3)*(x1-x3) + (y1-y3)*(y1-y3) + (z1-z3)*(z1-z3) );

		if ((a > b) && (a > c)) {
			// Nothing to do.
		} else
		if ((b > a) && (b > c)) {
			// Rotate.
			
			xt1=x1; yt1=y1; zt1=z1;
			xt2=x2; yt2=y2; zt2=z2;
			xt3=x3; yt3=y3; zt3=z3;
			
			x1 = xt2; y1 = yt2; z1 = zt2;
			x2 = xt3; y2 = yt3; z2 = zt3;
			x3 = xt1; y3 = yt1; z3 = zt1;

		} else
		if ((c > a) && (c > b)) {
			// Rotate.
			
			xt1=x1; yt1=y1; zt1=z1;
			xt2=x2; yt2=y2; zt2=z2;
			xt3=x3; yt3=y3; zt3=z3;
			
			x1 = xt3; y1 = yt3; z1 = zt3;
			x2 = xt1; y2 = yt1; z2 = zt1;
			x3 = xt2; y3 = yt2; z3 = zt2;
		}
		
////////////////////////////////////////LINE//////////////////////

		// Vertex 1 -> 2 always longer other.

		dx = x2-x1;
		dy = y2-y1;
		dz = z2-z1;

		len = sqrt(dx*dx + dy*dy + dz*dz);

		kdx = dx / len;
		kdy = dy / len;
		kdz = dz / len;

		ddx=ddy=ddz=0.0f;

		if ((fabs(dx) > 0.0f)&& (fabs(dx) >= fabs(dy)) && (fabs(dx) >= fabs(dz))) {
			// Dx is max.
		
			for (step=0.0f; fabs(step) < fabs(x2-x1); step += kdx) {
				fglLine( x1 + ddx, y1 + ddy, z1 + ddz, x3, y3, z3 );

//				fglColor(m_color+1);

				ddx += kdx; ddy += kdy; ddz += kdz;
			}
		} else
		if ((fabs(dy) > 0.0f) && (fabs(dy) >= fabs(dx)) && (fabs(dy) >= fabs(dz))) {
			// Dy is max.
		
			for (step=0.0f; fabs(step) < fabs(y2-y1); step += kdy) {
				fglLine( x1 + ddx, y1 + ddy, z1 + ddz, x3, y3, z3 );

//				fglColor(m_color+1);
	
				ddx += kdx; ddy += kdy; ddz += kdz;
			}
		} else
		if ((fabs(dz) > 0.0f) && (fabs(dz) >= fabs(dx)) && (fabs(dz) >= fabs(dy))) {
			// Dz is max.
		
			for (step=0.0f; fabs(step) < fabs(z2-z1); step += kdz) {
				fglLine( x1 + ddx, y1 + ddy, z1 + ddz, x3, y3, z3 );

//				fglColor(m_color+1);

				ddx += kdx; ddy += kdy; ddz += kdz;
			}
		}

//////////////////////////////////////........////////////////////

//		fglLine(x1, y1, z1, x2, y2, z2);
//		fglLine(x2, y2, z2, x3, y3, z3);
//		fglLine(x3, y3, z3, x1, y1, z1);
	}

	return 0;
}

int fglQuad(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4)
{
#ifdef DEBUG
	syslog("%s: fglQuad()", __FILE__ );
#endif

	COLORREF m_temp;
	double z;

	z = (z1+z2+z3)/3.0f;
	m_temp = m_color;
	m_color = fglBlend(m_color, RGB(0,0,0), -dtoi(z)/10, 0 );
	
	fglTrangle(x1, y1, z1, x2, y2, z2, x3, y3, z3);
	fglTrangle(x1, y1, z1, x3, y3, z3, x4, y4, z4);

	m_color = m_temp;

	return 0;
}

void fglCross(int l)
{
#ifdef DEBUG
	syslog("%s: fglCross()", __FILE__ );
#endif
	
	// X (red)
	fglColor(RGB(192,0,0));
	fglLine(0, 0, 0, +l, 0, 0);

	// Y (green)
	fglColor(RGB(0,192,0));
	fglLine(0, 0, 0, 0, +l, 0);

	// Z (blue)
	fglColor(RGB(0,0,192));
	fglLine(0, 0, 0, 0, 0, +l);
}


#define LEN_NORMAL 35

int fglNormal(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3)
{
#ifdef DEBUG
	syslog("%s: fglNormal()", __FILE__ );
#endif
	
	double x,y,z;
	double cc[4];
	double len;

	// Calc Normal.
	cc[0] = (y1-y2)*(z1-z3) - (z1-z2)*(y1-y3);
	cc[1] = (z1-z2)*(x1-x3) - (x1-x2)*(z1-z3);
	cc[2] = (x1-x2)*(y1-y3) - (y1-y2)*(x1-x3);
	cc[3]=1.0f;

	len = sqrt(cc[0]*cc[0] + cc[1]*cc[1] + cc[2]*cc[2]);
	
	x=(x1+x2+x3) / 3.0f;
	y=(y1+y2+y3) / 3.0f;
	z=(z1+z2+z3) / 3.0f;

	fglLine(x,y,z, x + LEN_NORMAL*cc[0]/len, y + LEN_NORMAL*cc[1]/len, z + LEN_NORMAL*cc[2]/len);

	return 0;
}
