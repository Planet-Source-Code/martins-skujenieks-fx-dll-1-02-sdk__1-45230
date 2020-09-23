// fx.cpp : Defines the entry point for the DLL application.
//
#include "stdafx.h"
#include "fx.h"



BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}



////////////////////////////////////////////////////////////////////////////
//
//	fxAlphaBlend()				Displays bitmaps with transparent and
//								semitransparent pixels, first
//								stretching or compressing the bitmap to fit
//								the dimensions of the destination rectangle,
//								if necessary.
//								If the function succeeds, the return value
//								is 1 (true); 
//								if fails, the return value is 0 (false). 
//
//	HDC		DestDC				Handle to the destination device context;
//	int		DestX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestWidth			Specifies the width, in logical units,
//								of the destination rectangle.
//	int		DestHeight			Specifies the height, in logical units,
//								of the destination rectangle.
//	HDC		SrcDC				Handle to the source device context;
//	int		SrcX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcWidth			Specifies the width, in logical units,
//								of the source rectangle;
//	int		SrcHeight			Specifies the height, in logical units,
//								of the source rectangle.
//	int		Alpha				Alpha value (value in range 0 to 255);
//	int		MaskColor			The RGB color in the source DC to 
//								treat as transparent;
//								if (MaskColor = -1) the transparency
//								will not be used;
//
////////////////////////////////////////////////////////////////////////////
int __stdcall fxAlphaBlend(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight, int Alpha, int MaskColor)
{
	if (Alpha < 0)
		Alpha = 0;
	if (Alpha > 255)
		Alpha = 255;

	BITMAPINFOHEADER	BMI;
	BMI.biSize			= sizeof(BITMAPINFOHEADER);
	BMI.biWidth			= DestWidth;
	BMI.biHeight		= DestHeight;
	BMI.biPlanes		= 1;
	BMI.biBitCount		= 32;
	BMI.biCompression	= BI_RGB;
	BMI.biSizeImage		= 0;
	BMI.biXPelsPerMeter = 0;
	BMI.biYPelsPerMeter = 0;
	BMI.biClrUsed		= 0;
	BMI.biClrImportant	= 0;
	
	BYTE				*pDestBits;
	HBITMAP				hbmDest;
	hbmDest = ::CreateDIBSection(DestDC, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pDestBits, NULL, 0l);

	BYTE				*pSrcBits;
	HBITMAP				hbmSrc;
	hbmSrc = ::CreateDIBSection(SrcDC, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pSrcBits, NULL, 0l);

	HDC					dc = ::CreateCompatibleDC(NULL);
	HBITMAP				hbm = (HBITMAP) ::SelectObject(dc, hbmSrc);
	
	if (!::StretchBlt(dc, 0, 0, DestWidth, DestHeight, SrcDC, SrcX, SrcY, SrcWidth, SrcHeight, SRCCOPY))
		return 0;

	::SelectObject(dc, hbmDest);

	if (!::StretchBlt(dc, 0, 0, DestWidth, DestHeight, DestDC, DestX, DestY, DestWidth, DestHeight, SRCCOPY))
		return 0;

	::SelectObject(dc, hbm);

	::DeleteDC(dc);

    for (int y = 0; y < DestHeight; y++)
    {
		LPBYTE pbDestRGB = (LPBYTE)&((DWORD*)pDestBits)[y * DestWidth];
		LPBYTE pbSrcRGB = (LPBYTE)&((DWORD*)pSrcBits)[y * DestWidth];

		for (int x = 0; x < DestWidth; x++)
		{

			if (MaskColor >= 0)
			{
				if (MaskColor == fxRGB(pbSrcRGB[0], pbSrcRGB[1], pbSrcRGB[2]))
				{
					pbSrcRGB[0] = pbDestRGB[0];
					pbSrcRGB[1] = pbDestRGB[1];
					pbSrcRGB[2] = pbDestRGB[2];
				}
				else
				{
					pbSrcRGB[0] = fxShadeColors(pbDestRGB[0], pbSrcRGB[0], Alpha);
					pbSrcRGB[1] = fxShadeColors(pbDestRGB[1], pbSrcRGB[1], Alpha);
					pbSrcRGB[2] = fxShadeColors(pbDestRGB[2], pbSrcRGB[2], Alpha);
				}
			}
			else
			{
				pbSrcRGB[0] = fxShadeColors(pbDestRGB[0], pbSrcRGB[0], Alpha);
				pbSrcRGB[1] = fxShadeColors(pbDestRGB[1], pbSrcRGB[1], Alpha);
				pbSrcRGB[2] = fxShadeColors(pbDestRGB[2], pbSrcRGB[2], Alpha);
			}
			pbSrcRGB += 4;
			pbDestRGB += 4;

		}
	}

	dc = ::CreateCompatibleDC(NULL);
	
	hbm = (HBITMAP) ::SelectObject(dc, hbmSrc);
	if (!::BitBlt(DestDC, DestX, DestY, DestWidth, DestHeight, dc, 0, 0, SRCCOPY))
		return 0;

	::DeleteDC(dc);

	::DeleteObject(hbmSrc);	
	::DeleteObject(hbmDest);	
	
	return 1;
}



