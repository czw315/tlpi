include ../Makefile.inc

EXE = copy seek_io bad_exclusive_open

#CFLAGS = -I${TLPI_INCL_DIR}

all : ${EXE}

clearn :
	${RM} ${EXE}

showall :
	@ echo ${EXE}
	@ echo ${CFLAGS}

${EXE} : ${TLPI_LIB}
