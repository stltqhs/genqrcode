#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"
#define OUT_FILE "/mnt/test/genqrcode/gen.bmp"
PBitmap wrap_qrcode_to_bitmap(QRcode *qrcode, int ps)
{
	int width = qrcode->width;
	BYTE *data = qrcode->data;
	int size_per_pixel = ps;

	int w = width * size_per_pixel;
	int h = width * size_per_pixel;
	PBitmap bitmap = create_bitmap(24, w, h);
	int i, j, k, n;
	for (i = 0; i < width; i++)//row
	{
		for (j = 0; j < width; j++)//column
		{
			int r = *(qrcode->data + i * width + j);
			int flag = r & 1;
			for(k = 0; k < size_per_pixel; k++)//row
			{
				for(n = 0; n < size_per_pixel; n++)//column
				{
					if (flag)
					{
					}
					else
						set_pixel_bitmap(bitmap, j * size_per_pixel + n, i * size_per_pixel + k, 0xFFFFFF);
				}
			}
		}	
	}
	return bitmap;
}
PBitmap create_bitmap(unsigned int bitCount, unsigned int width, unsigned int height)
{
	PBitmap bitmap;
	BITMAPFILEHEADER fh;
	BITMAPINFOHEADER ih;

	char BMFlag[] = {'B', 'M'};

	int rowDataLen = (width * bitCount / 8 + 3) / 4 * 4;
	int bitmapSize = rowDataLen * height;

	BYTE *bitmap_data = NULL;


	memset(&fh, 0, sizeof(fh));
	memset(&ih, 0, sizeof(ih));

	fh.bfType = *((WORD*)BMFlag);
	fh.bfSize = bitmapSize + sizeof(fh) + sizeof(ih);
	fh.bfOffBits = sizeof(fh) + sizeof(ih);

	ih.biSize = sizeof(ih);
	ih.biWidth = width;
	ih.biHeight = -height;
	ih.biPlanes = 1;
	ih.biBitCount = bitCount;
	ih.biCompression = BI_RGB;

	bitmap_data = malloc(fh.bfSize);
	memset(bitmap_data, 0, fh.bfSize);

	memcpy(bitmap_data, &fh, sizeof(fh));
	memcpy(bitmap_data + sizeof(fh), &ih, sizeof(ih));

	bitmap = malloc(sizeof(Bitmap));

	bitmap->width = width;
	bitmap->height = height;
	bitmap->bitCount = bitCount;
	bitmap->data = bitmap_data;
	bitmap->len = fh.bfSize;

	return bitmap;
}
void destroy_bitmap(PBitmap bitmap)
{
	free(bitmap->data);
	free(bitmap);
}
int get_pixel_bitmap(PBitmap bitmap, int x, int y)
{
	int rgb = 0;
	BYTE r = 0;
	BYTE g = 0;
	BYTE b = 0;
	int offset = offset_byte_bitmap(bitmap, x, y);
	b = *((BYTE*)(bitmap->data + offset));
	g = *((BYTE*)(bitmap->data + offset + 1));
	r = *((BYTE*)(bitmap->data + offset + 2));
	rgb = rgb | b;
	rgb = rgb | (g << 8);
	rgb = rgb | (r << 16);
	return rgb;
}
void set_pixel_bitmap(PBitmap bitmap, int x, int y, int rgb)
{
	int offset = offset_byte_bitmap(bitmap, x, y);
	BYTE r = (rgb >> 16) & 0xFF;
	BYTE g = (rgb >> 8) & 0xFF;
	BYTE b = rgb & 0xFF;
	BYTE *pdata = (BYTE*)(bitmap->data + offset);
	*pdata = b;
	pdata++;
	*pdata = g;
	pdata++;
	*pdata = r;	
}
int offset_byte_bitmap(PBitmap bitmap, int x, int y)
{
	PBITMAPFILEHEADER pfh = (PBITMAPFILEHEADER)bitmap->data;
	PBITMAPINFOHEADER pih = (PBITMAPINFOHEADER)(bitmap->data + sizeof(BITMAPFILEHEADER));
	int width = bitmap->width;
	int height = bitmap->height;
	int bc = bitmap->bitCount / 8;
	int rowDataLen = (width * bc + 3)/ 4 * 4;
	int offset = y * rowDataLen + x * bc;
	offset += sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	return offset;
}

void write_bitmap(PBitmap bitmap, char *fn)
{
	FILE *file = NULL;
	file = fopen(fn, "wb");
	if (file)
	{
		fwrite(bitmap->data, 1, bitmap->len, file);
		fclose(file);
	}
}
