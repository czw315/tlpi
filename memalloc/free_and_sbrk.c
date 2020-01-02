#include "tlpi_hdr.h"

#define MAX_ALLOCS 1000000

int
main(int argc, char* argv[])
{
    char* ptr[MAX_ALLOCS];
    int freestep, freemin, freemax, blocksize, numallocs, j;

    printf("\n");

    if(argc<3||strcmp(argv[1],"--help")==0)
        usageErr("%s numallocs blocksize [freestep [freemin [freemax]]]\n",argv[0]);

    numallocs=getInt(argv[1],GN_GT_0,"num-allocs");
    if(numallocs>MAX_ALLOCS)
        cmdLineErr("num-allocs > %d\n",MAX_ALLOCS);
    
    blocksize=getInt(argv[2],GN_GT_0 | GN_ANY_BASE,"block-size");

    freestep=(argc>3)?getInt(argv[3],GN_GT_0,"freestep"):1;
    freemin=(argc>4)?getInt(argv[4],GN_GT_0,"freemin"):1;
    freemax=(argc>5)?getInt(argv[5],GN_GT_0,"freemax"):numallocs;

    if(freemax>numallocs)
        cmdLineErr("freemax > %d\n",numallocs);
    
    printf("initial program break:      %10p\n",sbrk(0));

    printf("Allocating %d*%d bytes\n",numallocs,blocksize);
    for(j=0;j<numallocs;j++){
        ptr[j]=malloc(blocksize);
        if(ptr[j]==NULL)
            errExit("malloc");
    }

    printf("program break is now:       %10p\n",sbrk(0));

    printf("freeing blocks from %d to %d in steps of %d\n",
        freemin,freemax,freestep);

    for(j=freemin-1;j<freemax;j+=freestep)
        free(ptr[j]);

    printf("after free(), program break is:     %10p\n",sbrk(0));
    exit(EXIT_SUCCESS);
}