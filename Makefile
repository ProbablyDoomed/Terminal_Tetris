
IDIR = inc
ODIR = obj
SDIR = src

OUTPUT_BIN = tetris.exe

CC = x86_64-w64-mingw32-gcc
CFLAGS = -time -I$(IDIR) -o ${OUTPUT_BIN}

tetrismake:
	${CC} ${CFLAGS} $(SDIR)/*.c