////////////////////////////////////////////////////////////////////////////
//
//	fxAmbientLight()			Function displays bitmap in 
//								specified ambient light, first
//								stretching or compressing the bitmap to fit
//								the dimensions of the destination rectangle,
//								if necessary.
//								If the function succeeds, the return value
//								is 1 (true); 
//								if fails, the return value is 0 (false). 
//
//	HDC		DestDC				Handle to the destination device context;
//	int		DestX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestWidth			Specifies the width, in logical units,
//								of the destination rectangle.
//	int		DestHeight			Specifies the height, in logical units,
//								of the destination rectangle.
//	HDC		SrcDC				Handle to the source device context;
//	int		SrcX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcWidth			Specifies the width, in logical units,
//								of the source rectangle;
//	int		SrcHeight			Specifies the height, in logical units,
//								of the source rectangle;
//	int		Color				Ambient light color (RGB);
//	int		Intensity			Ambient light intensity (value in
//								range 0-255).
//
////////////////////////////////////////////////////////////////////////////
int __stdcall fxAmbientLight(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight, int Color, int Intensity)
{
	if (Intensity < 0)
		Intensity = 0;
	if (Intensity > 255)
		Intensity = 255;

	int fxR				= (255 - Intensity - fxGetRed(Color));
	int fxG				= (255 - Intensity - fxGetGreen(Color));
	int fxB				= (255 - Intensity - fxGetBlue(Color));

	BITMAPINFOHEADER	BMI;
	BMI.biSize			= sizeof(BITMAPINFOHEADER);
	BMI.biWidth			= DestWidth;
	BMI.biHeight		= DestHeight;
	BMI.biPlanes		= 1;
	BMI.biBitCount		= 32;
	BMI.biCompression	= BI_RGB;
	BMI.biSizeImage		= 0;
	BMI.biXPelsPerMeter = 0;
	BMI.biYPelsPerMeter = 0;
	BMI.biClrUsed		= 0;
	BMI.biClrImportant	= 0;
	
	BYTE				*pDestBits;
	HBITMAP				hbmDest;
	hbmDest = ::CreateDIBSection(DestDC, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pDestBits, NULL, 0l);

	BYTE				*pSrcBits;
	HBITMAP				hbmSrc;
	hbmSrc = ::CreateDIBSection(SrcDC, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pSrcBits, NULL, 0l);

	HDC					dc = ::CreateCompatibleDC(NULL);
	HBITMAP				hbm = (HBITMAP) ::SelectObject(dc, hbmSrc);
	
	if (!::StretchBlt(dc, 0, 0, DestWidth, DestHeight, SrcDC, SrcX, SrcY, SrcWidth, SrcHeight, SRCCOPY))
		return 0;

	::SelectObject(dc, hbmDest);

	if (!::StretchBlt(dc, 0, 0, DestWidth, DestHeight, DestDC, DestX, DestY, DestWidth, DestHeight, SRCCOPY))
		return 0;

	::SelectObject(dc, hbm);

	::DeleteDC(dc);

    for (int y = 0; y < DestHeight; y++)
    {
		LPBYTE pbDestRGB = (LPBYTE)&((DWORD*)pDestBits)[y * DestWidth];
		LPBYTE pbSrcRGB = (LPBYTE)&((DWORD*)pSrcBits)[y * DestWidth];

		for (int x = 0; x < DestWidth; x++)
		{
			pbSrcRGB[0] = fxByte(pbSrcRGB[0] - fxB);
			pbSrcRGB[1] = fxByte(pbSrcRGB[1] - fxG);
			pbSrcRGB[2] = fxByte(pbSrcRGB[2] - fxR);

			pbSrcRGB += 4;
			pbDestRGB += 4;
		}
	}

	dc = ::CreateCompatibleDC(NULL);
	
	hbm = (HBITMAP) ::SelectObject(dc, hbmSrc);
	if (!::BitBlt(DestDC, DestX, DestY, DestWidth, DestHeight, dc, 0, 0, SRCCOPY))
		return 0;

	::DeleteDC(dc);

	::DeleteObject(hbmSrc);	
	::DeleteObject(hbmDest);	
	
	return 1;
}



////////////////////////////////////////////////////////////////////////////
//
//	fxAntiAlias()				Displays anti-aliased (60% - 5pt) bitmap, 
//								first stretching or compressing it to fit
//								the dimensions of the destination rectangle,
//								if necessary.
//								If the function succeeds, the return value
//								is 1 (true); 
//								if fails, the return value is 0 (false). 
//
//	HDC		DestDC				Handle to the destination device context;
//	int		DestX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestWidth			Specifies the width, in logical units,
//								of the destination rectangle.
//	int		DestHeight			Specifies the height, in logical units,
//								of the destination rectangle.
//	HDC		SrcDC				Handle to the source device context;
//	int		SrcX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcWidth			Specifies the width, in logical units,
//								of the source rectangle;
//	int		SrcHeight			Specifies the height, in logical units,
//								of the source rectangle.
//
////////////////////////////////////////////////////////////////////////////
int __stdcall fxAntiAlias(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight)
{
	BITMAPINFOHEADER	BMI;
	BMI.biSize			= sizeof(BITMAPINFOHEADER);
	BMI.biWidth			= DestWidth;
	BMI.biHeight		= DestHeight;
	BMI.biPlanes		= 1;
	BMI.biBitCount		= 32;
	BMI.biCompression	= BI_RGB;
	BMI.biSizeImage		= 0;
	BMI.biXPelsPerMeter = 0;
	BMI.biYPelsPerMeter = 0;
	BMI.biClrUsed		= 0;
	BMI.biClrImportant	= 0;
	
	BYTE				*pDestBits;
	HBITMAP				hbmDest;
	hbmDest = ::CreateDIBSection(DestDC, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pDestBits, NULL, 0l);

	BYTE				*pSrcBits;
	HBITMAP				hbmSrc;
	hbmSrc = ::CreateDIBSection(SrcDC, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pSrcBits, NULL, 0l);

	HDC					dc = ::CreateCompatibleDC(NULL);
	HBITMAP				hbm = (HBITMAP) ::SelectObject(dc, hbmSrc);
	
	if (!::StretchBlt(dc, 0, 0, DestWidth, DestHeight, SrcDC, SrcX, SrcY, SrcWidth, SrcHeight, SRCCOPY))
		return 0;

	::SelectObject(dc, hbmDest);

	if (!::StretchBlt(dc, 0, 0, DestWidth, DestHeight, DestDC, DestX, DestY, DestWidth, DestHeight, SRCCOPY))
		return 0;

	::SelectObject(dc, hbm);

	::DeleteDC(dc);

	for (int y = 1; y < DestHeight - 1; y++)
    {
		LPBYTE pbDestRGB = (LPBYTE)&((DWORD*)pDestBits)[y * DestWidth];
		LPBYTE pbSrcRGB = (LPBYTE)&((DWORD*)pSrcBits)[y * DestWidth];
		LPBYTE pbSrcRGBx = (LPBYTE)&((DWORD*)pSrcBits)[y * DestWidth];
		LPBYTE pbSrcRGBy1 = (LPBYTE)&((DWORD*)pSrcBits)[(y-1) * DestWidth];
		LPBYTE pbSrcRGBy2 = (LPBYTE)&((DWORD*)pSrcBits)[(y+1) * DestWidth];

		for (int x = 1; x < DestWidth - 1; x++)
		{
			pbSrcRGB[4] = (pbSrcRGBx[0] + (pbSrcRGBx[4] * 6) + pbSrcRGBx[8] + pbSrcRGBy1[4] + pbSrcRGBy2[4]) / 10;
			pbSrcRGB[5] = (pbSrcRGBx[1] + (pbSrcRGBx[5] * 6) + pbSrcRGBx[9] + pbSrcRGBy1[5] + pbSrcRGBy2[5]) / 10;
			pbSrcRGB[6] = (pbSrcRGBx[2] + (pbSrcRGBx[6] * 6) + pbSrcRGBx[10] + pbSrcRGBy1[6] + pbSrcRGBy2[6]) / 10;
			
			pbDestRGB += 4;
			pbSrcRGB += 4;
			pbSrcRGBx += 4;
			pbSrcRGBy1 += 4;
			pbSrcRGBy2 += 4;
		}
	}

	dc = ::CreateCompatibleDC(NULL);
	
	hbm = (HBITMAP) ::SelectObject(dc, hbmSrc);
	if (!::BitBlt(DestDC, DestX, DestY, DestWidth, DestHeight, dc, 0, 0, SRCCOPY))
		return 0;

	::DeleteDC(dc);

	::DeleteObject(hbmSrc);	
	::DeleteObject(hbmDest);	
	
	return 1;
}



