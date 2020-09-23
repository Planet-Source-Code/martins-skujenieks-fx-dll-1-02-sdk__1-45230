
int __stdcall fxAlphaBlend(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight, int Alpha, int MaskColor);
int __stdcall fxAmbientLight(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight, int Color, int Intensity);
int __stdcall fxAntiAlias(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight);
int __stdcall fxBitBlt(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int RasterOperation);
int __stdcall fxBlur(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight);
int __stdcall fxBrightness(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight, int Brightness);
int __stdcall fxFilter(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight, int Filter, int Flags);
int __stdcall fxGamma(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight, int Gamma);
int __stdcall fxGetBlue(int RGB);
int __stdcall fxGetGreen(int RGB);
int __stdcall fxGetRed(int RGB);
int __stdcall fxReplaceColor(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight, int Color, int ReplaceColor, int Similarity);
int __stdcall fxRGB(int R, int G, int B);
int __stdcall fxScanlines(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight, int Color, int Flags);
int __stdcall fxShadeColors(int DestColor, int SrcColor, int Shade);
int __stdcall fxStretchBlt(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight, int RasterOperation);
int __stdcall fxTransparentBlt(HDC DestDC, int DestX, int DestY, int DestWidth, int DestHeight, HDC SrcDC, int SrcX, int SrcY, int SrcWidth, int SrcHeight, int TransparentColor);



////////////////////////////////////////////////////////////////////////////
//
//	fxByte()					Converts given value to a byte value
//								(if neccessary) and returns it.
//
//	int		Value				Specifies the value to be converted.
//
////////////////////////////////////////////////////////////////////////////
int fxByte(int Value)
{
	if (Value < 0)
		Value = 0;
	if (Value > 255)
		Value = 255;
	return Value;
}
