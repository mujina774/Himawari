# Makefile for HISD sample
# Specify the path according to the execution environment.
CC = /usr/bin/gcc
INC = -I/usr/local/include
LIB = -lm

MODULE = hisd_sample_130

SRC = main.c hisd_info.c  hisd_pixlin2lonlat.c  hisd_read.c
OBJ = $(SRC:%.c=%.o)

$(MODULE) : $(OBJ)
	$(CC) -o  $@ $(OBJ) $(LIB)

.c.o:
	$(CC) -c -Wall $(INC) $<

clean:
	-rm -f *.o $(MODULE)

 main.o					:hisd.h
 hisd_info.o			:hisd.h
 hisd_pixlin2lonlat.o	:hisd.h
 hisd_read.o			:hisd.h
