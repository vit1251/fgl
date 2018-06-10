#include <windows.h>
#include <string.h>
#include <time.h>

#include "fglaux.h"
#include "fglb.h"

HWND m_hWnd;

int width;
int height;

unsigned char *m_fbuff;
unsigned char *m_zbuff;


#define MoveTo(h,x,y) MoveToEx(h,x,y,NULL)

/* TODO (Vit1251#1#): Полностью перевести кадр в структуру BITMAP */
/* DONE (Vit1251#1#): Внутренний буффер для хранение кадра */

int fglUpdate()
{
	static HDC hDc;

	hDc=GetDC(m_hWnd);

	// Draw a scene.
//	SetBitmapBits(m_hBitmap, height*width*sizeof(DWORD), m_fbuff);

	static BITMAPINFO bmi;
		
	bmi.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth=width;
	bmi.bmiHeader.biHeight=height;
	bmi.bmiHeader.biPlanes=1;
	bmi.bmiHeader.biBitCount=32;
	bmi.bmiHeader.biCompression=0;
	bmi.bmiHeader.biSizeImage=0;
	bmi.bmiHeader.biXPelsPerMeter=0;
	bmi.bmiHeader.biYPelsPerMeter=0;
	bmi.bmiHeader.biClrUsed=0;
	bmi.bmiHeader.biClrImportant=0;
		
	SetDIBitsToDevice(hDc,
					0, 0,
					width, height,
					0,0,0,height,
					m_fbuff, // bitmap[0].bmBits
					&bmi,
					DIB_RGB_COLORS);	


//	BitBlt(hDc, m_rect.left, m_rect.top, m_rect.right-m_rect.left, m_rect.bottom-m_rect.top, m_hDc, 0, 0, SRCCOPY);

	ReleaseDC(m_hWnd, hDc);
	
	return 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_CREATE:
			m_hWnd=hWnd;

			init();

			return 0;


		case WM_KEYDOWN:
			switch ( (int)wParam )
			{
				case VK_ESCAPE:
					PostMessage(hWnd, WM_CLOSE, 0, 0);
					break;

				default:
					keyboard((int)wParam);
			}
			return 0;


		case WM_CLOSE:
			deinit();
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			return 0;


		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

#include "demo3d_private.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // | CS_DROPSHADOW;
	wndclass.lpfnWndProc = (WNDPROC)WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, "MAINICON");
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
	wndclass.lpszMenuName = NULL; //"MAINMENU"
	wndclass.lpszClassName = "FreeGLClass";

	RegisterClass(&wndclass);

	hwnd = CreateWindowEx(
	                      WS_EX_APPWINDOW,
	                      wndclass.lpszClassName,
	                      "FreeGL "VER_STRING,
	                      WS_POPUP,
	                      0, 0,
	                      width=640, height=480,
	                      NULL,
	                      NULL,
	                      hInstance,
	                      NULL
	                     );

	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);

	while(msg.message != WM_QUIT) {
		PeekMessage(&msg,NULL,0,0,PM_REMOVE);

		TranslateMessage(&msg);
		DispatchMessage(&msg);

		draw();
	}
	return msg.wParam;
}
