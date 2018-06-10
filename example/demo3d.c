#include <windows.h>
#include <math.h>

#include "fglaux.h"
#include "fgl.h"
#include "fglb.h"
#include "fgl2.h"
#include "fgl3.h"
#include "fglu.h"
#include "fglf.h"
#include "fgle.h"
#include "fglt.h"
#include "fgls.h"
#include "key.h"

// Definition.

#define dtoi(d) ((int)(d + 0.5f))

#ifndef M_PI
#define M_PI pi
#endif

#define A1 M_PI/3.0f
#define A2 2.0f*M_PI/3.0f
#define A3 0.0f

// Global flags (library)

char m_alpha;
char m_normal;
char m_wire;

// Local flags (filter)

char m_freeze;
char m_cross;
char m_blur;
char m_ax, m_ay, m_az;

// Cameras.

static float m_anglex, m_angley, m_anglez;
static float m_ddx, m_ddy, m_ddz;
static float m;

float data[10][10];

int init()
{
/*
	// Change video mode.
	static DEVMODE devMode;

	devMode.dmSize=sizeof(DEVMODE);
//	devMode.dmDriverExtra=NULL;
	devMode.dmBitsPerPel=32;
	devMode.dmPelsWidth=640;
	devMode.dmPelsHeight=480;
	devMode.dmFields=DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	ChangeDisplaySettings(&devMode, CDS_SET_PRIMARY);
*/

	int i,j;
	
	// Set flag default value.
	m_alpha=0;	// Off
	m_normal=1;	// Off
	m_wire=1;	// Off
	m_freeze=0;	// Off

	m_cross=0;	// Off
	m_blur=0;   // Off
	m_ax=0;     // On
	m_ay=1;     // Off
	m_az=0;     // Off

	m_anglex=m_angley=m_anglez=0.0f;	// Rotate
	m_ddx=m_ddy=m_ddz=0.0f;			// Translate
	m=1.0f;					// Zoom

	srand(time(NULL));

	for(i=0;i<10;i++) {
		for(j=0;j<10;j++) {
			data[i][j]=(float)(rand()%50) / 10.0f;
		}
	}

	m_fbuff = malloc(width*height*sizeof(DWORD));
	m_zbuff = malloc(width*height*sizeof(DWORD));

	fglLoadImage(0, "background.bmp");
	fglLoadImage(1, "bax1.bmp");	
	fglLoadImage(3, "cosmos.bmp");	

	return 0;
}

static char *line[1] = {"Presenting below work is not demoscrene work in full measure."};
static long frame = 0;

int draw(void)
{
	static char buff[200];
	static DWORD tick;

	if (tick+10 >= GetTickCount())
		return;
		
	tick = GetTickCount();

	// Clear buffer.

	fglColor(RGB(0,0,0));
	fglClear();

	// Loading identity matrix.
	fglLoadIdentity();

	// Start rendering scene.
	
	if ((0 < frame) && (frame < 25*25)) {
		static float anglex=0.0f;
		static float angle;
		static float len;
		static int i,j,c;

	
		for(i=0; i<100;i++) {
			float sa, ca;

			// Line.

			fglColor(RGB(rand()%255, rand()%255, rand()%255));

			angle = (rand() % 314/2) / 100.0f;
			
			sa = sin(angle);
			ca = cos(angle);			
			
			len = rand()%100;

			// Corner.
			fglLine2(-width/2,-height/2,-width/2 + len*ca, -height/2 + len*sa);
			fglLine2(+width/2,-height/2,+width/2 - len*ca, -height/2 + len*sa);
			fglLine2(-width/2,+height/2,-width/2 + len*ca, +height/2 - len*sa);
			fglLine2(+width/2,+height/2,+width/2 - len*ca, +height/2 - len*sa);
			
			// Center.
			fglLine2(0,0, -len/4*ca, -len/4*sa);
			fglLine2(0,0, -len/4*ca, +len/4*sa);
			fglLine2(0,0, +len/4*ca, -len/4*sa);
			fglLine2(0,0, +len/4*ca, +len/4*sa);

			// Top.
			fglLine2(0,height/2, -len/2*ca, height/2-len/2*sa);
			fglLine2(0,height/2, +len/2*ca, height/2-len/2*sa);
			
			// Left
			fglLine2(-width/2,0, -width/2 + len/2*ca, -len/2*sa);
			fglLine2(-width/2,0, -width/2 + len/2*ca, +len/2*sa);

			// Right
			fglLine2(width/2,0, width/2 - len/2*ca, -len/2*sa);
			fglLine2(width/2,0, width/2 - len/2*ca, +len/2*sa);
		}

		fglColor(RGB(0, 0, 128));
		fglsText(0, width - 3*frame + 1, height - 20 + 1, line[0], strlen(line[0]) );

		fglColor(RGB(255, 0, 0));
		fglsText(0, width - 3*frame, height - 20, line[0], strlen(line[0]) );

	} else
	if ((25*25 < frame) && (frame < 1600)) {
		static float angle = 0.0f;
		static float dy = 2*M_PI/360;
		// Show status

		fglColor(RGB(255,0,255));
		sprintf(buff, "%.2f", angle);
		fglsText(0, 100, 100, buff, strlen(buff));
		
		// Rotate.
		
		if (angle < 0.0f) {
			if (angle < -5.0f)
				fglRotateZ(angle+5.0f);
			fglRotateX(angle);
		} else
			fglRotateY(angle);

		fglColor(RGB(0,0,255));		
		fgluBox(80, 80, 80);
		fgluRect(80, 80, 80);

		if (frame == 1000)
			dy = -dy*2;

		angle += dy;	
	} else
	if ((1600 < frame) && (frame < 2400)) {
		static float angle = 0.0f;

		if (frame == 1600) {
			angle=0.0f;
		}
		
		// Show status

		fglColor(RGB(255,0,255));
		sprintf(buff, "%.2f", angle);
		fglsText(0, 50, 50, buff, strlen(buff));
		
		// Rotate.
		
		if (angle < 2*M_PI) {
			fglRotateX(-angle);
		} else
		fglRotateY(angle);
		
		fglColor(RGB(0,0,255));		
		fgluCylinder(85, 60, 3, 1, 16);

		angle += 2*M_PI/360;	
	} else
	if ((2400 < frame) && (frame < 3400)) {	
		#define N 3
		static char *line[2*N] = {"code", "_vit12",
								"idea", "plot",
								"gfx", "Gog"};
		static float ddy;
		int i;

		if (frame == 2400) {
			ddy=-200.0f;
		}

		for (i=0; i<N; i++) {
			fglColor(RGB(0,255,0));
			fglsText(0, -8*i-ddy,0, line[2*i], strlen(line[2*i]));
			fglColor(RGB(0,128,0));
			fglsText(0, -8*i-ddy,0, line[2*i+1], strlen(line[2*i+1]));			
		}
		
		ddy += 1.0f;
	} else
	if ((3400 < frame) && (4000 < frame)) {
		static float anglex = 0.0f;
		float x,y,z;
		float a, b;
		static float r=100.0f;

		// Идея создать *data из float и передать для fglNurb ;)
		// А вообще надо покрутить for-ы именно из-за них все ужасно

		float db = 2.0f*M_PI/15.0; // Where 10 is coeff..
		float da = M_PI/15.0; // Where 10 is coeff..

		fglRotateX(anglex += 0.1f);

		for(a=0.0f; a < M_PI; a = a + da) {
			for(b=0.0f; b < 2.0f*M_PI; b = b + db) {
				x=r*cosf(b)*cosf(a);
				y=r*cosf(b)*sinf(a);
				z=r*sinf(b);

				fglColor(RGB(100,100,100));				
				fglLine(0,0,0, x,y,z);
			}
		}
		
	} else
	if (4000 < frame) {
		frame = 0;
	}

	if (!m_freeze)
		frame++;

	fglUpdate();

	return 0;
}