////////////////////////////////////////////////////////////////////////////
//
//	fxBitBlt()					Function performs a bit-block transfer of
//								the color data corresponding to a rectangle
//								of pixels from the specified source device
//								context into a destination device context.
//								If the function succeeds, the return value
//								is 1 (true); 
//								if fails, the return value is 0 (false). 
//
//	HDC		DestDC				Handle to the destination device context;
//	int		DestX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestWidth			Specifies the width, in logical units,
//								of the destination rectangle.
//	int		DestHeight			Specifies the height, in logical units,
//								of the destination rectangle.
//	HDC		SrcDC				Handle to the source device context;
//	int		SrcX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		RasterOperation		Specifies a raster-operation code.
//
////////////////////////////////////////////////////////////////////////////
int __stdcall fxBitBlt(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int RasterOperation)
{
	return ::BitBlt(DestDC, DestX, DestY, DestWidth, DestHeight, SrcDC, SrcX, SrcY, RasterOperation);
}



////////////////////////////////////////////////////////////////////////////
//
//	fxBlur()					Displays blured (11% - 9pt) bitmap, 
//								first stretching or compressing it to fit
//								the dimensions of the destination rectangle,
//								if necessary.
//								If the function succeeds, the return value
//								is 1 (true); 
//								if fails, the return value is 0 (false). 
//
//	HDC		DestDC				Handle to the destination device context;
//	int		DestX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestWidth			Specifies the width, in logical units,
//								of the destination rectangle.
//	int		DestHeight			Specifies the height, in logical units,
//								of the destination rectangle.
//	HDC		SrcDC				Handle to the source device context;
//	int		SrcX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcWidth			Specifies the width, in logical units,
//								of the source rectangle;
//	int		SrcHeight			Specifies the height, in logical units,
//								of the source rectangle.
//
////////////////////////////////////////////////////////////////////////////
int __stdcall fxBlur(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight)
{
	BITMAPINFOHEADER	BMI;
	BMI.biSize			= sizeof(BITMAPINFOHEADER);
	BMI.biWidth			= DestWidth;
	BMI.biHeight		= DestHeight;
	BMI.biPlanes		= 1;
	BMI.biBitCount		= 32;
	BMI.biCompression	= BI_RGB;
	BMI.biSizeImage		= 0;
	BMI.biXPelsPerMeter = 0;
	BMI.biYPelsPerMeter = 0;
	BMI.biClrUsed		= 0;
	BMI.biClrImportant	= 0;
	
	BYTE				*pDestBits;
	HBITMAP				hbmDest;
	hbmDest = ::CreateDIBSection(DestDC, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pDestBits, NULL, 0l);

	BYTE				*pSrcBits;
	HBITMAP				hbmSrc;
	hbmSrc = ::CreateDIBSection(SrcDC, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pSrcBits, NULL, 0l);

	HDC					dc = ::CreateCompatibleDC(NULL);
	HBITMAP				hbm = (HBITMAP) ::SelectObject(dc, hbmSrc);
	
	if (!::StretchBlt(dc, 0, 0, DestWidth, DestHeight, SrcDC, SrcX, SrcY, SrcWidth, SrcHeight, SRCCOPY))
		return 0;

	::SelectObject(dc, hbmDest);

	if (!::StretchBlt(dc, 0, 0, DestWidth, DestHeight, DestDC, DestX, DestY, DestWidth, DestHeight, SRCCOPY))
		return 0;

	::SelectObject(dc, hbm);

	::DeleteDC(dc);

	for (int y = 1; y < DestHeight - 1; y++)
    {
		LPBYTE pbDestRGB = (LPBYTE)&((DWORD*)pDestBits)[y * DestWidth];
		LPBYTE pbSrcRGB = (LPBYTE)&((DWORD*)pSrcBits)[y * DestWidth];
		LPBYTE pbSrcRGBy1 = (LPBYTE)&((DWORD*)pSrcBits)[(y-1) * DestWidth];
		LPBYTE pbSrcRGBy2 = (LPBYTE)&((DWORD*)pSrcBits)[(y+1) * DestWidth];

		for (int x = 1; x < DestWidth - 1; x++)
		{	
			pbSrcRGB[4] = (pbSrcRGB[0] + pbSrcRGB[4] + pbSrcRGB[8] + pbSrcRGBy1[0] + pbSrcRGBy1[4] + pbSrcRGBy1[8] + pbSrcRGBy2[0] + pbSrcRGBy2[4] + pbSrcRGBy2[8]) / 9;
			pbSrcRGB[5] = (pbSrcRGB[1] + pbSrcRGB[5] + pbSrcRGB[9] + pbSrcRGBy1[1] + pbSrcRGBy1[5] + pbSrcRGBy1[9] + pbSrcRGBy2[1] + pbSrcRGBy2[5] + pbSrcRGBy2[9]) / 9;
			pbSrcRGB[6] = (pbSrcRGB[2] + pbSrcRGB[6] + pbSrcRGB[10] + pbSrcRGBy1[2] + pbSrcRGBy1[6] + pbSrcRGBy1[10] + pbSrcRGBy2[2] + pbSrcRGBy2[6] + pbSrcRGBy2[10]) / 9;

			pbDestRGB += 4;
			pbSrcRGB += 4;
			pbSrcRGBy1 += 4;
			pbSrcRGBy2 += 4;
		}
	}

	dc = ::CreateCompatibleDC(NULL);
	
	hbm = (HBITMAP) ::SelectObject(dc, hbmSrc);
	if (!::BitBlt(DestDC, DestX, DestY, DestWidth, DestHeight, dc, 0, 0, SRCCOPY))
		return 0;

	::DeleteDC(dc);

	::DeleteObject(hbmSrc);	
	::DeleteObject(hbmDest);	
	
	return 1;
}



