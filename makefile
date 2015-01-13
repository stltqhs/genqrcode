LIB_DIR=/usr/local/lib
LIB=qrencode
OBJS=genqrcode.o bitmap.o
MYOPTIONS= -g
genqrcode:$(OBJS)
	gcc $(MYOPTIONS) -o $@ -L$(LIB_DIR)  -l$(LIB) $^
genqrcode.o:genqrcode.c genqrcode.h bitmap.h
	gcc $(MYOPTIONS) -o $@ -c $<
bitmap.o:bitmap.c bitmap.h
	gcc $(MYOPTIONS) -o $@ -c $<
PHONY:clean
clean:
	rm -f genqrcode.0 genqrcode bitmap.o
