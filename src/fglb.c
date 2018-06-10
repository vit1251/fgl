#include <windows.h>
#include <stdio.h>

#include "fglaux.h"
#include "fglb.h"

#define DEBUG

BITMAP bitmap[100] = { 0 };

// Work with memory.
//
int fglCreateImage(int id, int w, int h)
{
#ifdef DEBUG
	syslog("%s: fglCreateImage()", __FILE__ );
#endif
	
	bitmap[id].bmType = 0x4D42;
	bitmap[id].bmWidth = w;
	bitmap[id].bmHeight = h;
	bitmap[id].bmWidthBytes = w*sizeof(DWORD);
	bitmap[id].bmPlanes = 1;
	bitmap[id].bmBitsPixel = 32;
	bitmap[id].bmBits = (VOID *)malloc( bitmap[id].bmWidthBytes*bitmap[id].bmHeight );

//	memset(bitmap[id].bmBits, 0xFF, bitmap[id].bmWidthBytes*bitmap[id].bmHeight);

	return 0;
}

int fglDestroyImage(int id)
{
	free(bitmap[id].bmBits);

	return 0;
}


// Work with pixel.
//
int GetPoint(int id, int x, int y)
{
	if ((bitmap[id].bmBits != NULL) && (x < bitmap[id].bmWidth) && (y < bitmap[id].bmHeight)) {
//		*(bitmap[id].bmBits + bitmap[id].bmWidthBytes*bitmap[id].bmHeight - (y+1)*bitmap[id].bmWidthBytes - x) = color;
	}

	return 0;
}

int SetPoint(int id, int x, int y, COLORREF color)
{
	static long offset;
	char r=GetRValue(color);
	char g=GetGValue(color);
	char b=GetBValue(color);

	if ((m_fbuff != NULL) &&
		((0 <= x) && (x < width)) &&
		((0 <= y) && (y < height)) ) {
		offset = width*sizeof(COLORREF)*height - (y+1)*width*sizeof(COLORREF) + x*sizeof(COLORREF);
		if (offset > 0)
			*(DWORD *)((unsigned char *)m_fbuff + offset) = RGB(b,g,r);
	}

	return 0;
}

// Work with file.
//
int fglLoadImage(int id, char *fname)
{
	FILE *f=NULL;

	if (f=fopen(fname, "r+b")) {

		BITMAPFILEHEADER bmfh;

		fread(&bmfh, 1, sizeof(BITMAPFILEHEADER), f);

		BITMAPINFOHEADER bmih;

		fread(&bmih, 1, sizeof(BITMAPINFOHEADER), f);
		
		bitmap[id].bmWidth = bmih.biWidth;
		bitmap[id].bmHeight = bmih.biHeight;
		

		bitmap[id].bmBits = (VOID *)malloc( bmih.biWidth*bmih.biHeight*sizeof(DWORD) );
		if ( bmih.biCompression == BI_RGB) {
			fseek(f, bmfh.bfOffBits, SEEK_SET);
			
			fread(bitmap[id].bmBits, 1, bmih.biWidth*bmih.biHeight*sizeof(DWORD), f);
		} else
		if ( bmih.biCompression == BI_BITFIELDS ) {
			DWORD dwRMask, dwGMask, dwBMask;
			DWORD dwColor, dwTemp, dwOffset, dwReal;
			int n;
			
			fseek(f, bmfh.bfOffBits-4*sizeof(DWORD), SEEK_SET);
			
			fread(&dwRMask, 1, sizeof(DWORD), f);
			fread(&dwGMask, 1, sizeof(DWORD), f);
			fread(&dwBMask, 1, sizeof(DWORD), f);
			fread(&dwTemp, 1, sizeof(DWORD), f);

			fseek(f, bmfh.bfOffBits, SEEK_SET);

			dwOffset=0;
			n=0;
			while (dwOffset < bmih.biWidth*bmih.biHeight*sizeof(DWORD)) {
				fread(&dwColor, 1, sizeof(DWORD), f);

				dwReal = 0L;
				
				// RED
				dwTemp = dwColor & dwRMask;
				while (dwTemp > 0x100)
					dwTemp = dwTemp >> 8;
				dwReal |= (dwTemp << 16);

				// GREEN
				dwTemp = dwColor & dwGMask;
				while (dwTemp > 0x100)
					dwTemp = dwTemp >> 8;
				dwReal |= (dwTemp << 8);

				// BLUE
				dwTemp = dwColor & dwBMask;
				while (dwTemp > 0x100)
					dwTemp = dwTemp >> 8;
				dwReal |= dwTemp;

				*((DWORD *)( ((UCHAR *)(bitmap[id].bmBits)) + dwOffset)) = dwReal;

				dwOffset += sizeof(DWORD);
				n++;
			}

		}
		
		fclose(f);
	}
}