////////////////////////////////////////////////////////////////////////////
//
//	fxBrightness()				Displays bitmap with specified 
//								brightness value, 
//								first stretching or compressing it to fit
//								the dimensions of the destination rectangle,
//								if necessary.
//								If the function succeeds, the return value
//								is 1 (true); 
//								if fails, the return value is 0 (false). 
//
//	HDC		DestDC				Handle to the destination device context;
//	int		DestX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestWidth			Specifies the width, in logical units,
//								of the destination rectangle.
//	int		DestHeight			Specifies the height, in logical units,
//								of the destination rectangle.
//	HDC		SrcDC				Handle to the source device context;
//	int		SrcX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcWidth			Specifies the width, in logical units,
//								of the source rectangle;
//	int		SrcHeight			Specifies the height, in logical units,
//								of the source rectangle.
//	int		Brightness			Brightness (value in range -255 to 255);
//
////////////////////////////////////////////////////////////////////////////
int __stdcall fxBrightness(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight, int Brightness)
{
	if (Brightness < -255)
		Brightness = -255;
	if (Brightness > 255)
		Brightness = 255;

	BITMAPINFOHEADER	BMI;
	BMI.biSize			= sizeof(BITMAPINFOHEADER);
	BMI.biWidth			= DestWidth;
	BMI.biHeight		= DestHeight;
	BMI.biPlanes		= 1;
	BMI.biBitCount		= 32;
	BMI.biCompression	= BI_RGB;
	BMI.biSizeImage		= 0;
	BMI.biXPelsPerMeter = 0;
	BMI.biYPelsPerMeter = 0;
	BMI.biClrUsed		= 0;
	BMI.biClrImportant	= 0;
	
	BYTE				*pDestBits;
	HBITMAP				hbmDest;
	hbmDest = ::CreateDIBSection(DestDC, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pDestBits, NULL, 0l);

	BYTE				*pSrcBits;
	HBITMAP				hbmSrc;
	hbmSrc = ::CreateDIBSection(SrcDC, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pSrcBits, NULL, 0l);

	HDC					dc = ::CreateCompatibleDC(NULL);
	HBITMAP				hbm = (HBITMAP) ::SelectObject(dc, hbmSrc);
	
	if (!::StretchBlt(dc, 0, 0, DestWidth, DestHeight, SrcDC, SrcX, SrcY, SrcWidth, SrcHeight, SRCCOPY))
		return 0;

	::SelectObject(dc, hbmDest);

	if (!::StretchBlt(dc, 0, 0, DestWidth, DestHeight, DestDC, DestX, DestY, DestWidth, DestHeight, SRCCOPY))
		return 0;

	::SelectObject(dc, hbm);

	::DeleteDC(dc);

    for (int y = 0; y < DestHeight; y++)
    {
		LPBYTE pbDestRGB = (LPBYTE)&((DWORD*)pDestBits)[y * DestWidth];
		LPBYTE pbSrcRGB = (LPBYTE)&((DWORD*)pSrcBits)[y * DestWidth];

		for (int x = 0; x < DestWidth; x++)
		{
			pbSrcRGB[0] = fxByte(pbSrcRGB[0] + Brightness);
			pbSrcRGB[1] = fxByte(pbSrcRGB[1] + Brightness);
			pbSrcRGB[2] = fxByte(pbSrcRGB[2] + Brightness);

			pbSrcRGB += 4;
			pbDestRGB += 4;
		}
	}

	dc = ::CreateCompatibleDC(NULL);
	
	hbm = (HBITMAP) ::SelectObject(dc, hbmSrc);
	if (!::BitBlt(DestDC, DestX, DestY, DestWidth, DestHeight, dc, 0, 0, SRCCOPY))
		return 0;

	::DeleteDC(dc);

	::DeleteObject(hbmSrc);	
	::DeleteObject(hbmDest);	
	
	return 1;
}



