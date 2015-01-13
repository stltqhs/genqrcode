#include "genqrcode.h"
#include <qrencode.h>
#include <stdio.h>
#include <string.h>
#include "bitmap.h"
int main(int argc, char *argv[])
{
    FILE *out = NULL;
    if (argc < 3)
	    print_usage();
    char *text = argv[1];
    char *fn = argv[2];
    qrencode(text, fn);
}
void qrencode(char * code, char *fn)
{
    QRcode *qrc = NULL;
    qrc = QRcode_encodeString(code, 0, QR_ECLEVEL_L, QR_MODE_8, 1);
    if (qrc)
    {
    	PBitmap bitmap = wrap_qrcode_to_bitmap(qrc, 8);
	write_bitmap(bitmap, fn);
	destroy_bitmap(bitmap);
    }
    QRcode_free(qrc);
}
void print_usage()
{
	printf("qrcode generate.\nusage:genqrcode TEXT FILE\nTEXT is used to encode\nFILE is output image file name.\n");
}
