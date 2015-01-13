#include <qrencode.h>
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef signed int LONG;
#define PIXEL_COLOR_B 0
#define PIXEL_COLOR_G 0
#define PIXEL_COLOR_R 0
#define BI_RGB 0L
#ifndef BITMAP
#define BITMAP
typedef struct __attribute__((packed)) tagBITMAPFILEHEADER
{
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;
typedef struct __attribute__((packed)) tagBITMAPINFOHEADER
{
	DWORD  biSize; 
	LONG   biWidth; 
	LONG   biHeight; 
	WORD   biPlanes; 
	WORD   biBitCount; 
	DWORD  biCompression; 
	DWORD  biSizeImage; 
	LONG   biXPelsPerMeter; 
	LONG   biYPelsPerMeter; 
	DWORD  biClrUsed; 
	DWORD  biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;
#endif
#ifndef BITMAP_S
#define BITMAP_S
typedef struct tagBITMAP
{
unsigned int width;
unsigned int height;
BYTE bitCount;
BYTE *data;
unsigned int len;
} Bitmap, *PBitmap;
#endif
PBitmap create_bitmap(unsigned int bitCount, unsigned int width, unsigned int height);
void destroy_bitmap(PBitmap bitmap);
int get_pixel_bitmap(PBitmap bitmap, int x, int y);
void set_pixel_bitmap(PBitmap bitmap, int x, int y, int rgb);
PBitmap wrap_qrcode_to_bitmap(QRcode *, int ps);
int offset_byte_bitmap(PBitmap bitmap, int x, int y);
void write_bitmap(PBitmap bitmap, char *fn);
