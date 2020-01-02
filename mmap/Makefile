include ../Makefile.inc
CFLAGS += -DUSE_MAP_ANON

EXE = mmcat t_mmap anon_mmap

all : ${EXE}

clear :
	${RM} ${EXE}

${EXE} : ${TLPI_LIB}
