include ../Makefile.inc

all : ${TLPI_LIB}

OBJECTS = $(patsubst %.c,%.o,$(wildcard *.c))

${TLPI_LIB} : ${OBJECTS}
	${RM} ${TLPI_LIB}
	${AR} rs ${TLPI_LIB} *.o

clearn : 
	${RM} *.o ${TLPI_LIB}