////////////////////////////////////////////////////////////////////////////
//
//	fxFilter()					Function displays filtered bitmap, 
//								first stretching or compressing it to fit
//								the dimensions of the destination rectangle,
//								if necessary.
//								If the function succeeds, the return value
//								is 1 (true); 
//								if fails, the return value is 0 (false). 
//
//	HDC		DestDC				Handle to the destination device context;
//	int		DestX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestWidth			Specifies the width, in logical units,
//								of the destination rectangle.
//	int		DestHeight			Specifies the height, in logical units,
//								of the destination rectangle.
//	HDC		SrcDC				Handle to the source device context;
//	int		SrcX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcWidth			Specifies the width, in logical units,
//								of the source rectangle;
//	int		SrcHeight			Specifies the height, in logical units,
//								of the source rectangle.
//	int		Filter				Filter mode.
//	int		Flags				Filter flags.
//
//	------------------------------------------------------------------------
//	F/X		Filter				Color			Flags
//	------------------------------------------------------------------------
//	0		(no filter)			-				-
//	1		invert				-				-
//	2		greyscale			-				-
//	3		glass				RGB				-
//	4		glass+				RGB				light (0-255)
//	5		reduce bits/pixel	-				bits/pixel (16, (8), 4, 2, 1)
//	------------------------------------------------------------------------
//
////////////////////////////////////////////////////////////////////////////
int __stdcall fxFilter(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight, int Filter, int Color, int Flags)
{
	int	fR = 0,
		fG = 0,
		fB = 0,
		fF = 0,
		fX = 0,
		fY = 0,
		fZ = 0;

	BITMAPINFOHEADER	BMI;
	BMI.biSize			= sizeof(BITMAPINFOHEADER);
	BMI.biWidth			= DestWidth;
	BMI.biHeight		= DestHeight;
	BMI.biPlanes		= 1;
	BMI.biBitCount		= 32;
	BMI.biCompression	= BI_RGB;
	BMI.biSizeImage		= 0;
	BMI.biXPelsPerMeter = 0;
	BMI.biYPelsPerMeter = 0;
	BMI.biClrUsed		= 0;
	BMI.biClrImportant	= 0;
	
	BYTE				*pDestBits;
	HBITMAP				hbmDest;
	hbmDest = ::CreateDIBSection(DestDC, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pDestBits, NULL, 0l);

	BYTE				*pSrcBits;
	HBITMAP				hbmSrc;
	hbmSrc = ::CreateDIBSection(SrcDC, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pSrcBits, NULL, 0l);

	HDC					dc = ::CreateCompatibleDC(NULL);
	HBITMAP				hbm = (HBITMAP) ::SelectObject(dc, hbmSrc);
	
	if (!::StretchBlt(dc, 0, 0, DestWidth, DestHeight, SrcDC, SrcX, SrcY, SrcWidth, SrcHeight, SRCCOPY))
		return 0;

	::SelectObject(dc, hbmDest);

	if (!::StretchBlt(dc, 0, 0, DestWidth, DestHeight, DestDC, DestX, DestY, DestWidth, DestHeight, SRCCOPY))
		return 0;

	::SelectObject(dc, hbm);

	::DeleteDC(dc);

    for (int y = 0; y < DestHeight; y++)
    {
		LPBYTE pbDestRGB = (LPBYTE)&((DWORD*)pDestBits)[y * DestWidth];
		LPBYTE pbSrcRGB = (LPBYTE)&((DWORD*)pSrcBits)[y * DestWidth];

		for (int x = 0; x < DestWidth; x++)
		{
			switch (Filter)
			{
			case 1:
				pbSrcRGB[0] = 255 - pbSrcRGB[0];
				pbSrcRGB[1] = 255 - pbSrcRGB[1];
				pbSrcRGB[2] = 255 - pbSrcRGB[2];
				break;
			case 2:
				fF = ((pbSrcRGB[0] + pbSrcRGB[1] + pbSrcRGB[2]) / 3),
				pbSrcRGB[0] = fF;
				pbSrcRGB[1] = fF;
				pbSrcRGB[2] = fF;
				break;
			case 3:
				pbSrcRGB[0] = fxByte(pbSrcRGB[0] - (255 - fxGetBlue(Color)));
				pbSrcRGB[1] = fxByte(pbSrcRGB[1] - (255 - fxGetGreen(Color)));
				pbSrcRGB[2] = fxByte(pbSrcRGB[2] - (255 - fxGetRed(Color)));
				break;
			case 4:
				pbSrcRGB[0] = fxByte(pbSrcRGB[0] - (255 - Flags - fxGetBlue(Color)));
				pbSrcRGB[1] = fxByte(pbSrcRGB[1] - (255 - Flags - fxGetGreen(Color)));
				pbSrcRGB[2] = fxByte(pbSrcRGB[2] - (255 - Flags - fxGetRed(Color)));
				break;
			case 5:
				pbSrcRGB[0] = pbSrcRGB[0] - (pbSrcRGB[0] % (Flags+1));
				pbSrcRGB[1] = pbSrcRGB[1] - (pbSrcRGB[1] % (Flags+1));
				pbSrcRGB[2] = pbSrcRGB[2] - (pbSrcRGB[2] % (Flags+1));
				break;
				/*
				if ((x % 4) == 3)
					pbSrcRGB[0] = fxByte(pbSrcRGB[0] + Flags),
					pbSrcRGB[1] = fxByte(pbSrcRGB[1] + Flags),
					pbSrcRGB[2] = fxByte(pbSrcRGB[2] + Flags);
				*/

				/*
				if (x > Flags)
				{
					pbSrcRGB[0] = fxByte(pbSrcRGB[0] + Flags);
					pbSrcRGB[1] = fxByte(pbSrcRGB[1] + Flags);
					pbSrcRGB[2] = fxByte(pbSrcRGB[2]);
				}
				else
				{
					pbSrcRGB[0] = pbSrcRGB[0];
					pbSrcRGB[1] = pbSrcRGB[1];
					pbSrcRGB[2] = pbSrcRGB[2];
				}
				break;
				*/
			default:
				pbSrcRGB[0] = pbSrcRGB[0];
				pbSrcRGB[1] = pbSrcRGB[1];
				pbSrcRGB[2] = pbSrcRGB[2];
				break;
			}
			pbSrcRGB += 4;
			pbDestRGB += 4;
		}
	}

	dc = ::CreateCompatibleDC(NULL);
	
	hbm = (HBITMAP) ::SelectObject(dc, hbmSrc);
	if (!::BitBlt(DestDC, DestX, DestY, DestWidth, DestHeight, dc, 0, 0, SRCCOPY))
		return 0;

	::DeleteDC(dc);

	::DeleteObject(hbmSrc);	
	::DeleteObject(hbmDest);	
	
	return 1;
}



