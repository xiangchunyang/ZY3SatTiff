#include "TiffDecoder.h"
#include "Bitmapper.h"
#include <time.h>
#include <exception>
using namespace std;

int main(void)
{
	char tiffFileName[] = "F:\\Dataset\\ZY3_00\\1.tiff";
	char bmpFileName[] = "F:\\Dataset\\ZY3_00\\1.bmp";

	try
	{
		TiffDecoder td;
		td.Open(tiffFileName);
		td.Prepare();

		int width = td.GetWidth();
		int height = td.GetHeight();
		int imgSize = width*height;

		printf("ImageSize: width=%d,height=%d\n", width, height);

		u16* srcData = new u16[imgSize];
		byte* u8 = new byte[imgSize];

		printf("Decoding, please wait...\n");

		time_t t0 = time(NULL);
		td.LoadData((byte*)srcData);
		time_t t1 = time(NULL);
		double et = difftime(t1, t0);

		printf("Decoding time: %.2f sec.\n", et);

		printf("Remapping, please wait...\n");

		u16 min = srcData[0];
		u16 max = min;
		for (int i = 1; i < imgSize; ++i)
		{
			if (srcData[i]>max) max = srcData[i];
			else if (srcData[i] < min) min = srcData[i];
			else continue;
		}

		if (max == min)
		{
			printf("INVALID IMAGE DATA!\n");
			throw new exception("max==min");
		}

		double factor = 255.0 / (max - min);

		for (int i = 0; i < imgSize; ++i)
		{
			u8[i] = (byte)((srcData[i] - min)*factor);
		}

		SaveAsBMP(u8, width, height, bmpFileName);

		time_t t2 = time(NULL);
		et = difftime(t2, t1);

		printf("Remapping time: %.2f sec.\n", et);

		delete[] srcData;
		delete[] u8;

		td.Release();

		printf("Complete!\n\n");
	}
	catch (exception e)
	{
		puts(e.what());
	}

	system("pause");
}