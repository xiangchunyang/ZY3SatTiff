#include "Bitmapper.h"
#include <stdio.h>

#ifdef _MSC_VER
#pragma warning(disable:4996)
#endif

void SaveAsBMP(byte* imgData, int width, int height, const char* fileName, bool flipud)
{
	int imgSize = width*height;

	BITMAPHEADER bmpHeader;
	bmpHeader.A01_2_bfType = CW_BM;
	bmpHeader.A02_4_bfSize = CL_BMPH_SZ + CL_BMPAL_SZ + imgSize; // !!!
	bmpHeader.A03_2_bfReserved1 = 0;
	bmpHeader.A04_2_bfReserved2 = 0;
	bmpHeader.A05_4_bfOffBits = CL_BMPH_SZ + CL_BMPAL_SZ;
	bmpHeader.A06_4_biSize = CL_BMIH_SZ;
	bmpHeader.A07_4_biWidth = width;
	bmpHeader.A08_4_biHeight = flipud ? -height : height; // IMPORTANT
	bmpHeader.A09_2_biPlanes = 1;
	bmpHeader.A10_2_biBitCount = 8;
	bmpHeader.A11_4_biCompression = CL_BI_UNC; // UNCOMPRESSED
	bmpHeader.A12_4_biSizeImage = imgSize;
	bmpHeader.A13_4_biXPelsPerMeter = 0;
	bmpHeader.A14_4_biYPelsPerMeter = 0;
	bmpHeader.A15_4_biClrUsed = 0;
	bmpHeader.A16_4_biClrImportant = 0;

	RGBQ* ct = new RGBQ[256];
	for (int i = 0; i < 256; ++i)
	{
		ct[i].b = ct[i].g = ct[i].r = (BYTE)i;
	}

	FILE* fp = fopen(fileName, "wb");
	fwrite(&bmpHeader, CL_BMPH_SZ, 1, fp);
	fwrite(ct, sizeof(RGBQ), 256, fp);

	int r = width % 4;
	if (r == 0)
	{
		fwrite(imgData, imgSize, 1, fp);
	}
	else
	{
		byte* ptr = imgData;
		int offset = 4 - r;
		byte zeros[5] = { 0,0,0,0,0 };
		for (int i = 0; i < height; ++i)
		{
			fwrite(ptr, width, 1, fp);
			fwrite(zeros, offset, 1, fp);
			ptr += width;
		}
	}

	fflush(fp);
	fclose(fp);

	delete[] ct;
}