////////////////////////////////////////////////////////////////////////////
//
//	fxGamma()					Function displays bitmap with specified 
//								gamma value, 
//								first stretching or compressing it to fit
//								the dimensions of the destination rectangle,
//								if necessary.
//								If the function succeeds, the return value
//								is 1 (true); 
//								if fails, the return value is 0 (false). 
//
//	HDC		DestDC				Handle to the destination device context;
//	int		DestX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestWidth			Specifies the width, in logical units,
//								of the destination rectangle.
//	int		DestHeight			Specifies the height, in logical units,
//								of the destination rectangle.
//	HDC		SrcDC				Handle to the source device context;
//	int		SrcX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcWidth			Specifies the width, in logical units,
//								of the source rectangle;
//	int		SrcHeight			Specifies the height, in logical units,
//								of the source rectangle.
//	int		Gamma				Gamma (value in range 0 to 255);
//
////////////////////////////////////////////////////////////////////////////
int __stdcall fxGamma(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight, int Gamma)
{
	if (Gamma < 0)
		Gamma = 0;
	if (Gamma > 255)
		Gamma = 255;

	double gamma		= (double) Gamma;
	gamma = gamma / 100;

	BITMAPINFOHEADER	BMI;
	BMI.biSize			= sizeof(BITMAPINFOHEADER);
	BMI.biWidth			= DestWidth;
	BMI.biHeight		= DestHeight;
	BMI.biPlanes		= 1;
	BMI.biBitCount		= 32;
	BMI.biCompression	= BI_RGB;
	BMI.biSizeImage		= 0;
	BMI.biXPelsPerMeter = 0;
	BMI.biYPelsPerMeter = 0;
	BMI.biClrUsed		= 0;
	BMI.biClrImportant	= 0;
	
	BYTE				*pDestBits;
	HBITMAP				hbmDest;
	hbmDest = ::CreateDIBSection(DestDC, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pDestBits, NULL, 0l);

	BYTE				*pSrcBits;
	HBITMAP				hbmSrc;
	hbmSrc = ::CreateDIBSection(SrcDC, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pSrcBits, NULL, 0l);

	HDC					dc = ::CreateCompatibleDC(NULL);
	HBITMAP				hbm = (HBITMAP) ::SelectObject(dc, hbmSrc);
	
	if (!::StretchBlt(dc, 0, 0, DestWidth, DestHeight, SrcDC, SrcX, SrcY, SrcWidth, SrcHeight, SRCCOPY))
		return 0;

	::SelectObject(dc, hbmDest);

	if (!::StretchBlt(dc, 0, 0, DestWidth, DestHeight, DestDC, DestX, DestY, DestWidth, DestHeight, SRCCOPY))
		return 0;

	::SelectObject(dc, hbm);

	::DeleteDC(dc);

    for (int y = 0; y < DestHeight; y++)
    {
		LPBYTE pbDestRGB = (LPBYTE)&((DWORD*)pDestBits)[y * DestWidth];
		LPBYTE pbSrcRGB = (LPBYTE)&((DWORD*)pSrcBits)[y * DestWidth];

		for (int x = 0; x < DestWidth; x++)
		{
			pbSrcRGB[0] = (int)(255.0 * pow(pbSrcRGB[0] / 255.0, 1.0 / gamma));
			pbSrcRGB[1] = (int)(255.0 * pow(pbSrcRGB[1] / 255.0, 1.0 / gamma));
			pbSrcRGB[2] = (int)(255.0 * pow(pbSrcRGB[2] / 255.0, 1.0 / gamma));

			pbSrcRGB += 4;
			pbDestRGB += 4;
		}
	}

	dc = ::CreateCompatibleDC(NULL);
	
	hbm = (HBITMAP) ::SelectObject(dc, hbmSrc);
	if (!::BitBlt(DestDC, DestX, DestY, DestWidth, DestHeight, dc, 0, 0, SRCCOPY))
		return 0;

	::DeleteDC(dc);

	::DeleteObject(hbmSrc);	
	::DeleteObject(hbmDest);	
	
	return 1;
}



////////////////////////////////////////////////////////////////////////////
//
//	fxGetBlue()					These function returns the red, green or
//	fxGetGreen()				blue values (value in range 0 to 255)
//  fxGetRed()					from the given RGB color value.
//  
//	int		RGB					Specifies the RGB color.
//
////////////////////////////////////////////////////////////////////////////
int __stdcall fxGetBlue(int RGB)
{
	return ((RGB & 16711680) / 65536);
}


int __stdcall fxGetGreen(int RGB)
{
	return ((RGB & 65280) / 256);
}


int __stdcall fxGetRed(int RGB)
{
	return (RGB & 255);
}



/*
////////////////////////////////////////////////////////////////////////////
//
//	fxHSL()						Function returns RGB color value
//								from given HSL values.
//
//	int		H					Hue value (value in range 0 to 255);
//	int		S					Saturation value (value in range 0 to 255);
//	int		L					Luminosity value (value in range 0 to 255).
//
////////////////////////////////////////////////////////////////////////////
int __stdcall fxHSL(int H, int S, int L)
{
	int fxR				= 0;
	int fxG				= 0;
	int fxB				= 0;

	int fxMax			= 0;
	int fxMin			= 0;

	if (S == 0)
	{
		// Achromatic case:
		fxR = L;
		fxG = L;
		fxB = L;
	}
	else
	{
		// Chromatic case:
		if (L <= 1)
		{
			fxMin = L * (1 - S);
		}
		else
		{
			fxMin = L - S * (1 - L);
		}

		fxMax = 2 * L - fxMin;

		if (H < 1)
		{
			fxR = Max;
			
			if (H < 0)
			{
				fxG = fxMin;
				fxB = fxG - H * (fxMax - fxMin);
			}
			else
			{
				fxB = fxMin;
				fxG = H * (fxMax - fxMin) + fxB;
			}
		}
		else
		{
			if (H < 3)
			{
				fxG = fxMax;
				if (H < 2)
				{
					fxB = fxMin;
					fxR = fxB - (H - 2) * (fxMax - fxMin);
				}
				else
				{
					fxR = fxMin;
					fxB = (H - 2) * (fxMax - fxMin) + fxR;
				}
			}
			else
			{
				fxB = fxMax;
				if (H < 4)
				{
					fxR = fxMin;
					fxG = fxR - (H - 4) * (fxMax - fxMin);
				}
				else
				{
					fxG = fxMin;
					fxR = (H - 4) * (fxMax - fxMin) + fxG;
				}
			}
		}

   R = rR * 255: G = rG * 255: B = rB * 255


	return (B * 65536 + G * 256 + R);
}
*/



