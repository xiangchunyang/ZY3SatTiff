#ifndef BITMAP_UTILIY_H
#define  BITMAP_UTILIY_H

#include "Common.h"

typedef struct tagRGBQUAD
{
	BYTE b, g, r, v;
}RGBQ;

#pragma pack(push,1)

typedef struct tagBITMAPHEADER
{
	//
	//  type A#(01~16)_#(2/4 bytes)_sufix
	//   
	//------ BMFH ------ //
	WORD A01_2_bfType;  // Constant := 0x4D42 aka. 'BM'
	DWORD  A02_4_bfSize;
	WORD  A03_2_bfReserved1;
	WORD  A04_2_bfReserved2;
	DWORD  A05_4_bfOffBits;
	//--------BMIH------//
	DWORD  A06_4_biSize;
	LONG  A07_4_biWidth;
	LONG  A08_4_biHeight;
	WORD  A09_2_biPlanes; // Constant := 1
	WORD  A10_2_biBitCount;  // Constant : =8 (gray ONLY)
	DWORD  A11_4_biCompression;  // UNCOMPRESSED
	DWORD  A12_4_biSizeImage;
	LONG  A13_4_biXPelsPerMeter;
	LONG  A14_4_biYPelsPerMeter;
	DWORD  A15_4_biClrUsed;
	DWORD  A16_4_biClrImportant;
}BITMAPHEADER;

#pragma pack(pop)

const WORD CW_BM = 0x4D42;   // Bitmap header 0x4D42 aka. 'BM'
const DWORD CL_BI_UNC = 0;      // Bitmap compression: UNCOMPRESSED
const DWORD CL_BMFH_SZ = 14; // sizeof(BitmapFileHeader)=14
const DWORD CL_BMIH_SZ = 40;  // sizeof(BitmapInfoHeader)=40
const DWORD CL_BMPAL_SZ = 1024;  // 256 * sizeof(RGBQ)=1024 (gray ONLY)
const DWORD CL_BMPH_SZ = 54;     // sizeof(BitmapHeader)=54

void SaveAsBMP(byte* imgData, int width, int height, const char* fileName, bool flipud = true);

#endif // BITMAP_UTILIY_H