int fglSaveImage(int id, char *fname)
{
	FILE *f=NULL;

	if (f=fopen(fname, "w+b")) {

		// Safe magic.
		BITMAPFILEHEADER bmfh;
		
		bmfh.bfType=0x4D42;
		bmfh.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+bitmap[id].bmWidth*bitmap[id].bmHeight*sizeof(DWORD);
		bmfh.bfReserved1=0;
		bmfh.bfReserved2=0;
		bmfh.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
		fwrite(&bmfh, 1, sizeof(BITMAPFILEHEADER), f);

		// Save info.
		BITMAPINFOHEADER bmih;		
		
		bmih.biSize=sizeof(BITMAPINFOHEADER);
		bmih.biWidth=bitmap[id].bmWidth;
		bmih.biHeight=bitmap[id].bmHeight;
		bmih.biPlanes=1;
		bmih.biBitCount=32;
		bmih.biCompression=0;
		bmih.biSizeImage=0;
		bmih.biXPelsPerMeter=0;
		bmih.biYPelsPerMeter=0;
		bmih.biClrUsed=0;
		bmih.biClrImportant=0;
		fwrite(&bmih, 1, sizeof(BITMAPINFOHEADER), f);

		fwrite(bitmap[id].bmBits, 1, bitmap[id].bmWidth*bitmap[id].bmHeight*sizeof(DWORD), f);
		
		fclose(f);
	}	
}

// Copy and other.
//
int fglCopyImage(int dst_id, int dst_x, int dst_y, int w, int h, int src_id, int src_x, int src_y)
{
	DWORD *dwSrcData;
	DWORD dwSrcWidth, dwSrcHeight;
	DWORD *dwDstData;
	DWORD dwDstWidth, dwDstHeight;	

	// Save a src attr.
	if (src_id >= 0) {
		dwSrcData = bitmap[src_id].bmBits;
		dwSrcWidth = bitmap[src_id].bmWidth;
		dwSrcHeight = bitmap[src_id].bmHeight;
	} else {
		dwSrcData = (DWORD *)m_fbuff;
		dwSrcWidth = width;
		dwSrcHeight = height;
	}

	// Save a dest attr.
	if (dst_id >= 0) {
		dwDstData = bitmap[dst_id].bmBits;
		dwDstWidth = bitmap[dst_id].bmWidth;
		dwDstHeight = bitmap[dst_id].bmHeight;
	} else {
		dwDstData = (DWORD *)m_fbuff;
		dwDstWidth = width;
		dwDstHeight = height;
	}

	// Check and normalize parameter.
	if (h <= 0)
		h = dwSrcHeight;
			
	if (w <= 0)
		w = dwSrcWidth;

	// X > 0
	if (dst_x + w < 0)
		return -1;

	// X < width
	if (dst_x < width) {
		while (dst_x + w > width)
			w--;
	} else
	return -1;

	// Y > 0
	if (dst_y + h < 0)
		return -1;
		
	// Y < height
	if (dst_y < height) {
		while (dst_y + h > height)
			h--;
	} else
	return -1;		

	DWORD dwWidth, dwHeight;
	DWORD dwColor;
	
	for(dwHeight=0; dwHeight < h; dwHeight++) {
		for(dwWidth=0; dwWidth < w; dwWidth++) {
			dwColor = *(dwSrcData + dwSrcWidth*(dwSrcHeight - dwHeight - src_y - 1) + dwWidth + src_x);
			*(dwDstData + dwDstWidth*(dwDstHeight - dwHeight - dst_y - 1) + dwWidth + dst_x) = dwColor;
		}
	}
			
	return 0;
}

int fglCopyTransparentImage(int dst_id, int dst_x, int dst_y, int w, int h, int src_id, int src_x, int src_y, COLORREF color)
{
	DWORD *dwSrcData;
	DWORD dwSrcWidth, dwSrcHeight;
	DWORD *dwDstData;
	DWORD dwDstWidth, dwDstHeight;	

	// Save a src attr.
	if (src_id >= 0) {
		dwSrcData = bitmap[src_id].bmBits;
		dwSrcWidth = bitmap[src_id].bmWidth;
		dwSrcHeight = bitmap[src_id].bmHeight;
	} else {
		dwSrcData = (DWORD *)m_fbuff;
		dwSrcWidth = width;
		dwSrcHeight = height;
	}

	// Save a dest attr.
	if (dst_id >= 0) {
		dwDstData = bitmap[dst_id].bmBits;
		dwDstWidth = bitmap[dst_id].bmWidth;
		dwDstHeight = bitmap[dst_id].bmHeight;
	} else {
		dwDstData = (DWORD *)m_fbuff;
		dwDstWidth = width;
		dwDstHeight = height;
	}

	// Check and normalize parameter.
	if (h <= 0)
		h = bitmap[src_id].bmHeight;
			
	if (w <= 0)
		w = bitmap[src_id].bmWidth;

	// X > 0
	if (dst_x + w < 0)
		return -1;

	// X < width
	if (dst_x < width) {
		while (dst_x + w > width)
			w--;
	} else
	return -1;

	// Y > 0
	if (dst_y + h < 0)
		return -1;
		
	// Y < height
	if (dst_y < height) {
		while (dst_y + h > height)
			h--;
	} else
	return -1;		

	DWORD dwWidth, dwHeight;
	DWORD dwColor;
	
	for(dwHeight=0; dwHeight < h; dwHeight++) {
		for(dwWidth=0; dwWidth < w; dwWidth++) {
			dwColor = *(dwSrcData + dwSrcWidth*(dwSrcHeight - dwHeight - 1) + dwWidth);
			if (dwColor != color)
				*(dwDstData + dwDstWidth*(dwDstHeight - dwHeight - dst_y - 1) + dwWidth + dst_x) = dwColor;
		}
	}
			
	return 0;
}