////////////////////////////////////////////////////////////////////////////
//
//	fxReplaceColor()			Function replaces given color in 
//								destination device context with specified
//								replace color, 
//								first stretching or compressing bitmap to 
//								fit the dimensions of the destination 
//								rectangle, if necessary.
//								If the function succeeds, the return value
//								is 1 (true); 
//								if fails, the return value is 0 (false). 
//
//	HDC		DestDC				Handle to the destination device context;
//	int		DestX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestWidth			Specifies the width, in logical units,
//								of the destination rectangle.
//	int		DestHeight			Specifies the height, in logical units,
//								of the destination rectangle.
//	HDC		SrcDC				Handle to the source device context;
//	int		SrcX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcWidth			Specifies the width, in logical units,
//								of the source rectangle;
//	int		SrcHeight			Specifies the height, in logical units,
//								of the source rectangle;
//	int		Color				Color to be replaced (RGB);
//	int		ReplaceColor		Color to replace with (RGB); 
//	int		Similarity			Similarity within the colors will be
//								replaced (value in range 0(1) to 255).
//
////////////////////////////////////////////////////////////////////////////
int __stdcall fxReplaceColor(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight, int Color, int ReplaceColor, int Similarity)
{
	if (Similarity < 0)
		Similarity = 0;
	if (Similarity > 255)
		Similarity = 255;

	int fxR				= fxGetRed(Color);
	int fxG				= fxGetGreen(Color);
	int fxB				= fxGetBlue(Color);

	int fxR_r			= fxGetRed(ReplaceColor);
	int fxG_r			= fxGetGreen(ReplaceColor);
	int fxB_r			= fxGetBlue(ReplaceColor);

	BITMAPINFOHEADER	BMI;
	BMI.biSize			= sizeof(BITMAPINFOHEADER);
	BMI.biWidth			= DestWidth;
	BMI.biHeight		= DestHeight;
	BMI.biPlanes		= 1;
	BMI.biBitCount		= 32;
	BMI.biCompression	= BI_RGB;
	BMI.biSizeImage		= 0;
	BMI.biXPelsPerMeter = 0;
	BMI.biYPelsPerMeter = 0;
	BMI.biClrUsed		= 0;
	BMI.biClrImportant	= 0;
	
	BYTE				*pDestBits;
	HBITMAP				hbmDest;
	hbmDest = ::CreateDIBSection(DestDC, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pDestBits, NULL, 0l);

	BYTE				*pSrcBits;
	HBITMAP				hbmSrc;
	hbmSrc = ::CreateDIBSection(SrcDC, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pSrcBits, NULL, 0l);

	HDC					dc = ::CreateCompatibleDC(NULL);
	HBITMAP				hbm = (HBITMAP) ::SelectObject(dc, hbmSrc);
	
	if (!::StretchBlt(dc, 0, 0, DestWidth, DestHeight, SrcDC, SrcX, SrcY, SrcWidth, SrcHeight, SRCCOPY))
		return 0;

	::SelectObject(dc, hbmDest);

	if (!::StretchBlt(dc, 0, 0, DestWidth, DestHeight, DestDC, DestX, DestY, DestWidth, DestHeight, SRCCOPY))
		return 0;

	::SelectObject(dc, hbm);

	::DeleteDC(dc);

    for (int y = 0; y < DestHeight; y++)
    {
		LPBYTE pbDestRGB = (LPBYTE)&((DWORD*)pDestBits)[y * DestWidth];
		LPBYTE pbSrcRGB = (LPBYTE)&((DWORD*)pSrcBits)[y * DestWidth];

		for (int x = 0; x < DestWidth; x++)
		{
			if ((abs(fxR - pbSrcRGB[2]) < Similarity) & (abs(fxG - pbSrcRGB[1]) < Similarity) & (abs(fxB - pbSrcRGB[0]) < Similarity))
				pbSrcRGB[0] = fxB_r,
				pbSrcRGB[1] = fxG_r,
				pbSrcRGB[2] = fxR_r;

			pbSrcRGB += 4;
			pbDestRGB += 4;
		}
	}

	dc = ::CreateCompatibleDC(NULL);
	
	hbm = (HBITMAP) ::SelectObject(dc, hbmSrc);
	if (!::BitBlt(DestDC, DestX, DestY, DestWidth, DestHeight, dc, 0, 0, SRCCOPY))
		return 0;

	::DeleteDC(dc);

	::DeleteObject(hbmSrc);	
	::DeleteObject(hbmDest);	
	
	return 1;
}



////////////////////////////////////////////////////////////////////////////
//
//	fxRGB()						Function returns the RGB color value from
//								given RGB values.
//
//	int		R					Red value (value in range 0 to 255);
//	int		G					Green value (value in range 0 to 255);
//	int		B					Blue value (value in range 0 to 255).
//
////////////////////////////////////////////////////////////////////////////
int __stdcall fxRGB(int R, int G, int B)
{
	return (B * 65536 + G * 256 + R);
}



