#include<sys/stat.h>
#include<fcntl.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int
main(int argc, char** argv)
{
    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];

    if(argc!=3 || strcmp(argv[1],"--help")==0)
        usageErr("%s input-file output-file\n",argv[0]);

    inputFd = open(argv[1], O_RDONLY);
    if(inputFd==-1)
        errExit("opening file %s",argv[1]);

    openFlags = O_WRONLY | O_CREAT | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    outputFd = open(argv[2], openFlags, filePerms);
    if(outputFd==-1)
        errExit("opening file %s",argv[2]);
    
    while((numRead=read(inputFd, buf, BUF_SIZE))>0)
        if(write(outputFd, buf, numRead)!=numRead)
            errExit("write file %s",argv[2]);
    
    if(numRead==-1)
        errExit("read file %s",argv[1]);

    if(close(inputFd)==-1)
        errExit("close input");
    if(close(outputFd)==-1)
        errExit("close output");
    
    exit(EXIT_SUCCESS);
}