int keyboard(int nVirtKey)
{
#ifdef DEBUG
	syslog("keyboard()");
#endif	
	
	switch(nVirtKey)
	{
		case VK_HOME:
			m_anglex=m_angley=m_anglez=0.0f;
			m_ddx=m_ddy=m_ddz=0.0f;
			break;


		case VK_N:
			m_normal = (m_normal+1) % 2;
			break;

		case VK_W:
			m_wire = (m_wire+1) % 2;
			break;

		case VK_A:
			m_alpha = (m_alpha+1) % 2;
			break;

		case VK_C:
			m_cross = (m_cross+1) % 2;
			break;

		case VK_B:
			m_blur = (m_blur+1) % 2;
			break;
			
		case VK_M:
			m = 1.0f;
			break;			


		case VK_X:
			if ( GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT) )
				m_anglex = m_anglex - 0.01f; else
				m_anglex = m_anglex + 0.01f;

			if (GetAsyncKeyState(VK_CONTROL))
				m_ax = (m_ax + 1) % 2;
			break;

		case VK_Y:               
			if ( GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT) )
				m_angley = m_angley - 0.01f; else
				m_angley = m_angley + 0.01f;
				
			if (GetAsyncKeyState(VK_CONTROL))
				m_ay = (m_ay + 1) % 2;
			break;

		case VK_Z:
			if ( GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT) )
				m_anglez = m_anglez - 0.01f; else
				m_anglez = m_anglez + 0.01f;
				
			if (GetAsyncKeyState(VK_CONTROL))
				m_az = (m_az + 1) % 2;				
			break;

		case VK_S:
			fglCreateImage(99, width, height);
			fglCopyImage(99, 0,0,0,0, -1, 0,0);
			fglSaveImage(99, "screen.bmp");
			fglDestroyImage(99);
			
			break;

		case VK_F:
			m_freeze = (m_freeze + 1)%2;
			break;

		case VK_F2:
			if ( GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT) )
				m_ddx = m_ddx - 5.0f; else
				m_ddx = m_ddx + 5.0f;
			break;

		case VK_F3:
			if ( GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT) )
				m_ddy = m_ddy - 5.0f; else
				m_ddy = m_ddy + 5.0f;
			break;

		case VK_F4:
			if ( GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT) )
				m_ddz = m_ddz - 5.0f; else
				m_ddz = m_ddz + 5.0f;
			break;

		case VK_ADD:
			if (m < 20.0f)
				m = m + 0.05;
			break;
			
		case VK_SUBTRACT:
			if (m > 0.0f)
				m = m - 0.05;
			break;
			
		case VK_TAB:			
			frame=0;
			break;
	}
	return 0;
}

int deinit()
{
//	free(m_fbuff);
//	free(m_zbuff);

//	fglDestroyImage(1);
//	fglDestroyImage(0);	

/*
	// Change video mode.
	static DEVMODE devMode;

	devMode.dmSize=sizeof(DEVMODE);
//	devMode.dmDriverExtra=NULL;
	devMode.dmBitsPerPel=32;
	devMode.dmPelsWidth=1024;
	devMode.dmPelsHeight=768;
	devMode.dmFields=DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	ChangeDisplaySettings(&devMode, CDS_SET_PRIMARY);
*/

	return 0;
}