////////////////////////////////////////////////////////////////////////////
//
//	fxScanlines()				Displays scan-lined bitmap,
//								first stretching or compressing it to fit
//								the dimensions of the destination rectangle,
//								if necessary.
//								If the function succeeds, the return value
//								is 1 (true); 
//								if fails, the return value is 0 (false). 
//
//	HDC		DestDC				Handle to the destination device context;
//	int		DestX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestWidth			Specifies the width, in logical units,
//								of the destination rectangle.
//	int		DestHeight			Specifies the height, in logical units,
//								of the destination rectangle.
//	HDC		SrcDC				Handle to the source device context;
//	int		SrcX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcWidth			Specifies the width, in logical units,
//								of the source rectangle;
//	int		SrcHeight			Specifies the height, in logical units,
//								of the source rectangle;
//	int		Color				Color of scan-lines (RGB);
//	int		Flags				Optional flags
//								FX_SCANLINES_STANDARD	= 0000
//								FX_SCANLINES_HORIZONTAL = 0001
//								FX_SCANLINES_VERTICAL	= 0010
//								FX_SCANLINES_ALPHA		= 0100
//
////////////////////////////////////////////////////////////////////////////
int __stdcall fxScanlines(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight, int Color, int Flags)
{
	if (Flags < 0)
		Flags = 0;
	if (Flags > 2)
		Flags = 2;

	BITMAPINFOHEADER	BMI;
	BMI.biSize			= sizeof(BITMAPINFOHEADER);
	BMI.biWidth			= DestWidth;
	BMI.biHeight		= DestHeight;
	BMI.biPlanes		= 1;
	BMI.biBitCount		= 32;
	BMI.biCompression	= BI_RGB;
	BMI.biSizeImage		= 0;
	BMI.biXPelsPerMeter = 0;
	BMI.biYPelsPerMeter = 0;
	BMI.biClrUsed		= 0;
	BMI.biClrImportant	= 0;
	
	BYTE				*pDestBits;
	HBITMAP				hbmDest;
	hbmDest = ::CreateDIBSection(DestDC, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pDestBits, NULL, 0l);

	BYTE				*pSrcBits;
	HBITMAP				hbmSrc;
	hbmSrc = ::CreateDIBSection(SrcDC, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pSrcBits, NULL, 0l);

	HDC					dc = ::CreateCompatibleDC(NULL);
	HBITMAP				hbm = (HBITMAP) ::SelectObject(dc, hbmSrc);
	
	if (!::StretchBlt(dc, 0, 0, DestWidth, DestHeight, SrcDC, SrcX, SrcY, SrcWidth, SrcHeight, SRCCOPY))
		return 0;

	::SelectObject(dc, hbmDest);

	if (!::StretchBlt(dc, 0, 0, DestWidth, DestHeight, DestDC, DestX, DestY, DestWidth, DestHeight, SRCCOPY))
		return 0;

	::SelectObject(dc, hbm);

	::DeleteDC(dc);

    for (int y = 0; y < DestHeight; y++)
    {
		LPBYTE pbDestRGB = (LPBYTE)&((DWORD*)pDestBits)[y * DestWidth];
		LPBYTE pbSrcRGB = (LPBYTE)&((DWORD*)pSrcBits)[y * DestWidth];

		for (int x = 0; x < DestWidth; x++)
		{
			if ((y % 2) == 1)
			{
				if ((Flags == 0) | (Flags == 2))
				pbSrcRGB[0] = fxByte(pbSrcRGB[0] + fxGetBlue(Color)),
				pbSrcRGB[1] = fxByte(pbSrcRGB[1] + fxGetGreen(Color)),
				pbSrcRGB[2] = fxByte(pbSrcRGB[2] + fxGetRed(Color));
			}
				
			if ((x % 2) == 1) 
			{
				if ((Flags == 1) | (Flags == 2))
				pbSrcRGB[0] = fxByte(pbSrcRGB[0] + fxGetBlue(Color)),
				pbSrcRGB[1] = fxByte(pbSrcRGB[1] + fxGetGreen(Color)),
				pbSrcRGB[2] = fxByte(pbSrcRGB[2] + fxGetRed(Color));
			}

			pbSrcRGB += 4;
			pbDestRGB += 4;
		}
	}

	dc = ::CreateCompatibleDC(NULL);
	
	hbm = (HBITMAP) ::SelectObject(dc, hbmSrc);
	if (!::BitBlt(DestDC, DestX, DestY, DestWidth, DestHeight, dc, 0, 0, SRCCOPY))
		return 0;

	::DeleteDC(dc);

	::DeleteObject(hbmSrc);	
	::DeleteObject(hbmDest);	
	
	return 1;
}



////////////////////////////////////////////////////////////////////////////
//
//	fxShadeColors()				Function returns the shaded color value
//								that is calculated from destination,
//								source colors and shade values.
//
//	int		DestColor			Specifies the destination color value;
//	int		SrcColor			Specifies the source color value;
//	int		ShadeValue			Shade value (value in range 0 to 255).
//
////////////////////////////////////////////////////////////////////////////
int __stdcall fxShadeColors(int DestColor, int SrcColor, int Shade)
{
	if (Shade == 0)
		return DestColor;
	if (Shade == 255)
		return SrcColor;

	return (DestColor * (255 - Shade) + SrcColor * Shade)>>8;
}



////////////////////////////////////////////////////////////////////////////
//
//	fxStretchBlt()				Function copies a bitmap from a source 
//								rectangle into a destination rectangle, 
//								stretching or compressing the bitmap to fit
//								the dimensions of the destination rectangle,
//								if necessary. Windows stretches or 
//								compresses the bitmap according to the 
//								stretching mode currently set in the 
//								destination device context.
//								If the function succeeds, the return value
//								is 1 (true); 
//								if fails, the return value is 0 (false). 
//
//	HDC		DestDC				Handle to the destination device context;
//	int		DestX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestWidth			Specifies the width, in logical units,
//								of the destination rectangle.
//	int		DestHeight			Specifies the height, in logical units,
//								of the destination rectangle.
//	HDC		SrcDC				Handle to the source device context;
//	int		SrcX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcWidth			Specifies the width, in logical units,
//								of the source rectangle;
//	int		SrcHeight			Specifies the height, in logical units,
//								of the source rectangle.
//	int		RasterOperation		Specifies a raster-operation code.
//
////////////////////////////////////////////////////////////////////////////
int __stdcall fxStretchBlt(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight, int RasterOperation)
{
	return ::StretchBlt(DestDC, DestX, DestY, DestWidth, DestHeight, SrcDC, SrcX, SrcY, SrcWidth, SrcHeight, RasterOperation);
}



////////////////////////////////////////////////////////////////////////////
//
//	fxTransparentBlt()			Function performs a bit-block transfer 
//								of the color data corresponding to a
//								rectangle of pixels from the specified
//								source device context into a destination
//								device context,	stretching or compressing
//								the bitmap to fit the dimensions of the
//								destination rectangle, if necessary.
//								If the function succeeds, the return value
//								is 1 (true); 
//								if fails, the return value is 0 (false). 
//
//	HDC		DestDC				Handle to the destination device context;
//	int		DestX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the destination rectangle;
//	int		DestWidth			Specifies the width, in logical units,
//								of the destination rectangle.
//	int		DestHeight			Specifies the height, in logical units,
//								of the destination rectangle.
//	HDC		SrcDC				Handle to the source device context;
//	int		SrcX				Specifies the x-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcY				Specifies the y-coordinate, 
//								in logical units, of the upper-left 
//								corner of the source rectangle;
//	int		SrcWidth			Specifies the width, in logical units,
//								of the source rectangle;
//	int		SrcHeight			Specifies the height, in logical units,
//								of the source rectangle;
//	int		TransparentColor	The RGB color in the source DC to 
//								treat as transparent.
//
////////////////////////////////////////////////////////////////////////////
int __stdcall fxTransparentBlt(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight, int TransparentColor)
{
	return fxAlphaBlend(DestDC, DestX, DestY, DestWidth, DestHeight, SrcDC, SrcX, SrcY, SrcWidth, SrcHeight, 255, TransparentColor);
}
